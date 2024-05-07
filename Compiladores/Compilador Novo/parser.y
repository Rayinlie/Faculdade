%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "funcs.h"

typedef enum {
    NODE_FUNCTION_DECLARATION,
    NODE_TYPE_SPECIFIER,
    NODE_IDENTIFIER,
    NODE_PARAMETERS,
    NODE_COMPOUND_DECLARATION,
    NODE_STATEMENT,
    NODE_EXPRESSION,
    NODE_VAR_DECLARATION,
    NODE_VAR,
    NODE_SIMPLE_EXPRESSION,
    NODE_RELATIONAL,
    NODE_SUM_EXPRESSION,
    NODE_SUM,
    NODE_TERM,
    NODE_MULT,
    NODE_FACTOR,
    NODE_ACTIVATION,
    NODE_ARGS,
    NODE_ARG_LIST,
    NODE_LOCAL_DECLARATIONS,
    NODE_STATEMENT_LIST,
    NODE_SELECTION_DECLARATION,
    NODE_ITERATION_DECLARATION,
    NODE_RETURN_DECLARATION,
    NODE_EXPRESSION_DECLARATION,
    NODE_PARAM_LIST,
    NODE_PARAM,
    NODE_PROGRAM,
    NODE_DECLARATION_LIST,
    NODE_DECLARATION,
    NODE_VOID,
    NODE_INT,
    NODE_IF,
    NODE_ELSE,
    NODE_WHILE,
    NODE_RETURN,
    NODE_SYMBOL_ASSIGN,
    NODE_SYMBOL_SEMICOLON,
    NODE_SYMBOL_COMMA,
    NODE_SYMBOL_LEFT_PARENTHESIS,
    NODE_SYMBOL_RIGHT_PARENTHESIS,
    NODE_SYMBOL_LEFT_BRACES,
    NODE_SYMBOL_RIGHT_BRACES,
    NODE_SYMBOL_LEFT_BRACKET,
    NODE_SYMBOL_RIGHT_BRACKET,
    NODE_PLUS,
    NODE_MINUS,
    NODE_MULTIPLY,
    NODE_DIVIDE,
    NODE_LESS_THAN,
    NODE_GREATER_THAN,
    NODE_EQUAL,
    NODE_NOT_EQUAL,
    NODE_LESS_THAN_OR_EQUAL,
    NODE_GREATER_THAN_OR_EQUAL,
    NODE_NUMBER,
    NODE_ERROR,
    NODE_NEW_LINE,
    NODE_END_OF_FILE
} NodeType;

typedef struct TreeNode {
    NodeType type;
    char* label;
    struct TreeNode* child;
    struct TreeNode* sibling;
    Token token;
} TreeNode;

#define YYSTYPE TreeNode *

Token token;
extern Token token;

static int yylex();
extern int yydebug;

TreeNode* createTreeNode(NodeType type, const char* label) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = type;
    node->label = strdup(label);
    node->child = NULL;
    node->sibling = NULL;
    node->token = token;
    return node;
}

void freeTree(TreeNode* node) {
    if (node == NULL) return;
    freeTree(node->child);
    freeTree(node->sibling);
    free(node->label);
    free(node);
}

void printTreeToFile(TreeNode* node, int depth, FILE* output_file) {
    if (node == NULL || output_file == NULL) return;

    int indentation = 4;

    for (int i = 0; i < depth * indentation; i++) {
        fprintf(output_file, " ");
    }
    fprintf(output_file, "|- %s / %d\n",node->label, node->type);

    printTreeToFile(node->child, depth + 1, output_file);
    printTreeToFile(node->sibling, depth, output_file);
}

TreeNode *root = NULL;

InputBuffer *input_buffer;
KeywordNode *keyword_tree;

void yyerror(char *s) {
    printf("ERRO SINTATICO: %s LINHA: %d\n", s,token.line_number);
}

FILE *output_file;

%}

%token TK_KEYWORD
%token TK_IDENTIFIER
%token TK_NUMBER
%token TK_SYMBOL_PLUS
%token TK_SYMBOL_MINUS
%token TK_SYMBOL_MULTIPLY
%token TK_SYMBOL_DIVIDE
%token TK_SYMBOL_ASSIGN
%token TK_SYMBOL_SEMICOLON
%token TK_SYMBOL_LESS_THAN
%token TK_SYMBOL_GREATER_THAN
%token TK_SYMBOL_LEFT_PARENTHESIS
%token TK_SYMBOL_RIGHT_PARENTHESIS
%token TK_SYMBOL_EQUAL
%token TK_SYMBOL_NOT_EQUAL
%token TK_SYMBOL_LESS_THAN_OR_EQUAL
%token TK_SYMBOL_GREATER_THAN_OR_EQUAL
%token TK_ERROR
%token TK_INT_TYPE
%token TK_VOID_TYPE
%token TK_WHILE_OP
%token TK_IF_OP
%token TK_ELSE_OP
%token TK_RETURN_OP
%token TK_SYMBOL_COMMA
%token TK_SYMBOL_LEFT_BRACES
%token TK_SYMBOL_RIGHT_BRACES
%token TK_SYMBOL_LEFT_BRACKET
%token TK_SYMBOL_RIGHT_BRACKET
%token TK_MAIN_OP
%token TK_NEW_LINE
%token TK_END_OF_FILE

