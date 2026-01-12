%code requires {
    #include "symtab.h"
}

%{
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern int yylineno;
extern int col;
int yylex();
void yyerror(const char *s);

/* Function Prototypes (Declarations only) */
static char *new_label();
static void copy_place(char *dst, const char *src);
static CVal gen_binop(CVal a, CVal b, const char *op_int, const char *op_float, const char *op_symbol);
static CVal gen_unary_minus(CVal a);

FILE *out = NULL;
%}

%union {
    int ival;
    double fval;
    char *sval;
    int bval;
    CVal cval;
}

%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL
%token <sval> STRING_LITERAL
%token <bval> BOOL_LITERAL
%token <sval> IDENTIFIER

%token INT FLOAT STRING BOOL STRUCT
%token REPEAT DO DONE
%token ASSIGN

%token PLUS MINUS MULT DIV MOD POW
%token GT LT GE LE EQ NEQ
%token AND OR NOT
%token LPAREN RPAREN LBRACE RBRACE COMMA SEMICOLON DOT

%type <cval> expr or_expr and_expr not_expr rel_expr add_expr mul_expr pow_expr unary primary

%start program

%%

program:
      stmt_list
    {
      fprintf(out, "HALT\n");
    }
;

stmt_list:
      stmt_list stmt
    | 
    ;

stmt:
      assign SEMICOLON
    |
      expr SEMICOLON
      {
          fprintf(out, "PARAM %s\n", $1.place);
          if ($1.type == TYPE_FLOAT) fprintf(out, "CALL PUTF, 1\n");
          else fprintf(out, "CALL PUTI, 1\n");
      }
    |
      INT IDENTIFIER '[' INT_LITERAL ']' SEMICOLON
      {
          symtab_add_array($2, TYPE_INT, $4);
          Symbol *s = symtab_get($2);
          if (s) s->base_address = 25;
      }
    |
      FLOAT IDENTIFIER '[' INT_LITERAL ']' SEMICOLON
      {
          symtab_add_array($2, TYPE_FLOAT, $4);
          Symbol *s = symtab_get($2);
          if (s) s->base_address = 25;
      }
    |
      REPEAT expr DO stmt_list DONE
      {
          if ($2.type != TYPE_INT) {
              fprintf(stderr, "Semantic error: repeat requires integer expression at line %d\n", yylineno);
          } else {
              char *Lstart = new_label();
              char *Lend = new_label();
              char *ctr = new_temp();

              fprintf(out, "%s := %s\n", ctr, $2.place);
              
              fprintf(out, "%s:\n", Lstart);
              
              fprintf(out, "IFLE %s 0 GOTO %s\n", ctr, Lend);
              
              fprintf(out, "%s := SUBI %s 1\n", ctr, ctr);
              
              fprintf(out, "GOTO %s\n", Lstart);
              
              fprintf(out, "%s:\n", Lend);
              
              free(Lstart); free(Lend); free(ctr);
          }
      }
;

assign:
      IDENTIFIER ASSIGN expr
      {
          Symbol *sym = symtab_get($1);
          if (!sym) {
              symtab_add($1, $3.type == TYPE_FLOAT ? TYPE_FLOAT : TYPE_INT);
              sym = symtab_get($1);
          }
          fprintf(out, "%s := %s\n", $1, $3.place);
      }
    | 
      IDENTIFIER '[' expr ']' ASSIGN expr
      {
          Symbol *sym = symtab_get($1);
          if (!sym || !sym->is_array) {
              fprintf(stderr, "Semantic error: undeclared array '%s' at line %d\n", $1, yylineno);
          } else {
              char *addr = new_temp();
              fprintf(out, "%s := ADDI %d %s\n", addr, sym->base_address, $3.place);
              
              if ($6.type == TYPE_FLOAT) fprintf(out, "STOREF %s %s\n", addr, $6.place);
              else fprintf(out, "STOREI %s %s\n", addr, $6.place);
              
              free(addr);
          }
      }
;

expr:
      or_expr { $$ = $1; }
;

or_expr:
      or_expr OR and_expr { $$ = $1; }
    | and_expr { $$ = $1; }
;

and_expr:
      and_expr AND not_expr { $$ = $1; }
    | not_expr { $$ = $1; }
;

not_expr:
      NOT not_expr { $$ = $2; }
    | rel_expr { $$ = $1; }
;

rel_expr:
      rel_expr GT add_expr { $$ = gen_binop($1, $3, "GTI", "GTF", ">"); }
    | rel_expr GE add_expr { $$ = gen_binop($1, $3, "GEI", "GEF", ">="); }
    | rel_expr LT add_expr { $$ = gen_binop($1, $3, "LTI", "LTF", "<"); }
    | rel_expr LE add_expr { $$ = gen_binop($1, $3, "LEI", "LEF", "<="); }
    | rel_expr EQ add_expr { $$ = gen_binop($1, $3, "EQI", "EQF", "=="); }
    | rel_expr NEQ add_expr { $$ = gen_binop($1, $3, "NEQI", "NEQF", "!="); }
    | add_expr { $$ = $1; }
