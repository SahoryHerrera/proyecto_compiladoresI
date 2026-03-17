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
/* "%code requires" blocks.  */
#line 16 "src/parser/parser.y"

    #include "../src/ast/ast.hpp"

#line 53 "build/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FN = 258,                      /* FN  */
    LET = 259,                     /* LET  */
    IF = 260,                      /* IF  */
    ELSE = 261,                    /* ELSE  */
    WHILE = 262,                   /* WHILE  */
    FOR = 263,                     /* FOR  */
    IN = 264,                      /* IN  */
    RETURN = 265,                  /* RETURN  */
    TYPE = 266,                    /* TYPE  */
    IDENTIFIER = 267,              /* IDENTIFIER  */
    INT_LITERAL = 268,             /* INT_LITERAL  */
    FLOAT_LITERAL = 269,           /* FLOAT_LITERAL  */
    BOOL_LITERAL = 270,            /* BOOL_LITERAL  */
    CHAR_LITERAL = 271,            /* CHAR_LITERAL  */
    STRING_LITERAL = 272,          /* STRING_LITERAL  */
    PLUS = 273,                    /* PLUS  */
    MINUS = 274,                   /* MINUS  */
    MUL = 275,                     /* MUL  */
    DIV = 276,                     /* DIV  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    NOT = 279,                     /* NOT  */
    EQ = 280,                      /* EQ  */
    NEQ = 281,                     /* NEQ  */
    LT = 282,                      /* LT  */
    GT = 283,                      /* GT  */
    LE = 284,                      /* LE  */
    GE = 285,                      /* GE  */
    ASSIGN = 286,                  /* ASSIGN  */
    LPAREN = 287,                  /* LPAREN  */
    RPAREN = 288,                  /* RPAREN  */
    LBRACE = 289,                  /* LBRACE  */
    RBRACE = 290,                  /* RBRACE  */
    LBRACKET = 291,                /* LBRACKET  */
    RBRACKET = 292,                /* RBRACKET  */
    COMMA = 293,                   /* COMMA  */
    SEMICOLON = 294,               /* SEMICOLON  */
    COLON = 295,                   /* COLON  */
    ARROW = 296,                   /* ARROW  */
    RANGE = 297,                   /* RANGE  */
    UMINUS = 298                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "src/parser/parser.y"

    char* text;
    ASTNode* node;

#line 118 "build/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_TAB_H_INCLUDED  */
