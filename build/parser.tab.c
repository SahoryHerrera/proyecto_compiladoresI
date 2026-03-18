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
#line 1 "src/parser/parser.y"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

int  yylex();
void yyerror(const char* s);

extern int   yylineno;
extern int   yycol;
extern FILE* yyin;

/* Incluir AST solo en el .c, no se propaga al .h */
#include "ast.hpp"

ProgramNode* ast_root = nullptr;

#line 92 "build/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_TYPE = 4,                       /* TYPE  */
  YYSYMBOL_INT_LIT = 5,                    /* INT_LIT  */
  YYSYMBOL_FLOAT_LIT = 6,                  /* FLOAT_LIT  */
  YYSYMBOL_STR_LIT = 7,                    /* STR_LIT  */
  YYSYMBOL_CHAR_LIT = 8,                   /* CHAR_LIT  */
  YYSYMBOL_BOOL_LIT = 9,                   /* BOOL_LIT  */
  YYSYMBOL_FN = 10,                        /* FN  */
  YYSYMBOL_LET = 11,                       /* LET  */
  YYSYMBOL_MUT = 12,                       /* MUT  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_IN = 17,                        /* IN  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_PRINTLN_MACRO = 19,             /* PRINTLN_MACRO  */
  YYSYMBOL_PLUS = 20,                      /* PLUS  */
  YYSYMBOL_MINUS = 21,                     /* MINUS  */
  YYSYMBOL_MUL = 22,                       /* MUL  */
  YYSYMBOL_DIV = 23,                       /* DIV  */
  YYSYMBOL_MOD = 24,                       /* MOD  */
  YYSYMBOL_ASSIGN = 25,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 26,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 27,              /* MINUS_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 28,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 29,                /* DIV_ASSIGN  */
  YYSYMBOL_EQ = 30,                        /* EQ  */
  YYSYMBOL_NEQ = 31,                       /* NEQ  */
  YYSYMBOL_LT = 32,                        /* LT  */
  YYSYMBOL_GT = 33,                        /* GT  */
  YYSYMBOL_LE = 34,                        /* LE  */
  YYSYMBOL_GE = 35,                        /* GE  */
  YYSYMBOL_AND = 36,                       /* AND  */
  YYSYMBOL_OR = 37,                        /* OR  */
  YYSYMBOL_NOT = 38,                       /* NOT  */
  YYSYMBOL_LPAREN = 39,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 40,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 41,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 42,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 43,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 44,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 45,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 46,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 47,                     /* COLON  */
  YYSYMBOL_ARROW = 48,                     /* ARROW  */
  YYSYMBOL_DOT_DOT = 49,                   /* DOT_DOT  */
  YYSYMBOL_UMINUS = 50,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_function = 53,                  /* function  */
  YYSYMBOL_ret_type = 54,                  /* ret_type  */
  YYSYMBOL_params = 55,                    /* params  */
  YYSYMBOL_param_list = 56,                /* param_list  */
  YYSYMBOL_param = 57,                     /* param  */
  YYSYMBOL_block = 58,                     /* block  */
  YYSYMBOL_statements = 59,                /* statements  */
  YYSYMBOL_statement = 60,                 /* statement  */
  YYSYMBOL_opt_mut = 61,                   /* opt_mut  */
  YYSYMBOL_opt_type = 62,                  /* opt_type  */
  YYSYMBOL_let_stmt = 63,                  /* let_stmt  */
  YYSYMBOL_assign_stmt = 64,               /* assign_stmt  */
  YYSYMBOL_if_stmt = 65,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 66,                /* while_stmt  */
  YYSYMBOL_for_stmt = 67,                  /* for_stmt  */
  YYSYMBOL_return_stmt = 68,               /* return_stmt  */
  YYSYMBOL_println_stmt = 69,              /* println_stmt  */
  YYSYMBOL_expr_stmt = 70,                 /* expr_stmt  */
  YYSYMBOL_expression = 71,                /* expression  */
  YYSYMBOL_call = 72,                      /* call  */
  YYSYMBOL_args = 73,                      /* args  */
  YYSYMBOL_arg_list = 74                   /* arg_list  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   417

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    67,    67,    72,    82,    96,    97,    98,   102,   103,
     107,   113,   121,   123,   129,   130,   135,   141,   149,   150,
     151,   152,   153,   154,   155,   156,   160,   161,   165,   166,
     167,   171,   184,   189,   195,   201,   207,   216,   221,   227,
     238,   246,   257,   259,   264,   272,   277,   279,   281,   283,
     285,   287,   289,   291,   293,   295,   297,   299,   301,   303,
     305,   307,   309,   311,   313,   315,   317,   319,   321,   326,
     334,   335,   339,   345
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "TYPE",
  "INT_LIT", "FLOAT_LIT", "STR_LIT", "CHAR_LIT", "BOOL_LIT", "FN", "LET",
  "MUT", "IF", "ELSE", "WHILE", "FOR", "IN", "RETURN", "PRINTLN_MACRO",
  "PLUS", "MINUS", "MUL", "DIV", "MOD", "ASSIGN", "PLUS_ASSIGN",
  "MINUS_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "EQ", "NEQ", "LT", "GT",
  "LE", "GE", "AND", "OR", "NOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "COMMA", "SEMICOLON", "COLON", "ARROW",
  "DOT_DOT", "UMINUS", "$accept", "program", "function", "ret_type",
  "params", "param_list", "param", "block", "statements", "statement",
  "opt_mut", "opt_type", "let_stmt", "assign_stmt", "if_stmt",
  "while_stmt", "for_stmt", "return_stmt", "println_stmt", "expr_stmt",
  "expression", "call", "args", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-84)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -84,     8,   -84,     1,   -84,   -30,    17,   -35,   -21,    27,
     -84,    25,   -14,    17,   -84,   -84,    59,    33,   -84,   -84,
     -84,    98,   -12,   -84,   -84,   -84,   -84,   -84,    63,   117,
     117,    73,    52,    46,   117,   117,   117,    44,    98,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   111,   -84,
     117,   117,   117,   117,   117,   117,   -84,    84,    49,   255,
     277,    75,   -84,   129,   117,   -84,   -84,   321,   -84,   -84,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   -84,   147,   165,   183,   201,   219,   342,
      53,    50,    65,    98,    98,   117,   -84,    54,   -84,     9,
       9,   -84,   -84,   -84,   382,   382,    16,    16,    16,    16,
     377,   360,   -84,   -84,   -84,   -84,   -84,   -84,   117,    61,
      72,    58,    66,    47,    64,   342,   -84,   -84,   117,   101,
     -84,   117,   -84,   237,   -11,   299,   -84,    98,   -84,    98,
      76,    79,   -84,   -84
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     3,     0,     8,     0,     0,     9,
      10,     0,     5,     0,    13,    12,     0,     0,    11,     7,
       6,    14,    68,    63,    64,    65,    66,    67,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,    16,
      18,    19,    20,    21,    22,    23,    24,    25,     0,    62,
       0,     0,     0,     0,     0,    70,    27,     0,    68,     0,
       0,     0,    42,     0,    70,    60,    59,     0,     4,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,     0,     0,     0,     0,    72,
       0,    71,    28,    14,    14,     0,    43,     0,    61,    46,
      47,    48,    49,    50,    55,    56,    51,    52,    53,    54,
      57,    58,    32,    33,    34,    35,    36,    69,     0,     0,
       0,     0,     0,     0,     0,    73,    30,    29,     0,    37,
      40,     0,    44,     0,     0,     0,    31,    14,    39,    14,
       0,     0,    38,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -84,   -84,   -84,   -84,   114,   -83,   -84,    90,
     -84,   -84,   -84,   -84,    -5,   -84,   -84,   -84,   -84,   -84,
     -29,   -84,    94,   -84
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     4,    17,     8,     9,    10,    37,    38,    39,
      57,   120,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    90,    91
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,    60,    29,    63,     5,    65,    66,    67,     2,     6,
     121,   122,    11,    50,    51,    52,    53,    54,     3,    12,
       7,    84,    85,    86,    87,    88,    89,    55,    14,    15,
     137,    72,    73,    74,    16,    89,    70,    71,    72,    73,
      74,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   140,    58,   141,    23,    24,    25,
      26,    27,    19,    20,   126,   127,   123,    70,    71,    72,
      73,    74,    13,    34,    21,    56,    61,    75,    76,    77,
      78,    79,    80,    81,    82,    64,    68,    92,    55,   125,
      35,    36,    95,   117,   124,   118,   131,   128,    62,   133,
     129,    22,   135,    23,    24,    25,    26,    27,   130,    28,
     132,    29,   119,    30,    31,   134,    32,    33,   142,    34,
      58,   143,    23,    24,    25,    26,    27,    18,    69,   138,
       0,    70,    71,    72,    73,    74,    35,    36,    34,     0,
       0,    75,    76,    77,    78,    79,    80,    81,    82,    70,
      71,    72,    73,    74,     0,    35,    36,    83,    97,    75,
      76,    77,    78,    79,    80,    81,    82,    70,    71,    72,
      73,    74,     0,     0,     0,    96,     0,    75,    76,    77,
      78,    79,    80,    81,    82,    70,    71,    72,    73,    74,
       0,     0,     0,   112,     0,    75,    76,    77,    78,    79,
      80,    81,    82,    70,    71,    72,    73,    74,     0,     0,
       0,   113,     0,    75,    76,    77,    78,    79,    80,    81,
      82,    70,    71,    72,    73,    74,     0,     0,     0,   114,
       0,    75,    76,    77,    78,    79,    80,    81,    82,    70,
      71,    72,    73,    74,     0,     0,     0,   115,     0,    75,
      76,    77,    78,    79,    80,    81,    82,    70,    71,    72,
      73,    74,     0,     0,     0,   116,     0,    75,    76,    77,
      78,    79,    80,    81,    82,    70,    71,    72,    73,    74,
       0,     0,     0,   136,     0,    75,    76,    77,    78,    79,
      80,    81,    82,     0,     0,     0,    93,    70,    71,    72,
      73,    74,     0,     0,     0,     0,     0,    75,    76,    77,
      78,    79,    80,    81,    82,     0,     0,     0,    94,    70,
      71,    72,    73,    74,     0,     0,     0,     0,     0,    75,
      76,    77,    78,    79,    80,    81,    82,     0,     0,     0,
     139,    70,    71,    72,    73,    74,     0,     0,     0,     0,
       0,    75,    76,    77,    78,    79,    80,    81,    82,     0,
       0,    98,    70,    71,    72,    73,    74,     0,     0,     0,
       0,     0,    75,    76,    77,    78,    79,    80,    81,    82,
      70,    71,    72,    73,    74,     0,     0,     0,     0,     0,
      75,    76,    77,    78,    79,    80,    81,    70,    71,    72,
      73,    74,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     0,    77,    78,    79,    80
};

static const yytype_int16 yycheck[] =
{
      29,    30,    13,    32,     3,    34,    35,    36,     0,    39,
      93,    94,    47,    25,    26,    27,    28,    29,    10,    40,
       3,    50,    51,    52,    53,    54,    55,    39,     3,     4,
      41,    22,    23,    24,    48,    64,    20,    21,    22,    23,
      24,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,   137,     3,   139,     5,     6,     7,
       8,     9,     3,     4,     3,     4,    95,    20,    21,    22,
      23,    24,    45,    21,    41,    12,     3,    30,    31,    32,
      33,    34,    35,    36,    37,    39,    42,     3,    39,   118,
      38,    39,    17,    40,    40,    45,    49,    25,    46,   128,
      42,     3,   131,     5,     6,     7,     8,     9,    42,    11,
      46,    13,    47,    15,    16,    14,    18,    19,    42,    21,
       3,    42,     5,     6,     7,     8,     9,    13,    38,   134,
      -1,    20,    21,    22,    23,    24,    38,    39,    21,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    20,
      21,    22,    23,    24,    -1,    38,    39,    46,    64,    30,
      31,    32,    33,    34,    35,    36,    37,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    46,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    46,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    46,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    20,    21,    22,    23,    24,    -1,    -1,    -1,    46,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    46,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    46,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    46,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    41,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    41,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      41,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    40,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    20,    21,    22,
      23,    24,    20,    21,    22,    23,    24,    30,    31,    32,
      33,    34,    35,    -1,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,     0,    10,    53,     3,    39,     3,    55,    56,
      57,    47,    40,    45,     3,     4,    48,    54,    57,     3,
       4,    41,     3,     5,     6,     7,     8,     9,    11,    13,
      15,    16,    18,    19,    21,    38,    39,    58,    59,    60,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      25,    26,    27,    28,    29,    39,    12,    61,     3,    71,
      71,     3,    46,    71,    39,    71,    71,    71,    42,    60,
      20,    21,    22,    23,    24,    30,    31,    32,    33,    34,
      35,    36,    37,    46,    71,    71,    71,    71,    71,    71,
      73,    74,     3,    41,    41,    17,    46,    73,    40,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    46,    46,    46,    46,    46,    40,    45,    47,
      62,    58,    58,    71,    40,    71,     3,     4,    25,    42,
      42,    49,    46,    71,    14,    71,    46,    41,    65,    41,
      58,    58,    42,    42
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    52,    53,    54,    54,    54,    55,    55,
      56,    56,    57,    57,    58,    58,    59,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    61,    61,    62,    62,
      62,    63,    64,    64,    64,    64,    64,    65,    65,    65,
      66,    67,    68,    68,    69,    70,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    72,
      73,    73,    74,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     9,     0,     2,     2,     0,     1,
       1,     3,     3,     3,     0,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     0,     2,
       2,     7,     4,     4,     4,     4,     4,     5,     9,     7,
       5,     9,     2,     3,     5,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     4,
       0,     1,     1,     3
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
  case 2: /* program: %empty  */
