#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#define BUFFER_SIZE 256
#define MAX_WORD_LENGTH 50
#define ALPHABET_SIZE 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode* createNode();
void insert(TrieNode* root, const char* word);
bool search(TrieNode* root, const char* word);
void freeTrie(TrieNode* root);

typedef struct {
    char buffer[BUFFER_SIZE];
    int currentPosition;
    int lineNumber;
} InputBuffer;

void initializeBuffer(InputBuffer* inputBuffer);
char getNextChar(InputBuffer* inputBuffer);
void unreadChar(InputBuffer* inputBuffer);

typedef struct {
    int type;
    char lexeme[MAX_WORD_LENGTH];
    int lineNumber;
} Token;

Token* lexicalAnalyzer(InputBuffer* inputBuffer, TrieNode* root);
void printTokens(Token* tokens);

void readFile(const char* filename, char** input);
void analyzeFile(const char* filename);

#endif
