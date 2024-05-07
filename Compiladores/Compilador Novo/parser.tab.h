/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_KEYWORD = 258,
     TK_IDENTIFIER = 259,
     TK_NUMBER = 260,
     TK_SYMBOL_PLUS = 261,
     TK_SYMBOL_MINUS = 262,
     TK_SYMBOL_MULTIPLY = 263,
     TK_SYMBOL_DIVIDE = 264,
     TK_SYMBOL_ASSIGN = 265,
     TK_SYMBOL_SEMICOLON = 266,
     TK_SYMBOL_LESS_THAN = 267,
     TK_SYMBOL_GREATER_THAN = 268,
     TK_SYMBOL_LEFT_PARENTHESIS = 269,
     TK_SYMBOL_RIGHT_PARENTHESIS = 270,
     TK_SYMBOL_EQUAL = 271,
     TK_SYMBOL_NOT_EQUAL = 272,
     TK_SYMBOL_LESS_THAN_OR_EQUAL = 273,
     TK_SYMBOL_GREATER_THAN_OR_EQUAL = 274,
     TK_ERROR = 275,
     TK_INT_TYPE = 276,
     TK_VOID_TYPE = 277,
     TK_WHILE_OP = 278,
     TK_IF_OP = 279,
     TK_ELSE_OP = 280,
     TK_RETURN_OP = 281,
     TK_SYMBOL_COMMA = 282,
     TK_SYMBOL_LEFT_BRACES = 283,
     TK_SYMBOL_RIGHT_BRACES = 284,
     TK_SYMBOL_LEFT_BRACKET = 285,
     TK_SYMBOL_RIGHT_BRACKET = 286,
     TK_MAIN_OP = 287,
     TK_NEW_LINE = 288,
     TK_END_OF_FILE = 289
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