#line 67 "src/parser/parser.y"
        {
            ProgramNode* p = new ProgramNode();
            ast_root = p;
            (yyval.node) = p;
        }
#line 1307 "build/parser.tab.c"
    break;

  case 3: /* program: program function  */
#line 73 "src/parser/parser.y"
        {
            ProgramNode* p = static_cast<ProgramNode*>((yyvsp[-1].node));
            p->add(static_cast<FunctionNode*>((yyvsp[0].node)));
            ast_root = p;
            (yyval.node) = p;
        }
#line 1318 "build/parser.tab.c"
    break;

  case 4: /* function: FN IDENTIFIER LPAREN params RPAREN ret_type LBRACE block RBRACE  */
#line 83 "src/parser/parser.y"
        {
            string name = (yyvsp[-7].str_val);
            string ret  = (yyvsp[-3].str_val) ? string((yyvsp[-3].str_val)) : string("");
            (yyval.node) = new FunctionNode(name,
                     static_cast<ParamListNode*>((yyvsp[-5].node)),
                     ret,
                     static_cast<BlockNode*>((yyvsp[-1].node)));
            free((yyvsp[-7].str_val));
            if ((yyvsp[-3].str_val)) free((yyvsp[-3].str_val));
        }
#line 1333 "build/parser.tab.c"
    break;

  case 5: /* ret_type: %empty  */
