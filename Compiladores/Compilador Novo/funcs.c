#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funcs.h"
#include <stdbool.h>

int tabelaEstados[11][7] = {
                    //letra	num	operation logical  assign  symbol 	keyword
  /*0Entry*/         {2,     3,      4,      5,      6,      7,      1},                    
  /*1Keyword*/       {1,     10,     9,      9,      9,      9,      2},
  /*2ID*/            {2,     10,     9,      9,      9,      9,      2},
  /*3num*/           {10,    3,      9,      9,      9,      9,      10},
  /*4operation*/     {9,     9,      10,     10,     10,     9,      9},
  /*5logical*/       {9,     9,      9,      6,      6,      9,      9},
  /*6logicalPlus*/   {9,     9,      9,      10,     10,     9,      9},
  /*7assign*/        {9,     9,      9,      10,     6,      9,      9},
  /*8symbol*/        {9,     9,      9,      10,     10,     9,      9},
  /*9accept*/        {9,     9,      9,      9,      9,      9,      9},
 /*10error*/         {10,    10,     10,     10,     10,     10,     10}
};

bool aceitacao[11] = {false, false, false, false, false, false, false, false, false, true, false};

int currentState = 0;
int lastState = 0; 

char get_next_char(InputBuffer *input_buffer) {
    if (input_buffer->position >= BUFFER_SIZE || input_buffer->buffer[input_buffer->position] == '\0') {
        int bytes_read = fread(input_buffer->buffer, sizeof(char), BUFFER_SIZE - 1, input_buffer->file);
        if (bytes_read == 0) {
            input_buffer->buffer[0] = '\0';
            return EOF;
        }
        input_buffer->buffer[bytes_read] = '\0';
        input_buffer->position = 0;
    }

    char current_char = input_buffer->buffer[input_buffer->position];
    if (current_char == '\n' || current_char == '\0') {
        input_buffer->line_number++;
    }
    input_buffer->position++;

    return current_char;
}



void retract_char(InputBuffer *input_buffer) {
    if (input_buffer->position > 0) {
        input_buffer->position--;
        if (input_buffer->buffer[input_buffer->position] == '\n') {
            input_buffer->line_number--;
        }
    }
}

void freeInputBuffer(InputBuffer *input_buffer) {
    fclose(input_buffer->file);
    free(input_buffer);
}

InputBuffer *createInputBuffer(const char *filename) {
    InputBuffer *input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->file = fopen(filename, "r");
    input_buffer->position = BUFFER_SIZE;
    input_buffer->line_number = 1;
    input_buffer->buffer[0] = '\0';
    return input_buffer;
}

KeywordNode* createKeywordNode(char* keyword, TokenType type) {
    KeywordNode* node = (KeywordNode*)malloc(sizeof(KeywordNode));
    node->keyword = keyword;
    node->type = type;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insertKeyword(KeywordNode* root, char* keyword, TokenType type) {
    KeywordNode* current = root;
    int length = strlen(keyword);
    for (int i = 0; i < length; i++) {
        int index = keyword[i] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createKeywordNode(NULL, IDENTIFIER);
        }
        current = current->children[index];
    }
    current->keyword = keyword;
    current->type = type;
}

TokenType searchKeyword(KeywordNode* root, char* keyword) {
    KeywordNode* current = root;
    int length = strlen(keyword);
    for (int i = 0; i < length; i++) {
        int index = keyword[i] - 'a';
        if (current->children[index] == NULL) {
            return IDENTIFIER;
        }
        current = current->children[index];
    }
    currentState = 1;
    return current->type;
}

KeywordNode* createKeywordTree() {
    KeywordNode* root = createKeywordNode(NULL, 258);
    insertKeyword(root, "int", 276);
    insertKeyword(root, "void", 277);
    insertKeyword(root, "while", 278);
    insertKeyword(root, "if", 279);
    insertKeyword(root, "else", 280);
    insertKeyword(root, "return", 281);
    insertKeyword(root, "main", 287);
    return root;
}

void freeKeywordTree(KeywordNode* root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        freeKeywordTree(root->children[i]);
    }
    free(root);
}

Token Keyword_State(InputBuffer *input_buffer, char ch, KeywordNode* keyword_tree) {
    Token token;
    token.line_number = input_buffer->line_number;
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    char next_char = get_next_char(input_buffer);
    while (isalpha(next_char)) {
        strcat(token.lexeme, &next_char);
        next_char = get_next_char(input_buffer);
    }
    retract_char(input_buffer);
    TokenType type = searchKeyword(keyword_tree, token.lexeme);
    if (type == IDENTIFIER) {
        token.type = IDENTIFIER;
    } else {
        token.type = type;
    }
    lastState = 1;
    currentState = 9;
    return setToken(token.type, token.lexeme, token.line_number);
}

