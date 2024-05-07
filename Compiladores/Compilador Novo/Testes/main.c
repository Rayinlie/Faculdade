#include "funcs.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: compila <filename>\n");
        return 1;
    }

    InputBuffer *input_buffer = createInputBuffer(argv[1]);
    KeywordNode *keyword_tree = createKeywordTree();

    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    Token token;

    do {
        token = getNextToken(input_buffer, keyword_tree);
        if (token.type != EOF) {
            printf("Token: %s, Tipo: %d, Linha: %d\n", token.lexeme, token.type, token.line_number);
            fprintf(output_file, "Token: %s, Tipo: %d, Linha: %d\n", token.lexeme, token.type, token.line_number);
        } 
    } while (token.type != EOF);

    fclose(output_file);
    freeInputBuffer(input_buffer);
    freeKeywordTree(keyword_tree);

    return 0;
}