#line 96 "src/parser/parser.y"
                       { (yyval.str_val) = nullptr; }
#line 1339 "build/parser.tab.c"
    break;

  case 6: /* ret_type: ARROW TYPE  */
#line 97 "src/parser/parser.y"
                       { (yyval.str_val) = (yyvsp[0].str_val);      }
#line 1345 "build/parser.tab.c"
    break;

  case 7: /* ret_type: ARROW IDENTIFIER  */
#line 98 "src/parser/parser.y"
                       { (yyval.str_val) = (yyvsp[0].str_val);      }
#line 1351 "build/parser.tab.c"
    break;

  case 8: /* params: %empty  */
#line 102 "src/parser/parser.y"
                  { (yyval.node) = new ParamListNode(); }
#line 1357 "build/parser.tab.c"
    break;

  case 9: /* params: param_list  */
#line 103 "src/parser/parser.y"
                  { (yyval.node) = (yyvsp[0].node);                  }
#line 1363 "build/parser.tab.c"
    break;

  case 10: /* param_list: param  */
#line 108 "src/parser/parser.y"
        {
            ParamListNode* pl = new ParamListNode();
            pl->add(static_cast<ParamNode*>((yyvsp[0].node)));
            (yyval.node) = pl;
        }
#line 1373 "build/parser.tab.c"
    break;

  case 11: /* param_list: param_list COMMA param  */
