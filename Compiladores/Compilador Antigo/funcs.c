#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lexical_analyzer.h"

TrieNode* createNode() {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    newNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(TrieNode* root, const char* word) {
    TrieNode* currentNode = root;
    int length = strlen(word);

    for (int level = 0; level < length; level++) {
        int index = CHAR_TO_INDEX(word[level]);
        if (!currentNode->children[index]) {
            currentNode->children[index] = createNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->isEndOfWord = true;
}

bool search(TrieNode* root, const char* word) {
    TrieNode* currentNode = root;
    int length = strlen(word);

    for (int level = 0; level < length; level++) {
        int index = CHAR_TO_INDEX(word[level]);
        if (!currentNode->children[index]) {
            return false;
        }
        currentNode = currentNode->children[index];
    }
    return (currentNode != NULL && currentNode->isEndOfWord);
}

void freeTrie(TrieNode* root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            freeTrie(root->children[i]);
        }
    }
    free(root);
}

void initializeBuffer(InputBuffer* inputBuffer) {
    memset(inputBuffer->buffer, 0, sizeof(inputBuffer->buffer));
    inputBuffer->currentPosition = 0;
    inputBuffer->lineNumber = 1;
}

char getNextChar(InputBuffer* inputBuffer) {
    if (inputBuffer->currentPosition >= BUFFER_SIZE || inputBuffer->buffer[inputBuffer->currentPosition] == '\0') {
        return '\0';
    }
    return inputBuffer->buffer[inputBuffer->currentPosition++];
}

void unreadChar(InputBuffer* inputBuffer) {
    if (inputBuffer->currentPosition > 0) {
        inputBuffer->currentPosition--;
    }
}

const char* keywords[] = {"int", "void", "while", "if", "else", "return", "main"};
const char* logicalOperators[] = {"==", "!=", "<", ">", "<=", ">="};
const char* simpleMathOps[] = {"+", "-", "*", "/"};
const char* complexMathOps[] = {"="};

bool isKeyword(const char* word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(keywords[i], word) == 0) {
            return true;
        }
    }
    return false;
}

bool isLogicalOperator(const char* symbol) {
    for (int i = 0; i < sizeof(logicalOperators) / sizeof(logicalOperators[0]); i++) {
        if (strcmp(logicalOperators[i], symbol) == 0) {
            return true;
        }
    }
    return false;
}

bool isSimpleMathOp(const char* symbol) {
    for (int i = 0; i < sizeof(simpleMathOps) / sizeof(simpleMathOps[0]); i++) {
        if (strcmp(simpleMathOps[i], symbol) == 0) {
            return true;
        }
    }
    return false;
}

bool isComplexMathOp(const char* symbol) {
    for (int i = 0; i < sizeof(complexMathOps) / sizeof(complexMathOps[0]); i++) {
        if (strcmp(complexMathOps[i], symbol) == 0) {
            return true;
        }
    }
    return false;
}

bool isNumber(const char* word) {
    int i = 0;
    while (word[i] != '\0') {
        if (!isdigit(word[i])) {
            return false;
        }
        i++;
    }
    return true;
}

Token* lexicalAnalyzer(InputBuffer* inputBuffer, TrieNode* root) {
    Token* tokens = (Token*)malloc(sizeof(Token) * BUFFER_SIZE);
    int tokenCount = 0;
    char lexeme[MAX_WORD_LENGTH] = "";

    int i = 0;
    while (true) {
        char currentChar = getNextChar(inputBuffer);
        if (currentChar == '\0') {
            break;
        }

        if (isalpha(currentChar) || currentChar == '_') {
            int j = 0;
            while (isalnum(currentChar) || currentChar == '_') {
                lexeme[j++] = currentChar;
                currentChar = getNextChar(inputBuffer);
            }
            lexeme[j] = '\0';
            unreadChar(inputBuffer);

            Token token;
            strcpy(token.lexeme, lexeme);
            if (isKeyword(lexeme)) {
                token.type = KEYWORD;
            } else {
                token.type = IDENTIFIER;
            }
            tokens[tokenCount++] = token;

            memset(lexeme, 0, sizeof(lexeme));
        } else if (isdigit(currentChar)) {
            int j = 0;
            while (isdigit(currentChar)) {
                lexeme[j++] = currentChar;
                currentChar = getNextChar(inputBuffer);
            }
            lexeme[j] = '\0';
            unreadChar(inputBuffer);

            Token token;
            strcpy(token.lexeme, lexeme);
            token.type = isNumber(lexeme) ? NUMBER : ERROR;
            tokens[tokenCount++] = token;

            memset(lexeme, 0, sizeof(lexeme));
        } else if (currentChar == ' ' || currentChar == '\t') {
            // Ignore spaces and tabs
        } else if (currentChar == '\n') {
            inputBuffer->lineNumber++;
        } else {
            lexeme[0] = currentChar;
            lexeme[1] = '\0';

            Token token;
            strcpy(token.lexeme, lexeme);

            if (isLogicalOperator(lexeme)) {
                token.type = LOGICAL_OPERATOR;
            } else if (isSimpleMathOp(lexeme)) {
                token.type = SIMPLE_MATH_OP;
            } else if (isComplexMathOp(lexeme)) {
                token.type = COMPLEX_MATH_OP;
            } else if (strcmp(lexeme, "=") == 0) {
                token.type = SYMBOL_ASSIGN;
            } else if (strcmp(lexeme, ";") == 0) {
                token.type = SYMBOL_SEMICOLON;
            } else {
                token.type = ERROR;
            }

            if (token.type == ERROR) {
                printf("ERRO LÉXICO: %s LINHA: %d\n", lexeme, inputBuffer->lineNumber);
            } else {
                tokens[tokenCount++] = token;
            }

            memset(lexeme, 0, sizeof(lexeme));
        }
    }

    Token endToken;
    endToken.type = NEW_LINE;
    tokens[tokenCount++] = endToken;

    return tokens;
}

void printTokens(Token* tokens) {
    int i = 0;
    while (tokens[i].type != NEW_LINE) {
        printf("Lexema: %s, Tipo: %d\n", tokens[i].lexeme, tokens[i].type);
        i++;
    }
}

void readFile(const char* filename, char** input) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    *input = (char*)malloc(fileSize + 1);
    if (*input == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(*input, 1, fileSize, file);
    (*input)[fileSize] = '\0';
    fclose(file);
}

void analyzeFile(const char* filename) {
    char* input = NULL;
    TrieNode* root = createNode();

    readFile(filename, &input);

    InputBuffer inputBuffer;
    initializeBuffer(&inputBuffer);
    strncpy(inputBuffer.buffer, input, strlen(input));

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        insert(root, keywords[i]);
    }

    Token* tokens = lexicalAnalyzer(&inputBuffer, root);
    printTokens(tokens);

    free(input);
    freeTrie(root);
    free(tokens);
}