Token Identifier_State(InputBuffer *input_buffer, char ch) {
    Token token;
    token.line_number = input_buffer->line_number;
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    char next_char = get_next_char(input_buffer);
    while (isalpha(next_char)) {
        strcat(token.lexeme, &next_char);
        next_char = get_next_char(input_buffer);
    }

    retract_char(input_buffer);
    token.type = IDENTIFIER;
    lastState = 2;
    currentState = 9;
    return token;
}

Token Number_State(InputBuffer *input_buffer, char ch) {
    Token token;
    token.line_number = input_buffer->line_number;
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    char next_char = get_next_char(input_buffer);
    char temp[2];

    while (isdigit(next_char)) {
        temp[0] = next_char;
        temp[1] = '\0';
        strcat(token.lexeme, temp);
        next_char = get_next_char(input_buffer);
    }

    if (next_char != '\0' && !isspace(next_char) && !ispunct(next_char) && next_char != EOF) {
        retract_char(input_buffer);
    }
    retract_char(input_buffer);
    token.type = NUMBER;
    lastState = 3;
    currentState = 9;
    return token;
}

Token Logical_State(InputBuffer *input_buffer, char ch) {
    Token token;
    token.line_number = input_buffer->line_number;
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    char next_char = get_next_char(input_buffer);
    if (next_char == '=') {
        strcat(token.lexeme, &next_char);
    } else {
        retract_char(input_buffer);
    }
    switch (ch) {
        case '<':
            token.type = SYMBOL_LESS_THAN;
            break;
        case '>':
            token.type = SYMBOL_GREATER_THAN;
            break;
        default:
            token.type = ERROR;
            break;
    }
    lastState = 5;
    currentState = 9;
    return token;
}

Token Logical_Plus_State(InputBuffer *input_buffer, char ch) {
    Token token;
    token.line_number = input_buffer->line_number;
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    char next_char = get_next_char(input_buffer);
    if (next_char == '=') {
        strcat(token.lexeme, &next_char);
    } else {
        retract_char(input_buffer);
    }
    switch (ch) {
        case '<':
            token.type = SYMBOL_LESS_THAN_OR_EQUAL;
            break;
        case '>':
            token.type = SYMBOL_GREATER_THAN_OR_EQUAL;
            break;
        case '!':
            token.type = SYMBOL_NOT_EQUAL;
            break;
        default:
            token.type = ERROR;
            break;
    }
    lastState = 6;
    currentState = 9;
    return token;
}

Token Assign_State(InputBuffer *input_buffer, char ch) {
    Token token;
    token.line_number = input_buffer->line_number;
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    char next_char = get_next_char(input_buffer);
    if (next_char == '=') {
        strcat(token.lexeme, &next_char);
        token.type = SYMBOL_EQUAL; 
    } else {
        retract_char(input_buffer);
        token.type = SYMBOL_ASSIGN;
    }
    lastState = 7;
    currentState = 9;
    return token;
}

Token Symbol_State(InputBuffer *input_buffer, char ch) {
    Token token;
    token.line_number = input_buffer->line_number;
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    switch (ch) {
        case ';':
            token.type = SYMBOL_SEMICOLON;
            break;
        case ',':
            token.type = SYMBOL_COMMA;
            break;
        case '(':
            token.type = SYMBOL_LEFT_PARENTHESIS;
            break;
        case ')':
            token.type = SYMBOL_RIGHT_PARENTHESIS;
            break;
        case '{':
            token.type = SYMBOL_LEFT_BRACES;
            break;
        case '}':
            token.type = SYMBOL_RIGHT_BRACES;
            break;
        case '[':
            token.type = SYMBOL_LEFT_BRACKET;
            break;
        case ']':
            token.type = SYMBOL_RIGHT_BRACKET;
            break;
        default:
            token.type = ERROR;
            break;
    } 
    lastState = 8;
    currentState = 9;
    return token;
    
}

Token Operation_State(InputBuffer *input_buffer, char ch) {
    Token token;
    token.line_number = input_buffer->line_number;
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    char next_char = get_next_char(input_buffer);
    if (next_char == '=') {
        strcat(token.lexeme, &next_char);
    } else {
        retract_char(input_buffer);
    }
    switch (ch) {
        case '+':
            token.type = SYMBOL_PLUS;
            break;
        case '-':
            token.type = SYMBOL_MINUS;
            break;
        case '*':
            token.type = SYMBOL_MULTIPLY;
            break;
        case '/':
            token.type = SYMBOL_DIVIDE;
            break;
        default:
            token.type = ERROR;
            break;
    }
    lastState = 4;
    currentState = 9;
    return token;
}

