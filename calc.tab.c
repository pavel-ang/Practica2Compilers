/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "calc.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "symtab.h"

extern int yylineno;
extern int col;
int yylex();
void yyerror(const char *s);

%code requires {
    typedef struct {
        VarType type;
        char place[128];
    } CVal;
}
FILE *out = NULL;

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

#line 133 "calc.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "calc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_LITERAL = 3,                /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 4,              /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 5,             /* STRING_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 6,               /* BOOL_LITERAL  */
  YYSYMBOL_IDENTIFIER = 7,                 /* IDENTIFIER  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_FLOAT = 9,                      /* FLOAT  */
  YYSYMBOL_STRING = 10,                    /* STRING  */
  YYSYMBOL_BOOL = 11,                      /* BOOL  */
  YYSYMBOL_STRUCT = 12,                    /* STRUCT  */
  YYSYMBOL_REPEAT = 13,                    /* REPEAT  */
  YYSYMBOL_DO = 14,                        /* DO  */
  YYSYMBOL_DONE = 15,                      /* DONE  */
  YYSYMBOL_ASSIGN = 16,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 17,                      /* PLUS  */
  YYSYMBOL_MINUS = 18,                     /* MINUS  */
  YYSYMBOL_MULT = 19,                      /* MULT  */
  YYSYMBOL_DIV = 20,                       /* DIV  */
  YYSYMBOL_MOD = 21,                       /* MOD  */
  YYSYMBOL_POW = 22,                       /* POW  */
  YYSYMBOL_GT = 23,                        /* GT  */
  YYSYMBOL_LT = 24,                        /* LT  */
  YYSYMBOL_GE = 25,                        /* GE  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_EQ = 27,                        /* EQ  */
  YYSYMBOL_NEQ = 28,                       /* NEQ  */
  YYSYMBOL_AND = 29,                       /* AND  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_NOT = 31,                       /* NOT  */
  YYSYMBOL_LPAREN = 32,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 33,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 34,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 35,                    /* RBRACE  */
  YYSYMBOL_COMMA = 36,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 37,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 38,                       /* DOT  */
  YYSYMBOL_39_ = 39,                       /* '['  */
  YYSYMBOL_40_ = 40,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_stmt_list = 43,                 /* stmt_list  */
  YYSYMBOL_stmt = 44,                      /* stmt  */
  YYSYMBOL_assign = 45,                    /* assign  */
  YYSYMBOL_expr = 46,                      /* expr  */
  YYSYMBOL_or_expr = 47,                   /* or_expr  */
  YYSYMBOL_and_expr = 48,                  /* and_expr  */
  YYSYMBOL_not_expr = 49,                  /* not_expr  */
  YYSYMBOL_rel_expr = 50,                  /* rel_expr  */
  YYSYMBOL_add_expr = 51,                  /* add_expr  */
  YYSYMBOL_mul_expr = 52,                  /* mul_expr  */
  YYSYMBOL_pow_expr = 53,                  /* pow_expr  */
  YYSYMBOL_unary = 54,                     /* unary  */
  YYSYMBOL_primary = 55                    /* primary  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   98

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  42
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  86

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    93,    93,   100,   101,   105,   107,   114,   121,   128,
     155,   165,   183,   187,   188,   192,   193,   197,   198,   202,
     203,   204,   205,   206,   207,   208,   212,   213,   214,   215,
     216,   220,   221,   222,   223,   227,   228,   232,   236,   237,
     242,   247,   260
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT_LITERAL",
  "FLOAT_LITERAL", "STRING_LITERAL", "BOOL_LITERAL", "IDENTIFIER", "INT",
  "FLOAT", "STRING", "BOOL", "STRUCT", "REPEAT", "DO", "DONE", "ASSIGN",
  "PLUS", "MINUS", "MULT", "DIV", "MOD", "POW", "GT", "LT", "GE", "LE",
  "EQ", "NEQ", "AND", "OR", "NOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "COMMA", "SEMICOLON", "DOT", "'['", "']'", "$accept", "program",
  "stmt_list", "stmt", "assign", "expr", "or_expr", "and_expr", "not_expr",
  "rel_expr", "add_expr", "mul_expr", "pow_expr", "unary", "primary", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-26)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -26,     5,    41,   -26,   -26,   -26,   -10,    -6,    12,    24,
      57,    57,    24,    24,   -26,   -25,   -16,    -7,    -3,   -26,
      53,    35,   -12,   -26,     8,   -26,    24,    24,     4,    18,
      26,    32,    35,    35,   -26,    37,   -26,   -26,    24,    24,
      57,    57,    57,    57,    57,    57,    59,    59,    59,    59,
      59,    59,   -26,    11,    68,    83,    24,   -26,   -26,    -3,
     -26,    35,    35,    35,    35,    35,    35,   -12,   -12,   -26,
     -26,   -26,   -26,    71,    48,    50,    52,     7,    24,    56,
      58,   -26,   -26,   -26,   -26,   -26
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,    39,    40,    41,     0,     0,     0,
       0,     0,     0,     0,     3,     0,     0,    12,    14,    16,
      18,    25,    30,    34,    36,    37,     0,     0,     0,     0,
      41,     0,    26,    27,    17,     0,     5,     6,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    10,     0,     0,     0,     0,     4,    38,    13,
      15,    19,    21,    20,    22,    23,    24,    28,    29,    31,
      32,    33,    35,    42,     0,     0,     0,     0,     0,     0,
       0,    42,     9,    11,     7,     8
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -26,   -26,    39,   -26,   -26,    -9,   -26,    60,     1,   -26,
      -8,    21,    34,   -26,   -26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      31,    28,    32,    33,    35,     3,    26,    48,    49,    50,
       4,     5,    36,    34,     6,     7,     8,    52,    53,    29,
       9,    37,    82,    38,    10,    11,    39,     4,     5,    27,
      51,    30,    61,    62,    63,    64,    65,    66,    12,    13,
      60,    10,    11,    54,     4,     5,    57,    76,     6,     7,
       8,    73,    46,    47,     9,    12,    13,    55,    10,    11,
       4,     5,     4,     5,    30,    56,    30,    67,    68,    83,
      58,    74,    12,    13,    10,    11,    40,    41,    42,    43,
      44,    45,    69,    70,    71,    72,    75,    78,    79,    13,
      80,    13,    81,    84,     0,    85,    77,     0,    59
};

static const yytype_int8 yycheck[] =
{
       9,     7,    10,    11,    13,     0,    16,    19,    20,    21,
       3,     4,    37,    12,     7,     8,     9,    26,    27,     7,
      13,    37,    15,    30,    17,    18,    29,     3,     4,    39,
      22,     7,    40,    41,    42,    43,    44,    45,    31,    32,
      39,    17,    18,    39,     3,     4,    14,    56,     7,     8,
       9,    40,    17,    18,    13,    31,    32,    39,    17,    18,
       3,     4,     3,     4,     7,    39,     7,    46,    47,    78,
      33,     3,    31,    32,    17,    18,    23,    24,    25,    26,
      27,    28,    48,    49,    50,    51,     3,    16,    40,    32,
      40,    32,    40,    37,    -1,    37,    57,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    42,    43,     0,     3,     4,     7,     8,     9,    13,
      17,    18,    31,    32,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    16,    39,     7,     7,
       7,    46,    51,    51,    49,    46,    37,    37,    30,    29,
      23,    24,    25,    26,    27,    28,    17,    18,    19,    20,
      21,    22,    46,    46,    39,    39,    39,    14,    33,    48,
      49,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      53,    53,    53,    40,     3,     3,    46,    43,    16,    40,
      40,    40,    15,    46,    37,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    44,    44,
      45,    45,    46,    47,    47,    48,    48,    49,    49,    50,
      50,    50,    50,    50,    50,    50,    51,    51,    51,    51,
      51,    52,    52,    52,    52,    53,    53,    54,    55,    55,
      55,    55,    55
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     2,     6,     6,     5,
       3,     6,     1,     3,     1,     3,     1,     2,     1,     3,
       3,     3,     3,     3,     3,     1,     2,     2,     3,     3,
       1,     3,     3,     3,     1,     3,     1,     1,     3,     1,
       1,     1,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmt_list  */
