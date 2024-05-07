#include "funcs.h"

InputBuffer *createInputBuffer(const char *filename) {
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    input_buffer->file = fopen(filename, "r");
    input_buffer->position = 0;
    input_buffer->line_number = 1;
    return input_buffer;
}

void freeInputBuffer(InputBuffer *input_buffer) {
    fclose(input_buffer->file);
    free(input_buffer);
}

char get_next_char(InputBuffer *input_buffer) {
    if (input_buffer->position == 0 || input_buffer->position == BUFFER_SIZE) {
        int bytes_read = fread(input_buffer->buffer, sizeof(char), BUFFER_SIZE, input_buffer->file);
        input_buffer->position = 0;
        if (bytes_read == 0) {
            return EOF;
        }
    }

    char current_char = input_buffer->buffer[input_buffer->position];
    if (current_char == '\n') {
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

int isIdentifier(const char *str) {
    int state = 0;
    int i = 0;
    char current_char = str[i];

    while (current_char != '\0') {
        switch (state) {
            case 0:
                if (isalpha(current_char) || current_char == '_') {
                    state = 1;
                } else {
                    return 0;
                }
                break;
            case 1:
                if (isalnum(current_char) || current_char == '_') {
                    // Continua no estado 1
                } else {
                    return 0;
                }
                break;
            default:
                return 0;
        }
        i++;
        current_char = str[i];
    }

    return (state == 1);
}

int isInteger(const char *str) {
    int state = 0;
    int i = 0;
    char current_char = str[i];

    while (current_char != '\0') {
        switch (state) {
            case 0:
                if (isdigit(current_char) && current_char != '0') {
                    state = 1;
                } else {
                    return 0;
                }
                break;
            case 1:
                if (isdigit(current_char)) {
                    // Continua no estado 1
                } else {
                    return 0;
                }
                break;
            default:
                return 0;
        }
        i++;
        current_char = str[i];
    }

    return (state == 1);
}

int isMathOperator(char ch) {
    int state = 0;

    switch (ch) {
        case '+':
            state = 1;
            break;
        case '-':
            state = 2;
            break;
        case '*':
            state = 3;
            break;
        case '/':
            state = 4;
            break;
        default:
            state = -1;
            break;
    }

    return state;
}

int isLogicalOperator(char ch) {
    int state = 0;

    switch (ch) {
        case '<':
            state = 1;
            break;
        case '>':
            state = 2;
            break;
        case '=':
            state = 3;
            break;
        default:
            state = -1;
            break;
    }

    return state;
}

Token getNextToken(InputBuffer *input_buffer) {
    Token token;
    char ch = get_next_char(input_buffer);

    while (isspace(ch)) {
        if (ch == '\n') {
            return token;
        }
        ch = get_next_char(input_buffer);
    }

    if (ch == '/') {
        char next_char = get_next_char(input_buffer);
        if (next_char == '*') {
            // Início de um comentário /* ... */
            char prev_char = '\0'; // Caractere anterior ao atual
            while (1) {
                ch = get_next_char(input_buffer);
                if (ch == EOF) {
                    token.type = ERROR;
                    printf("ERRO LÉXICO: Comentário não finalizado LINHA: %d\n", input_buffer->line_number);
                    return token;
                }
                if (prev_char == '*' && ch == '/') {
                    // Fim do comentário
                    break;
                }
                prev_char = ch;
            }
            ch = get_next_char(input_buffer); // Avança para o próximo caractere após o comentário fechado
            return getNextToken(input_buffer); // Chama recursivamente para analisar o próximo token
        } else {
            retract_char(input_buffer);
        }
    }

    int math_state = isMathOperator(ch);
    int logical_state = isLogicalOperator(ch);

    switch (math_state) {
        case 1:
            token.lexeme[0] = ch;
            token.lexeme[1] = '\0';
            token.type = SYMBOL_PLUS;
            break;
        case 2:
            token.lexeme[0] = ch;
            token.lexeme[1] = '\0';
            token.type = SYMBOL_MINUS;
            break;
        case 3:
            token.lexeme[0] = ch;
            token.lexeme[1] = '\0';
            token.type = SYMBOL_TIMES;
            break;
        case 4:
            token.lexeme[0] = ch;
            token.lexeme[1] = '\0';
            token.type = SYMBOL_DIVIDE;
            break;
        default:
            switch (logical_state) {
                case 1: {
                    char next_char = get_next_char(input_buffer);
                    if (next_char == '=') {
                        token.lexeme[0] = ch;
                        token.lexeme[1] = next_char;
                        token.lexeme[2] = '\0';
                        token.type = SYMBOL_LESS_THAN_OR_EQUAL;
                    } else {
                        token.lexeme[0] = ch;
                        token.lexeme[1] = '\0';
                        token.type = SYMBOL_LESS_THAN;
                        retract_char(input_buffer);
                    }
                    break;
                }
                case 2: {
                    char next_char = get_next_char(input_buffer);
                    if (next_char == '=') {
                        token.lexeme[0] = ch;
                        token.lexeme[1] = next_char;
                        token.lexeme[2] = '\0';
                        token.type = SYMBOL_GREATER_THAN_OR_EQUAL;
                    } else {
                        token.lexeme[0] = ch;
                        token.lexeme[1] = '\0';
                        token.type = SYMBOL_GREATER_THAN;
                        retract_char(input_buffer);
                    }
                    break;
                }
                case 3: {
                    char next_char = get_next_char(input_buffer);
                    if (next_char == '=') {
                        token.lexeme[0] = ch;
                        token.lexeme[1] = next_char;
                        token.lexeme[2] = '\0';
                        token.type = SYMBOL_EQUAL;
                    } else {
                        token.lexeme[0] = ch;
                        token.lexeme[1] = '\0';
                        token.type = ERROR;
                        printf("ERRO LÉXICO: %c LINHA: %d\n", ch, input_buffer->line_number);
                        retract_char(input_buffer);
                    }
                    break;
                }
                default:
                    if (isalpha(ch) || ch == '_') {
                        int i = 0;
                        token.lexeme[i++] = ch;
                        ch = get_next_char(input_buffer);
                        while (isalnum(ch) || ch == '_') {
                            token.lexeme[i++] = ch;
                            ch = get_next_char(input_buffer);
                        }
                        token.lexeme[i] = '\0';

                        if (isIdentifier(token.lexeme)) {
                            token.type = IDENTIFIER;
                        } else {
                            token.type = ERROR;
                            printf("ERRO LÉXICO: %s LINHA: %d\n", token.lexeme, input_buffer->line_number);
                        }
                        retract_char(input_buffer);
                    } else if (isdigit(ch)) {
                        int i = 0;
                        token.lexeme[i++] = ch;
                        ch = get_next_char(input_buffer);
                        while (isdigit(ch)) {
                            token.lexeme[i++] = ch;
                            ch = get_next_char(input_buffer);
                        }
                        token.lexeme[i] = '\0';
                        if (!isInteger(token.lexeme)) {
                            token.type = ERROR;
                            printf("ERRO LÉXICO: %s LINHA: %d\n", token.lexeme, input_buffer->line_number);
                        } else {
                            token.type = NUMBER;
                        }
                        retract_char(input_buffer);
                    } else if (ch == ';') {
                        token.lexeme[0] = ch;
                        token.lexeme[1] = '\0';
                        token.type = SYMBOL_SEMICOLON;
                    } else if (ch == '(') {
                        token.lexeme[0] = ch;
                        token.lexeme[1] = '\0';
                        token.type = SYMBOL_LEFT_PARENTHESIS;
                    } else if (ch == ')') {
                        token.lexeme[0] = ch;
                        token.lexeme[1] = '\0';
                        token.type = SYMBOL_RIGHT_PARENTHESIS;
                    } else {
                        token.lexeme[0] = ch;
                        token.lexeme[1] = '\0';
                        token.type = ERROR;
                        printf("ERRO LÉXICO: %c LINHA: %d\n", ch, input_buffer->line_number);
                    }
                    break;
            }
            break;
    }

    return token;
}
