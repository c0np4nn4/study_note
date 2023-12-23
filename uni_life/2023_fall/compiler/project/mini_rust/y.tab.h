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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    FN = 258,                      /* FN  */
    L_PAREN = 259,                 /* L_PAREN  */
    R_PAREN = 260,                 /* R_PAREN  */
    L_BRACE = 261,                 /* L_BRACE  */
    R_BRACE = 262,                 /* R_BRACE  */
    MAIN = 263,                    /* MAIN  */
    LET = 264,                     /* LET  */
    TYPE_U8 = 265,                 /* TYPE_U8  */
    TYPE_STR = 266,                /* TYPE_STR  */
    MACRO_PRINTLN = 267,           /* MACRO_PRINTLN  */
    ARROW = 268,                   /* ARROW  */
    SEMICOLON = 269,               /* SEMICOLON  */
    COLON = 270,                   /* COLON  */
    COMMA = 271,                   /* COMMA  */
    OP_ADD = 272,                  /* OP_ADD  */
    OP_SUB = 273,                  /* OP_SUB  */
    OP_MUL = 274,                  /* OP_MUL  */
    OP_DIV = 275,                  /* OP_DIV  */
    OP_ASSIGN = 276,               /* OP_ASSIGN  */
    NUM = 277,                     /* NUM  */
    ID = 278,                      /* ID  */
    STR_LITERAL = 279              /* STR_LITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define FN 258
#define L_PAREN 259
#define R_PAREN 260
#define L_BRACE 261
#define R_BRACE 262
#define MAIN 263
#define LET 264
#define TYPE_U8 265
#define TYPE_STR 266
#define MACRO_PRINTLN 267
#define ARROW 268
#define SEMICOLON 269
#define COLON 270
#define COMMA 271
#define OP_ADD 272
#define OP_SUB 273
#define OP_MUL 274
#define OP_DIV 275
#define OP_ASSIGN 276
#define NUM 277
#define ID 278
#define STR_LITERAL 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "parser.y"

  char *sval;
  int ival;

#line 120 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