%left TK_ELSE_OP
%%
programa: declaracao_lista 
            {root = $1;}
;

declaracao_lista: declaracao_lista declaracao  
            { $$ = createTreeNode(NODE_DECLARATION_LIST, "Declaration List"); 
                $$->child = $1; 
                $$->child->sibling = $2;
            }
| declaracao  
            { $$ = createTreeNode(NODE_DECLARATION, "Declaration "); 
                $$->child = $1;
            }
;

declaracao: var_declaracao 
            { $$ = createTreeNode(NODE_VAR_DECLARATION, "Var Declaration"); 
                $$->child = $1;
            }
| fun_declaracao
            {
                $$ = createTreeNode(NODE_DECLARATION, "Declaration");
                $$->child = $1;
            }
;

var_declaracao: tipo_especificador TK_IDENTIFIER TK_SYMBOL_SEMICOLON
            {
                $$ = createTreeNode(NODE_VAR_DECLARATION, "Var Declaration");
                $$->child = $1;
                $$->child->sibling = createTreeNode(NODE_IDENTIFIER, "identifier");
                $$->child->sibling->sibling = createTreeNode(NODE_SYMBOL_SEMICOLON, ";");           
            }
| tipo_especificador TK_IDENTIFIER TK_SYMBOL_LEFT_BRACKET TK_NUMBER TK_SYMBOL_RIGHT_BRACKET TK_SYMBOL_SEMICOLON
            {
                $$ = createTreeNode(NODE_VAR_DECLARATION, "Var Declaration");
                $$->child = $1;
                $$->child->sibling = createTreeNode(NODE_IDENTIFIER, "identifier");
                $$->child->sibling->sibling = createTreeNode(NODE_SYMBOL_LEFT_BRACKET, "[");
                $$->child->sibling->sibling->sibling = createTreeNode(NODE_NUMBER, "number");
                $$->child->sibling->sibling->sibling->sibling = createTreeNode(NODE_SYMBOL_RIGHT_BRACKET, "]");
                $$->child->sibling->sibling->sibling->sibling->sibling = createTreeNode(NODE_SYMBOL_SEMICOLON, ";");
            }
;

fun_declaracao: tipo_especificador TK_IDENTIFIER TK_SYMBOL_LEFT_PARENTHESIS params TK_SYMBOL_RIGHT_PARENTHESIS composto_decl
            {
                $$ = createTreeNode(NODE_FUNCTION_DECLARATION, "Function Declaration");
                $$->child = $1;
                $$->child->sibling = createTreeNode(NODE_IDENTIFIER, "identifier");
                $$->child->sibling->sibling = $4;
                $$->child->sibling->sibling->sibling = $6;
                $$->child->sibling->sibling->sibling->sibling = createTreeNode(NODE_SYMBOL_RIGHT_PARENTHESIS, ")");
                $$->child->sibling->sibling->sibling->sibling->sibling = createTreeNode(NODE_COMPOUND_DECLARATION, "Compound Declaration");
            }
;

tipo_especificador: TK_INT_TYPE 
            {$$ = createTreeNode(NODE_TYPE_SPECIFIER, "int");}
| TK_VOID_TYPE 
            {$$ = createTreeNode(NODE_TYPE_SPECIFIER, "void");}
;

params: param_lista 
            {
            $$ = createTreeNode(NODE_PARAM_LIST, "Param List"); 
            $$->child = $1;
            }
| TK_VOID_TYPE 
            {
                $$ = createTreeNode(NODE_PARAMETERS, "Parameters"); 
                $$->child = createTreeNode(NODE_VOID, "void");
            }
;

param_lista: param_lista TK_SYMBOL_COMMA param 
            {
                $$ = createTreeNode(NODE_PARAM_LIST, "Param List"); 
                $$->child = $1; 
                $$->child->sibling = $3;
            }
| param 
            {
                $$ = createTreeNode(NODE_PARAM_LIST, "Param List"); 
                $$->child = $1;
            }