#line 114 "src/parser/parser.y"
        {
            static_cast<ParamListNode*>((yyvsp[-2].node))->add(static_cast<ParamNode*>((yyvsp[0].node)));
            (yyval.node) = (yyvsp[-2].node);
        }
#line 1382 "build/parser.tab.c"
    break;

  case 12: /* param: IDENTIFIER COLON TYPE  */
#line 122 "src/parser/parser.y"
        { (yyval.node) = new ParamNode(string((yyvsp[-2].str_val)), string((yyvsp[0].str_val))); free((yyvsp[-2].str_val)); free((yyvsp[0].str_val)); }
#line 1388 "build/parser.tab.c"
    break;

  case 13: /* param: IDENTIFIER COLON IDENTIFIER  */
#line 124 "src/parser/parser.y"
        { (yyval.node) = new ParamNode(string((yyvsp[-2].str_val)), string((yyvsp[0].str_val))); free((yyvsp[-2].str_val)); free((yyvsp[0].str_val)); }
#line 1394 "build/parser.tab.c"
    break;

  case 14: /* block: %empty  */
#line 129 "src/parser/parser.y"
        { (yyval.node) = new BlockNode(new StatementListNode()); }
#line 1400 "build/parser.tab.c"
    break;

  case 15: /* block: statements  */