#line 94 "calc.y"
    {
      fprintf(out, "HALT\n");
    }
#line 1229 "calc.tab.c"
    break;

  case 6: /* stmt: expr SEMICOLON  */
#line 108 "calc.y"
      {
          fprintf(out, "PARAM %s\n", (yyvsp[-1].cval).place);
          if ((yyvsp[-1].cval).type == TYPE_FLOAT) fprintf(out, "CALL PUTF, 1\n");
          else fprintf(out, "CALL PUTI, 1\n");
      }
#line 1239 "calc.tab.c"
    break;

  case 7: /* stmt: INT IDENTIFIER '[' INT_LITERAL ']' SEMICOLON  */
#line 115 "calc.y"
      {
          symtab_add_array((yyvsp[-4].sval), TYPE_INT, (yyvsp[-2].ival));
          Symbol *s = symtab_get((yyvsp[-4].sval));
          if (s) s->base_address = 25;
      }
#line 1249 "calc.tab.c"
    break;

  case 8: /* stmt: FLOAT IDENTIFIER '[' INT_LITERAL ']' SEMICOLON  */
#line 122 "calc.y"
      {
          symtab_add_array((yyvsp[-4].sval), TYPE_FLOAT, (yyvsp[-2].ival));
          Symbol *s = symtab_get((yyvsp[-4].sval));
          if (s) s->base_address = 25;
      }