;

param: tipo_especificador TK_IDENTIFIER 
            {
                $$ = createTreeNode(NODE_PARAM, "Param"); 
                $$->child = $1; 
                $$->child->sibling = createTreeNode(NODE_IDENTIFIER, "identifier");
            }
| tipo_especificador TK_IDENTIFIER TK_SYMBOL_LEFT_BRACKET TK_SYMBOL_RIGHT_BRACKET 
            {
                $$ = createTreeNode(NODE_PARAM, "Param"); 
                $$->child = $1; 
                $$->child->sibling = createTreeNode(NODE_IDENTIFIER, "identifier");
                $$->child->sibling->sibling = createTreeNode(NODE_SYMBOL_RIGHT_BRACKET, "]");
                $$->child->sibling->sibling->sibling = createTreeNode(NODE_SYMBOL_LEFT_BRACKET, "[");
            }
;

composto_decl: TK_SYMBOL_LEFT_BRACES local_declaracoes statement_lista TK_SYMBOL_RIGHT_BRACES 
            {
                $$ = createTreeNode(NODE_COMPOUND_DECLARATION, "Compound Declaration"); 
                $$->child = createTreeNode(NODE_SYMBOL_LEFT_BRACES, "{"); 
                $$->child->sibling = $2; 
                $$->child->sibling->sibling = $3; 
                $$->child->sibling->sibling->sibling = createTreeNode(NODE_SYMBOL_RIGHT_BRACES, "}");
            }
;


local_declaracoes: local_declaracoes var_declaracao
            {
                $$ = createTreeNode(NODE_LOCAL_DECLARATIONS, "Local Declarations");
                $$->child = $1;
                $$->child->sibling = $2;
            }
|
            { 
                $$ = createTreeNode(NODE_LOCAL_DECLARATIONS, "Local Declarations");
                $$->child = NULL;
            }
;

statement_lista: statement_lista statement
            {
                $$ = createTreeNode(NODE_STATEMENT_LIST, "Statement List");
                $$->child = $1;
                $$->child->sibling = $2;
            }        
|
            { 
                $$ = createTreeNode(NODE_STATEMENT_LIST, "Statement List");
                $$->child = NULL;
            }
;

statement: expressao_decl
            {
                $$ = createTreeNode(NODE_STATEMENT, "Statement");
                $$->child = $1;
            }
| composto_decl
            {
                $$ = createTreeNode(NODE_STATEMENT, "Statement");
                $$->child = $1;
            }
| selecao_decl
            {
                $$ = createTreeNode(NODE_STATEMENT, "Statement");
                $$->child = $1;
            }
| iteracao_decl
            {
                $$ = createTreeNode(NODE_STATEMENT, "Statement");
                $$->child = $1;
            }
| retorno_decl
            {
                $$ = createTreeNode(NODE_STATEMENT, "Statement");
                $$->child = $1;
            }  
;

expressao_decl: expressao TK_SYMBOL_SEMICOLON
            {
                $$ = createTreeNode(NODE_EXPRESSION_DECLARATION, "Expression Declaration");
                $$->child = $1;
                $$->child->sibling = createTreeNode(NODE_SYMBOL_SEMICOLON, ";");
            }
| TK_SYMBOL_SEMICOLON
            {
                $$ = createTreeNode(NODE_EXPRESSION_DECLARATION, "Expression Declaration");
                $$->child = createTreeNode(NODE_SYMBOL_SEMICOLON, ";");
            }
;

selecao_decl : if_statement
            { $$ = $1;}
| if_statement_with_else
            { $$ = $1;}
;

if_statement : TK_IF_OP TK_SYMBOL_LEFT_PARENTHESIS expressao TK_SYMBOL_RIGHT_PARENTHESIS statement
            {
                $$ = createTreeNode(NODE_SELECTION_DECLARATION, "Selection Declaration");
                $$->child = createTreeNode(NODE_IF, "if");
                $$->child->sibling = createTreeNode(NODE_SYMBOL_LEFT_PARENTHESIS, "(");
                $$->child->sibling->sibling = $3;
                $$->child->sibling->sibling->sibling = createTreeNode(NODE_SYMBOL_RIGHT_PARENTHESIS, ")");
                $$->child->sibling->sibling->sibling->sibling = $5;
            }
;