#line 131 "src/parser/parser.y"
        { (yyval.node) = new BlockNode(static_cast<StatementListNode*>((yyvsp[0].node))); }
#line 1406 "build/parser.tab.c"
    break;

  case 16: /* statements: statement  */
#line 136 "src/parser/parser.y"
        {
            StatementListNode* sl = new StatementListNode();
            if ((yyvsp[0].node)) sl->add(static_cast<StmtNode*>((yyvsp[0].node)));
            (yyval.node) = sl;
        }
#line 1416 "build/parser.tab.c"
    break;

  case 17: /* statements: statements statement  */
#line 142 "src/parser/parser.y"
        {
            if ((yyvsp[0].node)) static_cast<StatementListNode*>((yyvsp[-1].node))->add(static_cast<StmtNode*>((yyvsp[0].node)));
            (yyval.node) = (yyvsp[-1].node);
        }
#line 1425 "build/parser.tab.c"
    break;

  case 18: /* statement: let_stmt  */
#line 149 "src/parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1431 "build/parser.tab.c"
    break;

  case 19: /* statement: assign_stmt  */
#line 150 "src/parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1437 "build/parser.tab.c"
    break;

  case 20: /* statement: if_stmt  */
#line 151 "src/parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1443 "build/parser.tab.c"
    break;

  case 21: /* statement: while_stmt  */
#line 152 "src/parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1449 "build/parser.tab.c"
    break;

  case 22: /* statement: for_stmt  */
#line 153 "src/parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1455 "build/parser.tab.c"
    break;

  case 23: /* statement: return_stmt  */
#line 154 "src/parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1461 "build/parser.tab.c"
    break;

  case 24: /* statement: println_stmt  */
#line 155 "src/parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1467 "build/parser.tab.c"
    break;

  case 25: /* statement: expr_stmt  */
#line 156 "src/parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1473 "build/parser.tab.c"
    break;

  case 26: /* opt_mut: %empty  */
#line 160 "src/parser/parser.y"
                  { (yyval.str_val) = nullptr;       }
#line 1479 "build/parser.tab.c"
    break;

  case 27: /* opt_mut: MUT  */
#line 161 "src/parser/parser.y"
                  { (yyval.str_val) = strdup("mut"); }
#line 1485 "build/parser.tab.c"
    break;

  case 28: /* opt_type: %empty  */
#line 165 "src/parser/parser.y"
                       { (yyval.str_val) = nullptr; }
#line 1491 "build/parser.tab.c"
    break;

  case 29: /* opt_type: COLON TYPE  */
#line 166 "src/parser/parser.y"
                       { (yyval.str_val) = (yyvsp[0].str_val);      }
#line 1497 "build/parser.tab.c"
    break;

  case 30: /* opt_type: COLON IDENTIFIER  */
#line 167 "src/parser/parser.y"
                       { (yyval.str_val) = (yyvsp[0].str_val);      }