;

add_expr:
      PLUS add_expr { $$ = $2; }
    | MINUS add_expr { $$ = gen_unary_minus($2); }
    | add_expr PLUS mul_expr { $$ = gen_binop($1, $3, "ADDI", "ADDF", "+"); }
    | add_expr MINUS mul_expr { $$ = gen_binop($1, $3, "SUBI", "SUBF", "-"); }
    | mul_expr { $$ = $1; }
;

mul_expr:
      mul_expr MULT pow_expr { $$ = gen_binop($1, $3, "MULI", "MULF", "*"); }
    | mul_expr DIV pow_expr { $$ = gen_binop($1, $3, "DIVI", "DIVF", "/"); }
    | mul_expr MOD pow_expr { $$ = gen_binop($1, $3, "MODI", "MODF", "%"); }
    | pow_expr { $$ = $1; }
;

pow_expr:
      unary POW pow_expr { $$ = gen_binop($1, $3, "POWI", "POWF", "**"); }
    | unary { $$ = $1; }
;

unary:
      primary { $$ = $1; }
;

primary:
      LPAREN expr RPAREN { $$ = $2; }
    | INT_LITERAL { 
          CVal v; v.type = TYPE_INT; 
          snprintf(v.place, sizeof(v.place), "%d", $1); 
          $$ = v; 
      }
    | FLOAT_LITERAL { 
          CVal v; v.type = TYPE_FLOAT; 
          snprintf(v.place, sizeof(v.place), "%lf", $1); 
          $$ = v; 
      }
    | IDENTIFIER {
          CVal v;
          Symbol *s = symtab_get($1);
          if (!s) {
              fprintf(stderr, "Semantic error: undeclared variable '%s' at line %d\n", $1, yylineno);
              v.type = TYPE_INT; strcpy(v.place, "0");
          } else {
              v.type = s->type;
              strncpy(v.place, $1, sizeof(v.place)-1);
              v.place[sizeof(v.place)-1]=0;
          }
          $$ = v;
      }
    | IDENTIFIER '[' expr ']' {
          CVal v;
          Symbol *s = symtab_get($1);
          if (!s || !s->is_array) {
              fprintf(stderr, "Semantic error: undeclared array '%s' at line %d\n", $1, yylineno);
              v.type = TYPE_INT; strcpy(v.place, "0");
          } else {
              char *addr = new_temp();
              fprintf(out, "%s := ADDI %d %s\n", addr, s->base_address, $3.place);
              
              char *valtmp = new_temp();
              if (s->type == TYPE_FLOAT) fprintf(out, "%s := LOADF %s\n", valtmp, addr);
              else fprintf(out, "%s := LOADI %s\n", valtmp, addr);
              
              v.type = s->type;
              copy_place(v.place, valtmp);
              free(addr); free(valtmp);
          }
          $$ = v;
      }
;

%%

static int lbl_counter = 0;
static char *new_label() {
    char buf[32];
    lbl_counter++;
    snprintf(buf, sizeof(buf), "L%d", lbl_counter);
    char *r = (char*)malloc(strlen(buf)+1);
    strcpy(r, buf);
    return r;
}

static void copy_place(char *dst, const char *src) { 
    strncpy(dst, src, 127);
    dst[127]=0; 
}

static CVal gen_binop(CVal a, CVal b, const char *op_int, const char *op_float, const char *op_symbol) {
    (void)op_symbol; 
    CVal res;
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        res.type = TYPE_FLOAT;
        char *tmp = new_temp();
        fprintf(out, "%s := %s %s %s\n", tmp, op_float, a.place, b.place);
        copy_place(res.place, tmp);
        free(tmp);
    } else {
        res.type = TYPE_INT;
        char *tmp = new_temp();
        fprintf(out, "%s := %s %s %s\n", tmp, op_int, a.place, b.place);
        copy_place(res.place, tmp);
        free(tmp);
    }
    return res;
}

static CVal gen_unary_minus(CVal a) {
    CVal zero;
    zero.type = a.type;
    if (a.type == TYPE_FLOAT) strcpy(zero.place, "0.0"); 
    else strcpy(zero.place, "0");
    return gen_binop(zero, a, "SUBI", "SUBF", "-");
}

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d, col %d: %s\n", yylineno, col, s);
}

int main(int argc, char **argv) {
    (void)argc; (void)argv;
    out = stdout;
    symtab_init();
    yyparse();
    return 0;
}