#line 1259 "calc.tab.c"
    break;

  case 9: /* stmt: REPEAT expr DO stmt_list DONE  */
#line 129 "calc.y"
      {
          if ((yyvsp[-3].cval).type != TYPE_INT) {
              fprintf(stderr, "Semantic error: repeat requires integer expression at line %d\n", yylineno);
          } else {
              char *Lstart = new_label();
              char *Lend = new_label();
              char *ctr = new_temp();

              fprintf(out, "%s := %s\n", ctr, (yyvsp[-3].cval).place);
              
              fprintf(out, "%s:\n", Lstart);
              
              fprintf(out, "IFLE %s 0 GOTO %s\n", ctr, Lend);
              
              fprintf(out, "%s := SUBI %s 1\n", ctr, ctr);
              
              fprintf(out, "GOTO %s\n", Lstart);
              
              fprintf(out, "%s:\n", Lend);
              
              free(Lstart); free(Lend); free(ctr);
          }
      }
#line 1287 "calc.tab.c"
    break;

  case 10: /* assign: IDENTIFIER ASSIGN expr  */
#line 156 "calc.y"
      {
          Symbol *sym = symtab_get((yyvsp[-2].sval));
          if (!sym) {
              symtab_add((yyvsp[-2].sval), (yyvsp[0].cval).type == TYPE_FLOAT ? TYPE_FLOAT : TYPE_INT);
              sym = symtab_get((yyvsp[-2].sval));
          }
          fprintf(out, "%s := %s\n", (yyvsp[-2].sval), (yyvsp[0].cval).place);
      }
#line 1300 "calc.tab.c"
    break;

  case 11: /* assign: IDENTIFIER '[' expr ']' ASSIGN expr  */
#line 166 "calc.y"
      {
          Symbol *sym = symtab_get((yyvsp[-5].sval));
          if (!sym || !sym->is_array) {
              fprintf(stderr, "Semantic error: undeclared array '%s' at line %d\n", (yyvsp[-5].sval), yylineno);
          } else {
              char *addr = new_temp();
              fprintf(out, "%s := ADDI %d %s\n", addr, sym->base_address, (yyvsp[-3].cval).place);
              
              if ((yyvsp[0].cval).type == TYPE_FLOAT) fprintf(out, "STOREF %s %s\n", addr, (yyvsp[0].cval).place);
              else fprintf(out, "STOREI %s %s\n", addr, (yyvsp[0].cval).place);
              
              free(addr);
          }
      }
#line 1319 "calc.tab.c"
    break;

  case 12: /* expr: or_expr  */