#line 1503 "build/parser.tab.c"
    break;

  case 31: /* let_stmt: LET opt_mut IDENTIFIER opt_type ASSIGN expression SEMICOLON  */
#line 172 "src/parser/parser.y"
        {
            string name = (yyvsp[-4].str_val);
            string type = (yyvsp[-3].str_val) ? string((yyvsp[-3].str_val)) : string("");
            if ((yyvsp[-5].str_val)) name = "mut " + name;
            (yyval.node) = new LetNode(name, type, static_cast<ExprNode*>((yyvsp[-1].node)));
            free((yyvsp[-4].str_val));
            if ((yyvsp[-5].str_val)) free((yyvsp[-5].str_val));
            if ((yyvsp[-3].str_val)) free((yyvsp[-3].str_val));
        }
#line 1517 "build/parser.tab.c"
    break;

  case 32: /* assign_stmt: IDENTIFIER ASSIGN expression SEMICOLON  */
#line 185 "src/parser/parser.y"
        {
            (yyval.node) = new AssignNode(string((yyvsp[-3].str_val)), static_cast<ExprNode*>((yyvsp[-1].node)));
            free((yyvsp[-3].str_val));
        }
#line 1526 "build/parser.tab.c"
    break;

  case 33: /* assign_stmt: IDENTIFIER PLUS_ASSIGN expression SEMICOLON  */
#line 190 "src/parser/parser.y"
        {
            ExprNode* id = new IdentifierNode(string((yyvsp[-3].str_val)));
            (yyval.node) = new AssignNode(string((yyvsp[-3].str_val)), new BinaryOpNode("+", id, static_cast<ExprNode*>((yyvsp[-1].node))));
            free((yyvsp[-3].str_val));
        }
#line 1536 "build/parser.tab.c"
    break;

  case 34: /* assign_stmt: IDENTIFIER MINUS_ASSIGN expression SEMICOLON  */
#line 196 "src/parser/parser.y"
        {
            ExprNode* id = new IdentifierNode(string((yyvsp[-3].str_val)));
            (yyval.node) = new AssignNode(string((yyvsp[-3].str_val)), new BinaryOpNode("-", id, static_cast<ExprNode*>((yyvsp[-1].node))));
            free((yyvsp[-3].str_val));
        }
#line 1546 "build/parser.tab.c"
    break;

  case 35: /* assign_stmt: IDENTIFIER MUL_ASSIGN expression SEMICOLON  */
#line 202 "src/parser/parser.y"
        {
            ExprNode* id = new IdentifierNode(string((yyvsp[-3].str_val)));
            (yyval.node) = new AssignNode(string((yyvsp[-3].str_val)), new BinaryOpNode("*", id, static_cast<ExprNode*>((yyvsp[-1].node))));
            free((yyvsp[-3].str_val));
        }
#line 1556 "build/parser.tab.c"
    break;

  case 36: /* assign_stmt: IDENTIFIER DIV_ASSIGN expression SEMICOLON  */
#line 208 "src/parser/parser.y"
        {
            ExprNode* id = new IdentifierNode(string((yyvsp[-3].str_val)));
            (yyval.node) = new AssignNode(string((yyvsp[-3].str_val)), new BinaryOpNode("/", id, static_cast<ExprNode*>((yyvsp[-1].node))));
            free((yyvsp[-3].str_val));
        }
#line 1566 "build/parser.tab.c"
    break;

  case 37: /* if_stmt: IF expression LBRACE block RBRACE  */
#line 217 "src/parser/parser.y"
        {
            (yyval.node) = new IfNode(static_cast<ExprNode*>((yyvsp[-3].node)),
                            static_cast<BlockNode*>((yyvsp[-1].node)), nullptr);
        }
#line 1575 "build/parser.tab.c"
    break;

  case 38: /* if_stmt: IF expression LBRACE block RBRACE ELSE LBRACE block RBRACE  */
#line 222 "src/parser/parser.y"
        {
            (yyval.node) = new IfNode(static_cast<ExprNode*>((yyvsp[-7].node)),
                            static_cast<BlockNode*>((yyvsp[-5].node)),
                            static_cast<BlockNode*>((yyvsp[-1].node)));
        }
#line 1585 "build/parser.tab.c"
    break;

  case 39: /* if_stmt: IF expression LBRACE block RBRACE ELSE if_stmt  */
