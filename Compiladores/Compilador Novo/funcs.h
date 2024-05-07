#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define MAX_LEXEME_SIZE 64

typedef enum TokenType{
    KEYWORD = 258,
    IDENTIFIER = 259,
    NUMBER = 260,
    SYMBOL_PLUS = 261,
    SYMBOL_MINUS = 262,
    SYMBOL_MULTIPLY = 263,
    SYMBOL_DIVIDE = 264,
    SYMBOL_ASSIGN = 265,
    SYMBOL_SEMICOLON = 266,
    SYMBOL_LESS_THAN = 267,
    SYMBOL_GREATER_THAN = 268,
    SYMBOL_LEFT_PARENTHESIS = 269,
    SYMBOL_RIGHT_PARENTHESIS = 270,
    SYMBOL_EQUAL = 271,
    SYMBOL_NOT_EQUAL = 272,
    SYMBOL_LESS_THAN_OR_EQUAL = 273,
    SYMBOL_GREATER_THAN_OR_EQUAL = 274,
    ERROR = 275,
    INT_TYPE = 276,
    VOID_TYPE = 277,
    WHILE_OP = 278,
    IF_OP = 279,
    ELSE_OP = 280,
    RETURN_OP = 281,
    SYMBOL_COMMA = 282,
    SYMBOL_LEFT_BRACES = 283,
    SYMBOL_RIGHT_BRACES = 284,
    SYMBOL_LEFT_BRACKET = 285,
    SYMBOL_RIGHT_BRACKET = 286,
    MAIN_OP = 287,
    NEW_LINE = 288,
    END_OF_FILE = 289
} TokenType;

enum keywords {INT, VOID, WHILE, IF, ELSE, RETURN, MAIN};

typedef struct KeywordNode {
    char* keyword;
    TokenType type;
    struct KeywordNode* children[26];
} KeywordNode;

typedef struct {
    FILE *file;
    char buffer[BUFFER_SIZE];
    int position;
    int line_number;
} InputBuffer;

typedef struct {
    TokenType type;
    char lexeme[MAX_LEXEME_SIZE];
    int line_number;
} Token;

KeywordNode* createKeywordTree();
void freeKeywordTree(KeywordNode* root);
KeywordNode* createKeywordNode(char* keyword, TokenType type);
void insertKeyword(KeywordNode* root, char* keyword, TokenType type);
TokenType searchKeyword(KeywordNode* root, char* keyword);

InputBuffer *createInputBuffer(const char *filename);
void freeInputBuffer(InputBuffer *buffer);
char get_next_char(InputBuffer *buffer);
void retract_char(InputBuffer *buffer);
void printToken(Token token);

Token setToken(TokenType type, char* lexeme, int line_number);
Token getNextToken(InputBuffer *buffer, KeywordNode* keyword_tree);
Token Keyword_State(InputBuffer *buffer, char ch, KeywordNode* keyword_tree);
Token Identifier_State(InputBuffer *buffer, char ch );
Token Number_State(InputBuffer *buffer, char ch);
Token Operator_State(InputBuffer *buffer, char ch);
Token Logical_State(InputBuffer *buffer, char ch);
Token Logical_Plus_State(InputBuffer *buffer, char ch);
Token Assign_State(InputBuffer *buffer, char ch);
Token Symbol_State(InputBuffer *buffer, char ch);