#line 183 "calc.y"
              { (yyval.cval) = (yyvsp[0].cval); }
#line 1325 "calc.tab.c"
    break;

  case 13: /* or_expr: or_expr OR and_expr  */
#line 187 "calc.y"
                          { (yyval.cval) = (yyvsp[-2].cval); }
#line 1331 "calc.tab.c"
    break;

  case 14: /* or_expr: and_expr  */
#line 188 "calc.y"
               { (yyval.cval) = (yyvsp[0].cval); }
#line 1337 "calc.tab.c"
    break;

  case 15: /* and_expr: and_expr AND not_expr  */
#line 192 "calc.y"
                            { (yyval.cval) = (yyvsp[-2].cval); }
#line 1343 "calc.tab.c"
    break;

  case 16: /* and_expr: not_expr  */
#line 193 "calc.y"
               { (yyval.cval) = (yyvsp[0].cval); }
#line 1349 "calc.tab.c"
    break;

  case 17: /* not_expr: NOT not_expr  */
#line 197 "calc.y"
                   { (yyval.cval) = (yyvsp[0].cval); }
#line 1355 "calc.tab.c"
    break;

  case 18: /* not_expr: rel_expr  */
#line 198 "calc.y"
               { (yyval.cval) = (yyvsp[0].cval); }
#line 1361 "calc.tab.c"
    break;

  case 19: /* rel_expr: rel_expr GT add_expr  */
#line 202 "calc.y"
                           { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "GTI", "GTF", ">"); }
#line 1367 "calc.tab.c"
    break;

  case 20: /* rel_expr: rel_expr GE add_expr  */
#line 203 "calc.y"
                           { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "GEI", "GEF", ">="); }
#line 1373 "calc.tab.c"
    break;

  case 21: /* rel_expr: rel_expr LT add_expr  */
#line 204 "calc.y"
                           { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "LTI", "LTF", "<"); }
#line 1379 "calc.tab.c"
    break;

  case 22: /* rel_expr: rel_expr LE add_expr  */
#line 205 "calc.y"
                           { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "LEI", "LEF", "<="); }
#line 1385 "calc.tab.c"
    break;

  case 23: /* rel_expr: rel_expr EQ add_expr  */
#line 206 "calc.y"
                           { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "EQI", "EQF", "=="); }
#line 1391 "calc.tab.c"
    break;

  case 24: /* rel_expr: rel_expr NEQ add_expr  */
#line 207 "calc.y"
                            { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "NEQI", "NEQF", "!="); }
#line 1397 "calc.tab.c"
    break;

  case 25: /* rel_expr: add_expr  */
#line 208 "calc.y"
               { (yyval.cval) = (yyvsp[0].cval); }
#line 1403 "calc.tab.c"
    break;

  case 26: /* add_expr: PLUS add_expr  */
#line 212 "calc.y"
                    { (yyval.cval) = (yyvsp[0].cval); }
#line 1409 "calc.tab.c"
    break;

  case 27: /* add_expr: MINUS add_expr  */
#line 213 "calc.y"
                     { (yyval.cval) = gen_unary_minus((yyvsp[0].cval)); }
#line 1415 "calc.tab.c"
    break;

  case 28: /* add_expr: add_expr PLUS mul_expr  */
#line 214 "calc.y"
                             { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "ADDI", "ADDF", "+"); }
#line 1421 "calc.tab.c"
    break;

  case 29: /* add_expr: add_expr MINUS mul_expr  */
#line 215 "calc.y"
                              { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "SUBI", "SUBF", "-"); }
#line 1427 "calc.tab.c"
    break;

  case 30: /* add_expr: mul_expr  */
#line 216 "calc.y"
               { (yyval.cval) = (yyvsp[0].cval); }
#line 1433 "calc.tab.c"
    break;

  case 31: /* mul_expr: mul_expr MULT pow_expr  */
#line 220 "calc.y"
                             { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "MULI", "MULF", "*"); }
#line 1439 "calc.tab.c"
    break;

  case 32: /* mul_expr: mul_expr DIV pow_expr  */