#line 228 "src/parser/parser.y"
        {
            StatementListNode* sl = new StatementListNode();
            sl->add(static_cast<StmtNode*>((yyvsp[0].node)));
            (yyval.node) = new IfNode(static_cast<ExprNode*>((yyvsp[-5].node)),
                            static_cast<BlockNode*>((yyvsp[-3].node)),
                            new BlockNode(sl));
        }
#line 1597 "build/parser.tab.c"
    break;

  case 40: /* while_stmt: WHILE expression LBRACE block RBRACE  */
#line 239 "src/parser/parser.y"
        {
            (yyval.node) = new WhileNode(static_cast<ExprNode*>((yyvsp[-3].node)),
                               static_cast<BlockNode*>((yyvsp[-1].node)));
        }
#line 1606 "build/parser.tab.c"
    break;

  case 41: /* for_stmt: FOR IDENTIFIER IN expression DOT_DOT expression LBRACE block RBRACE  */
#line 247 "src/parser/parser.y"
        {
            (yyval.node) = new ForNode(string((yyvsp[-7].str_val)),
                             static_cast<ExprNode*>((yyvsp[-5].node)),
                             static_cast<ExprNode*>((yyvsp[-3].node)),
                             static_cast<BlockNode*>((yyvsp[-1].node)));
            free((yyvsp[-7].str_val));
        }
#line 1618 "build/parser.tab.c"
    break;

  case 42: /* return_stmt: RETURN SEMICOLON  */
#line 258 "src/parser/parser.y"
        { (yyval.node) = new ReturnNode(nullptr); }
#line 1624 "build/parser.tab.c"
    break;

  case 43: /* return_stmt: RETURN expression SEMICOLON  */
#line 260 "src/parser/parser.y"
        { (yyval.node) = new ReturnNode(static_cast<ExprNode*>((yyvsp[-1].node))); }
#line 1630 "build/parser.tab.c"
    break;

  case 44: /* println_stmt: PRINTLN_MACRO LPAREN args RPAREN SEMICOLON  */
#line 265 "src/parser/parser.y"
        {
            (yyval.node) = new ExprStmtNode(
                     new CallNode("println!", static_cast<ArgListNode*>((yyvsp[-2].node))));
        }
#line 1639 "build/parser.tab.c"
    break;

  case 45: /* expr_stmt: expression SEMICOLON  */
#line 273 "src/parser/parser.y"
        { (yyval.node) = new ExprStmtNode(static_cast<ExprNode*>((yyvsp[-1].node))); }
#line 1645 "build/parser.tab.c"
    break;

  case 46: /* expression: expression PLUS expression  */
#line 278 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("+", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1651 "build/parser.tab.c"
    break;

  case 47: /* expression: expression MINUS expression  */
#line 280 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("-", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1657 "build/parser.tab.c"
    break;

  case 48: /* expression: expression MUL expression  */
#line 282 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("*", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1663 "build/parser.tab.c"
    break;

  case 49: /* expression: expression DIV expression  */
#line 284 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("/", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1669 "build/parser.tab.c"
    break;

  case 50: /* expression: expression MOD expression  */
#line 286 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("%", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1675 "build/parser.tab.c"
    break;

  case 51: /* expression: expression LT expression  */
#line 288 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("<", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1681 "build/parser.tab.c"
    break;

  case 52: /* expression: expression GT expression  */
#line 290 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode(">", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1687 "build/parser.tab.c"
    break;

  case 53: /* expression: expression LE expression  */
#line 292 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("<=", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1693 "build/parser.tab.c"
    break;

  case 54: /* expression: expression GE expression  */
#line 294 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode(">=", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1699 "build/parser.tab.c"
    break;

  case 55: /* expression: expression EQ expression  */
#line 296 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("==", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1705 "build/parser.tab.c"
    break;

  case 56: /* expression: expression NEQ expression  */
#line 298 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("!=", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1711 "build/parser.tab.c"
    break;

  case 57: /* expression: expression AND expression  */
#line 300 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("&&", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1717 "build/parser.tab.c"
    break;

  case 58: /* expression: expression OR expression  */