void printToken(Token token) {
    printf("%s\t%d\t%d\n", token.lexeme, token.type, token.line_number);
}

Token setToken(TokenType type, char* lexeme, int line_number) {
    Token token;
    token.type = type;
    strcpy(token.lexeme, lexeme);
    token.line_number = line_number;
    return token;
}

int getCharType(char ch) {
    if (isalpha(ch)) {
        return 1;  // letra
    } else if (isdigit(ch)) {
        return 3;  // num
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        return 4;  // operation
    } else if (ch == '<' || ch == '>' || ch == '!') {
        return 5;  // logical
    } else if (ch == '=') {
        return 7;  // assign
    } else if (ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']') {
        return 8;  // symbol
    } else {
        return 10; // outros caracteres
    }
}


Token getNextToken(InputBuffer *input_buffer, KeywordNode* keyword_tree) {
    Token token;
        char current_char = get_next_char(input_buffer);
            
        while (isspace(current_char) || current_char == '\n') {
            current_char = get_next_char(input_buffer);
        }
        if (current_char == EOF) {
            token.type = EOF;
            token.lexeme[0] = '\0';
            token.line_number = input_buffer->line_number;
            freeInputBuffer(input_buffer);
            return token;
        }
        

        if (current_char == '/') {
            char next_char = get_next_char(input_buffer);
            if (next_char == '*') {
                char prev_char = '\0';
                while (1) {
                    current_char = get_next_char(input_buffer);
                    if (current_char == EOF) {
                        token.type = ERROR;
                        return token;
                    }
                    if (prev_char == '*' && current_char == '/') {
                        
                        break;
                    }
                    prev_char = current_char;
                }
                current_char = get_next_char(input_buffer);
                return getNextToken(input_buffer, keyword_tree);
            } else {
                retract_char(input_buffer);
            }
        }
    char lexeme[MAX_LEXEME_SIZE];

    int index = 0;
    int entry = 0;
    while (!isspace(current_char) && current_char != '\0') {
        entry = getCharType(current_char);
        
        switch (entry) {
            case 1:
                token = Keyword_State(input_buffer, current_char, keyword_tree);                
                return token;
            case 2:
                token = Identifier_State(input_buffer, current_char);
                return token;
            case 3:
                token = Number_State(input_buffer, current_char);
                return token;
            case 4:
                token = Operation_State(input_buffer, current_char);
                return token;
            case 5:
                token = Logical_State(input_buffer, current_char);
                return token;
            case 6:
                token = Logical_Plus_State(input_buffer, current_char);
                return token;
            case 7:
                token = Assign_State(input_buffer, current_char);
                return token;
            case 8:
                token = Symbol_State(input_buffer, current_char);
                return token;
            case 9:
                return setToken(token.type, lexeme, input_buffer->line_number);                
            case 10:                    
                return setToken(ERROR, lexeme, input_buffer->line_number);
        }
        lexeme[index++] = current_char;
        current_char = get_next_char(input_buffer);
    }

    lastState = getCharType(current_char);

    currentState = tabelaEstados[currentState][getCharType(current_char)];
    
    if (aceitacao[currentState]) {
        retract_char(input_buffer);
        lexeme[index] = '\0';
        
        switch (currentState) {
            case 1:
                token = Keyword_State(input_buffer, current_char, keyword_tree);                
                return token;
            case 2:
                token = Identifier_State(input_buffer, current_char);
                return token;
            case 3:
                token = Number_State(input_buffer, current_char);
                return token;
            case 4:
                token = Operation_State(input_buffer, current_char);
                return token;
            case 5:
                token = Logical_State(input_buffer, current_char);
                return token;
            case 6:
                token = Logical_Plus_State(input_buffer, current_char);
                return token;
            case 7:
                token = Assign_State(input_buffer, current_char);
                return token;
            case 8:
                token = Symbol_State(input_buffer, current_char);
                return token;
            case 9:
                return setToken(token.type, lexeme, input_buffer->line_number);                
            case 10:
                printf("Erro léxico: %s\n", lexeme, "Linha: %d", input_buffer->line_number);                    
                return setToken(ERROR, lexeme, input_buffer->line_number);
        }
    }
    current_char = get_next_char(input_buffer);    

    lexeme[index] = '\0';

    freeInputBuffer(input_buffer);
    return token;
}