#line 221 "calc.y"
                            { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "DIVI", "DIVF", "/"); }
#line 1445 "calc.tab.c"
    break;

  case 33: /* mul_expr: mul_expr MOD pow_expr  */
#line 222 "calc.y"
                            { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "MODI", "MODF", "%"); }
#line 1451 "calc.tab.c"
    break;

  case 34: /* mul_expr: pow_expr  */
#line 223 "calc.y"
               { (yyval.cval) = (yyvsp[0].cval); }
#line 1457 "calc.tab.c"
    break;

  case 35: /* pow_expr: unary POW pow_expr  */
#line 227 "calc.y"
                         { (yyval.cval) = gen_binop((yyvsp[-2].cval), (yyvsp[0].cval), "POWI", "POWF", "**"); }
#line 1463 "calc.tab.c"
    break;

  case 36: /* pow_expr: unary  */
#line 228 "calc.y"
            { (yyval.cval) = (yyvsp[0].cval); }
#line 1469 "calc.tab.c"
    break;

  case 37: /* unary: primary  */
#line 232 "calc.y"
              { (yyval.cval) = (yyvsp[0].cval); }
#line 1475 "calc.tab.c"
    break;

  case 38: /* primary: LPAREN expr RPAREN  */
#line 236 "calc.y"
                         { (yyval.cval) = (yyvsp[-1].cval); }
#line 1481 "calc.tab.c"
    break;

  case 39: /* primary: INT_LITERAL  */
#line 237 "calc.y"
                  { 
          CVal v; v.type = TYPE_INT; 
          snprintf(v.place, sizeof(v.place), "%d", (yyvsp[0].ival)); 
          (yyval.cval) = v; 
      }
#line 1491 "calc.tab.c"
    break;

  case 40: /* primary: FLOAT_LITERAL  */
#line 242 "calc.y"
                    { 
          CVal v; v.type = TYPE_FLOAT; 
          snprintf(v.place, sizeof(v.place), "%lf", (yyvsp[0].fval)); 
          (yyval.cval) = v; 
      }
#line 1501 "calc.tab.c"
    break;

  case 41: /* primary: IDENTIFIER  */
#line 247 "calc.y"
                 {
          CVal v;
          Symbol *s = symtab_get((yyvsp[0].sval));
          if (!s) {
              fprintf(stderr, "Semantic error: undeclared variable '%s' at line %d\n", (yyvsp[0].sval), yylineno);
              v.type = TYPE_INT; strcpy(v.place, "0");
          } else {
              v.type = s->type;
              strncpy(v.place, (yyvsp[0].sval), sizeof(v.place)-1);
              v.place[sizeof(v.place)-1]=0;
          }
          (yyval.cval) = v;
      }
#line 1519 "calc.tab.c"
    break;

  case 42: /* primary: IDENTIFIER '[' expr ']'  */
#line 260 "calc.y"
                              {
          CVal v;
          Symbol *s = symtab_get((yyvsp[-3].sval));
          if (!s || !s->is_array) {
              fprintf(stderr, "Semantic error: undeclared array '%s' at line %d\n", (yyvsp[-3].sval), yylineno);
              v.type = TYPE_INT; strcpy(v.place, "0");
          } else {
              char *addr = new_temp();
              fprintf(out, "%s := ADDI %d %s\n", addr, s->base_address, (yyvsp[-1].cval).place);
              
              char *valtmp = new_temp();
              if (s->type == TYPE_FLOAT) fprintf(out, "%s := LOADF %s\n", valtmp, addr);
              else fprintf(out, "%s := LOADI %s\n", valtmp, addr);
              
              v.type = s->type;
              copy_place(v.place, valtmp);
              free(addr); free(valtmp);
          }
          (yyval.cval) = v;
      }
#line 1544 "calc.tab.c"
    break;


#line 1548 "calc.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 282 "calc.y"


void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d, col %d: %s\n", yylineno, col, s);
}

int main(int argc, char **argv) {
    out = stdout;
    symtab_init();
    yyparse();
    return 0;
}