#line 302 "src/parser/parser.y"
        { (yyval.node) = new BinaryOpNode("||", static_cast<ExprNode*>((yyvsp[-2].node)), static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1723 "build/parser.tab.c"
    break;

  case 59: /* expression: NOT expression  */
#line 304 "src/parser/parser.y"
        { (yyval.node) = new UnaryOpNode("!", static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1729 "build/parser.tab.c"
    break;

  case 60: /* expression: MINUS expression  */
#line 306 "src/parser/parser.y"
        { (yyval.node) = new UnaryOpNode("-", static_cast<ExprNode*>((yyvsp[0].node))); }
#line 1735 "build/parser.tab.c"
    break;

  case 61: /* expression: LPAREN expression RPAREN  */
#line 308 "src/parser/parser.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1741 "build/parser.tab.c"
    break;

  case 62: /* expression: call  */
#line 310 "src/parser/parser.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1747 "build/parser.tab.c"
    break;

  case 63: /* expression: INT_LIT  */
#line 312 "src/parser/parser.y"
        { (yyval.node) = new LiteralNode("int",    string((yyvsp[0].str_val))); free((yyvsp[0].str_val)); }
#line 1753 "build/parser.tab.c"
    break;

  case 64: /* expression: FLOAT_LIT  */
#line 314 "src/parser/parser.y"
        { (yyval.node) = new LiteralNode("float",  string((yyvsp[0].str_val))); free((yyvsp[0].str_val)); }
#line 1759 "build/parser.tab.c"
    break;

  case 65: /* expression: STR_LIT  */
#line 316 "src/parser/parser.y"
        { (yyval.node) = new LiteralNode("string", string((yyvsp[0].str_val))); free((yyvsp[0].str_val)); }
#line 1765 "build/parser.tab.c"
    break;

  case 66: /* expression: CHAR_LIT  */
#line 318 "src/parser/parser.y"
        { (yyval.node) = new LiteralNode("char",   string((yyvsp[0].str_val))); free((yyvsp[0].str_val)); }
#line 1771 "build/parser.tab.c"
    break;

  case 67: /* expression: BOOL_LIT  */
#line 320 "src/parser/parser.y"
        { (yyval.node) = new LiteralNode("bool",   string((yyvsp[0].str_val))); free((yyvsp[0].str_val)); }
#line 1777 "build/parser.tab.c"
    break;

  case 68: /* expression: IDENTIFIER  */
#line 322 "src/parser/parser.y"
        { (yyval.node) = new IdentifierNode(string((yyvsp[0].str_val))); free((yyvsp[0].str_val)); }
#line 1783 "build/parser.tab.c"
    break;

  case 69: /* call: IDENTIFIER LPAREN args RPAREN  */
#line 327 "src/parser/parser.y"
        {
            (yyval.node) = new CallNode(string((yyvsp[-3].str_val)), static_cast<ArgListNode*>((yyvsp[-1].node)));
            free((yyvsp[-3].str_val));
        }
#line 1792 "build/parser.tab.c"
    break;

  case 70: /* args: %empty  */
#line 334 "src/parser/parser.y"
                  { (yyval.node) = new ArgListNode(); }
#line 1798 "build/parser.tab.c"
    break;

  case 71: /* args: arg_list  */
#line 335 "src/parser/parser.y"
                  { (yyval.node) = (yyvsp[0].node);               }
#line 1804 "build/parser.tab.c"
    break;

  case 72: /* arg_list: expression  */
#line 340 "src/parser/parser.y"
        {
            ArgListNode* al = new ArgListNode();
            al->add(static_cast<ExprNode*>((yyvsp[0].node)));
            (yyval.node) = al;
        }
#line 1814 "build/parser.tab.c"
    break;

  case 73: /* arg_list: arg_list COMMA expression  */
#line 346 "src/parser/parser.y"
        {
            static_cast<ArgListNode*>((yyvsp[-2].node))->add(static_cast<ExprNode*>((yyvsp[0].node)));
            (yyval.node) = (yyvsp[-2].node);
        }
#line 1823 "build/parser.tab.c"
    break;


#line 1827 "build/parser.tab.c"

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

#line 352 "src/parser/parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "[ERROR SINTACTICO L%d C%d] %s\n", yylineno, yycol, s);
}