if_statement_with_else : TK_IF_OP TK_SYMBOL_LEFT_PARENTHESIS expressao TK_SYMBOL_RIGHT_PARENTHESIS statement TK_ELSE_OP statement
            {
                $$ = createTreeNode(NODE_SELECTION_DECLARATION, "Selection Declaration");
                $$->child = createTreeNode(NODE_IF, "if");
                $$->child->sibling = createTreeNode(NODE_SYMBOL_LEFT_PARENTHESIS, "(");
                $$->child->sibling->sibling = $3;
                $$->child->sibling->sibling->sibling = createTreeNode(NODE_SYMBOL_RIGHT_PARENTHESIS, ")");
                $$->child->sibling->sibling->sibling->sibling = $5;
                $$->child->sibling->sibling->sibling->sibling->sibling = $6;
            }
;

iteracao_decl: TK_WHILE_OP TK_SYMBOL_LEFT_PARENTHESIS expressao TK_SYMBOL_RIGHT_PARENTHESIS statement
            {
                $$ = createTreeNode(NODE_ITERATION_DECLARATION, "Iteration Declaration");
                $$->child = createTreeNode(NODE_WHILE, "while");
                $$->child->sibling = createTreeNode(NODE_SYMBOL_LEFT_PARENTHESIS, "(");
                $$->child->sibling->sibling = $3;
                $$->child->sibling->sibling->sibling = createTreeNode(NODE_SYMBOL_RIGHT_PARENTHESIS, ")");
                $$->child->sibling->sibling->sibling->sibling = $5;
            }
;

retorno_decl: TK_RETURN_OP TK_SYMBOL_SEMICOLON
            {
                $$ = createTreeNode(NODE_RETURN_DECLARATION, "Return Declaration");
                $$->child = createTreeNode(NODE_RETURN, "return");
                $$->child->sibling = createTreeNode(NODE_SYMBOL_SEMICOLON, ";");
            }
| TK_RETURN_OP expressao TK_SYMBOL_SEMICOLON
            {
                $$ = createTreeNode(NODE_RETURN_DECLARATION, "Return Declaration");
                $$->child = createTreeNode(NODE_RETURN, "return");
                $$->child->sibling = $2;
                $$->child->sibling->sibling = createTreeNode(NODE_SYMBOL_SEMICOLON, ";");
            }
;

expressao: var TK_SYMBOL_ASSIGN expressao
            {
                $$ = createTreeNode(NODE_EXPRESSION, "Expression");
                $$->child = $1;
                $$->child->sibling = createTreeNode(NODE_SYMBOL_ASSIGN, "=");
                $$->child->sibling->sibling = $3;
            }
| simples_expressao
            {
                $$ = createTreeNode(NODE_EXPRESSION, "Expression");
                $$->child = $1;
            }
;

var: TK_IDENTIFIER
            {
                $$ = createTreeNode(NODE_VAR, "Var");
                $$->child = createTreeNode(NODE_IDENTIFIER, "identifier");
            }
| TK_IDENTIFIER TK_SYMBOL_LEFT_BRACKET expressao TK_SYMBOL_RIGHT_BRACKET
            {
                $$ = createTreeNode(NODE_VAR, "Var");
                $$->child = createTreeNode(NODE_IDENTIFIER, "identifier");
                $$->child->sibling = createTreeNode(NODE_SYMBOL_LEFT_BRACKET, "[");
                $$->child->sibling->sibling = $3;
                $$->child->sibling->sibling->sibling = createTreeNode(NODE_SYMBOL_RIGHT_BRACKET, "]");
            }
;

simples_expressao: soma_expressao relacional soma_expressao
            {
                $$ = createTreeNode(NODE_SIMPLE_EXPRESSION, "Simple Expression");
                $$->child = $1;
                $$->child->sibling = $2;
                $$->child->sibling->sibling = $3;
            }
| soma_expressao
            {
                $$ = createTreeNode(NODE_SIMPLE_EXPRESSION, "Simple Expression");
                $$->child = $1;
            }
;

relacional: TK_SYMBOL_LESS_THAN
            { $$ = createTreeNode(NODE_RELATIONAL, "<"); }
| TK_SYMBOL_GREATER_THAN
            { $$ = createTreeNode(NODE_RELATIONAL, ">"); }
| TK_SYMBOL_EQUAL
            { $$ = createTreeNode(NODE_RELATIONAL, "=="); }
| TK_SYMBOL_NOT_EQUAL
            { $$ = createTreeNode(NODE_RELATIONAL, "!="); }
| TK_SYMBOL_LESS_THAN_OR_EQUAL
            { $$ = createTreeNode(NODE_RELATIONAL, "<="); }
| TK_SYMBOL_GREATER_THAN_OR_EQUAL
            { $$ = createTreeNode(NODE_RELATIONAL, ">="); }
;

