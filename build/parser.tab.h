/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_PARSER_TAB_H_INCLUDED
# define YY_YY_BUILD_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    TYPE = 259,                    /* TYPE  */
    INT_LIT = 260,                 /* INT_LIT  */
    FLOAT_LIT = 261,               /* FLOAT_LIT  */
    STR_LIT = 262,                 /* STR_LIT  */
    CHAR_LIT = 263,                /* CHAR_LIT  */
    BOOL_LIT = 264,                /* BOOL_LIT  */
    FN = 265,                      /* FN  */
    LET = 266,                     /* LET  */
    MUT = 267,                     /* MUT  */
    IF = 268,                      /* IF  */
    ELSE = 269,                    /* ELSE  */
    WHILE = 270,                   /* WHILE  */
    FOR = 271,                     /* FOR  */
    IN = 272,                      /* IN  */
    RETURN = 273,                  /* RETURN  */
    PRINTLN_MACRO = 274,           /* PRINTLN_MACRO  */
    PLUS = 275,                    /* PLUS  */
    MINUS = 276,                   /* MINUS  */
    MUL = 277,                     /* MUL  */
    DIV = 278,                     /* DIV  */
    MOD = 279,                     /* MOD  */
    ASSIGN = 280,                  /* ASSIGN  */
    PLUS_ASSIGN = 281,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 282,            /* MINUS_ASSIGN  */
    MUL_ASSIGN = 283,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 284,              /* DIV_ASSIGN  */
    EQ = 285,                      /* EQ  */
    NEQ = 286,                     /* NEQ  */
    LT = 287,                      /* LT  */
    GT = 288,                      /* GT  */
    LE = 289,                      /* LE  */
    GE = 290,                      /* GE  */
    AND = 291,                     /* AND  */
    OR = 292,                      /* OR  */
    NOT = 293,                     /* NOT  */
    LPAREN = 294,                  /* LPAREN  */
    RPAREN = 295,                  /* RPAREN  */
    LBRACE = 296,                  /* LBRACE  */
    RBRACE = 297,                  /* RBRACE  */
    LBRACKET = 298,                /* LBRACKET  */
    RBRACKET = 299,                /* RBRACKET  */
    COMMA = 300,                   /* COMMA  */
    SEMICOLON = 301,               /* SEMICOLON  */
    COLON = 302,                   /* COLON  */
    ARROW = 303,                   /* ARROW  */
    DOT_DOT = 304,                 /* DOT_DOT  */
    UMINUS = 305                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "src/parser/parser.y"

    char*  str_val;
    void*  node;

#line 119 "build/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_TAB_H_INCLUDED  */
