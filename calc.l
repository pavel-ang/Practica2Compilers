%option noyywrap
%option yylineno
%option case-insensitive
%option noinput
%option nounput

%{
#include "calc.tab.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int col = 1;
#define YY_USER_ACTION col += yyleng;
%}

%x COMMENT

digit   [0-9]
int     {digit}+
float   {digit}+"."{digit}+([eE][+-]?{digit}+)? 
id      [a-zA-Z_][a-zA-Z0-9_]*
string  \"([^\\\n]|(\\.))*\"

%%

[ \t\r]+ ;
\n { col = 1; }

"//".* ;
"#".* ;

"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>. ;
<COMMENT>\n { col = 1; }

"int"      { return INT; }
"float"    { return FLOAT; }
"string"   { return STRING; }
"bool"     { return BOOL; }
"struct"   { return STRUCT; }

"not"      { return NOT; }
"and"      { return AND; }
"or"       { return OR; }

"true"     { yylval.bval = 1; return BOOL_LITERAL; }
"false"    { yylval.bval = 0; return BOOL_LITERAL; }

"PI"       { yylval.fval = 3.141592653589793; return FLOAT_LITERAL; }
"E"        { yylval.fval = 2.718281828459045; return FLOAT_LITERAL; }



"repeat"   { return REPEAT; }
"do"       { return DO; }
"done"     { return DONE; }

":=" { return ASSIGN; }
">=" { return GE; }
"<=" { return LE; }
"<>" { return NEQ; }
">"  { return GT; }
"<"  { return LT; }
"="  { return EQ; }

"**" { return POW; }
"+"  { return PLUS; }
"-"  { return MINUS; }
"*"  { return MULT; }
"/"  { return DIV; }
"%"  { return MOD; }

";" { return SEMICOLON; }
"," { return COMMA; }
"(" { return LPAREN; }
")" { return RPAREN; }
"{" { return LBRACE; }
"}" { return RBRACE; }
"[" { return '['; }
"]" { return ']'; }
"." { return DOT; }

{float} {
    yylval.fval = atof(yytext);
    return FLOAT_LITERAL;
}

{int} {
    yylval.ival = atoi(yytext);
    return INT_LITERAL;
}

{string} {
    int len = yyleng;
    char *s = strdup(yytext + 1);
    s[len - 2] = 0;
    yylval.sval = s;
    return STRING_LITERAL;
}

{id} {
    yylval.sval = strdup(yytext);
    return IDENTIFIER;
}

. {
    fprintf(stderr, "Lexical error: unknown symbol '%s' at line %d\n",
            yytext, yylineno);
}

%%