soma_expressao: soma_expressao TK_SYMBOL_PLUS termo
            { $$ = createTreeNode(NODE_SUM_EXPRESSION, "Sum Expression");
                $$->child = $1;
                $$->child->sibling = createTreeNode(NODE_SUM, "+");
                $$->child->sibling->sibling = $3;
            }
| soma_expressao TK_SYMBOL_MINUS termo
            { 
                $$ = createTreeNode(NODE_SUM_EXPRESSION, "Sum Expression");
                $$->child = $1;
                $$->child->sibling = createTreeNode(NODE_SUM, "-");
                $$->child->sibling->sibling = $3;
            }
| termo
            {
                $$ = createTreeNode(NODE_SUM_EXPRESSION, "Sum Expression");
                $$->child = $1;
            }
;

termo: termo TK_SYMBOL_MULTIPLY fator
            { 
                $$ = createTreeNode(NODE_TERM, "Term");
                $$->child = $1;
                $$->child->sibling = createTreeNode(NODE_MULT, "*");
                $$->child->sibling->sibling = $3;
            }
| termo TK_SYMBOL_DIVIDE fator
            { 
                $$ = createTreeNode(NODE_TERM, "Term");
                $$->child = $1;
                $$->child->sibling = createTreeNode(NODE_MULT, "/");
                $$->child->sibling->sibling = $3;
            }
| fator
            {
                $$ = createTreeNode(NODE_TERM, "Term");
                $$->child = $1;
            }
;

fator: TK_SYMBOL_LEFT_PARENTHESIS expressao TK_SYMBOL_RIGHT_PARENTHESIS
            { 
                $$ = createTreeNode(NODE_FACTOR, "Factor");
                $$->child = createTreeNode(NODE_SYMBOL_LEFT_PARENTHESIS, "(");
                $$->child->sibling = $2;
                $$->child->sibling->sibling = createTreeNode(NODE_SYMBOL_RIGHT_PARENTHESIS, ")");
            }
| var
            {
                $$ = createTreeNode(NODE_FACTOR, "Factor");
                $$->child = $1;
            }
| ativacao
            {
                $$ = createTreeNode(NODE_FACTOR, "Factor");
                $$->child = $1;
            }
| TK_NUMBER
            {
                $$ = createTreeNode(NODE_FACTOR, "Factor");
                $$->child = createTreeNode(NODE_NUMBER, "number");
            }
;  

ativacao: TK_IDENTIFIER TK_SYMBOL_LEFT_PARENTHESIS args TK_SYMBOL_RIGHT_PARENTHESIS
            {
                $$ = createTreeNode(NODE_ACTIVATION, "Activation");
                $$->child = createTreeNode(NODE_IDENTIFIER, "identifier");
                $$->child->sibling = createTreeNode(NODE_SYMBOL_LEFT_PARENTHESIS, "(");
                $$->child->sibling->sibling = $3;
                $$->child->sibling->sibling->sibling = createTreeNode(NODE_SYMBOL_RIGHT_PARENTHESIS, ")");
            }
;

args: arg_lista
            {
                $$ = createTreeNode(NODE_ARGS, "Args");
                $$->child = $1;
            }
|
            {
                $$ = createTreeNode(NODE_ARGS, "Args");
                $$->child = NULL;
            }
;

arg_lista: arg_lista TK_SYMBOL_COMMA expressao
            {
                $$ = createTreeNode(NODE_ARG_LIST, "Arg List");
                $$->child = $1;
                $$->child->sibling = createTreeNode(NODE_SYMBOL_COMMA, ",");
                $$->child->sibling->sibling = $3;
            }
| expressao
            {
                $$ = createTreeNode(NODE_ARG_LIST, "Arg List");
                $$->child = $1;
            }
;
%%

static TreeNode* parse(){
    yyparse();
    return root;
}

static int yylex(void){
    token = getNextToken(input_buffer, keyword_tree);
    return token.type;
}

int main(int argc, char *argv[]) {
    yydebug = 1;

    if (argc != 2) {
        printf("Argumentos insuficientes\n");
        return 1;
    }

    input_buffer = createInputBuffer(argv[1]);

    if (input_buffer == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    FILE *output_file = fopen("output.txt", "w");

    if (output_file == NULL) {
        printf("Erro ao abrir o arquivo de saida.\n");
        return 1;
    }

    keyword_tree = createKeywordTree();

    parse();

    if (root != NULL) {  
        printf("Arvore Sintatica Gerada em: output.txt\n");
        printTreeToFile(root, 0, output_file);
    } else {
        yyerror(token.lexeme);
    }

    fclose(output_file);
    freeInputBuffer(input_buffer);
    freeKeywordTree(keyword_tree);
    freeTree(root);
    return 0;
}
