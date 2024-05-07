#include "funcs.h"



void addToHashTable(HashTable* table, const char* key, int type, int scope, int line, bool isDeclared)
void traverseTreeAndClassify(HashTable* table, const char* key, int type, int scope, int line, bool isDeclared, HashTable* variableTable, HashTable* declarationTable)
HashTable createSymbolTable();
void printSymbolTable(HashTable* table);
void freeSymbolTable(HashTable* table);
void classifyVariables(HashTable* table, char *entry);
void checkUndeclaredVariables(HashTable* table);
void checkUndeclaredFunctions(HashTable* table);
void checkMultipleDeclarations(HashTable* table);
