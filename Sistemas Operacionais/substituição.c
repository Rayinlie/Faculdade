#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUM_PAGINAS 10 // Número de páginas distintas (0 a 9)
#define TAMANHO_SEQUENCIA 20 // Tamanho da sequência de referências de páginas

// Função para gerar uma sequência de referências de páginas aleatória
void gerar_sequencia_referencias(int* pages, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        pages[i] = rand() % NUM_PAGINAS;
    }
}

// Função para verificar se a página está nos quadros (retorna o índice ou -1)
int esta_nos_quadros(int* frames, int num_frames, int page) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return -1;
}

// Algoritmo de substituição de páginas FIFO
int fifo(int* pages, int tamanho, int num_frames) {
    int* frames = (int*)malloc(num_frames * sizeof(int));
    int page_faults = 0;
    int index = 0; // Índice para substituir páginas

    for (int i = 0; i < tamanho; i++) {
        if (esta_nos_quadros(frames, num_frames, pages[i]) == -1) {
            frames[index] = pages[i];
            index = (index + 1) % num_frames;
            page_faults++;
        }
    }

    free(frames);
    return page_faults;
}

// Algoritmo de substituição de páginas LRU
int lru(int* pages, int tamanho, int num_frames) {
    int* frames = (int*)malloc(num_frames * sizeof(int));
    int* timestamps = (int*)malloc(num_frames * sizeof(int));
    int page_faults = 0;
    int time = 0;

    for (int i = 0; i < tamanho; i++) {
        int idx = esta_nos_quadros(frames, num_frames, pages[i]);

        if (idx == -1) { // Página não encontrada, ocorrerá falta de página
            int lru_index = 0;
            for (int j = 1; j < num_frames; j++) {
                if (timestamps[j] < timestamps[lru_index]) {
                    lru_index = j;
                }
            }
            frames[lru_index] = pages[i];
            timestamps[lru_index] = time;
            page_faults++;
        } else { // Página encontrada, atualizar timestamp
            timestamps[idx] = time;
        }
        time++;
    }

    free(frames);
    free(timestamps);
    return page_faults;
}

int main() {
    srand(time(NULL)); // Inicializar semente aleatória

    int pages[TAMANHO_SEQUENCIA];
    gerar_sequencia_referencias(pages, TAMANHO_SEQUENCIA);

    printf("Sequência de Referências de Páginas: ");
    for (int i = 0; i < TAMANHO_SEQUENCIA; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\n");

    // Aplicar os algoritmos de substituição para diferentes números de quadros
    for (int num_frames = 1; num_frames <= 7; num_frames++) {
        int fifo_faults = fifo(pages, TAMANHO_SEQUENCIA, num_frames);
        int lru_faults = lru(pages, TAMANHO_SEQUENCIA, num_frames);

        printf("Com %d quadros: FIFO = %d faltas de página, LRU = %d faltas de página\n", num_frames, fifo_faults, lru_faults);
    }

    return 0;
}