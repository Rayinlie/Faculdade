#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 2000      // Tamanho da grade
#define T 1000      // Número de iterações no tempo
#define D 0.1       // Coeficiente de difusão
#define DELTA_T 0.01
#define DELTA_X 1.0

void diff_eq(double **C, double **C_new, int num_threads) {
    omp_set_num_threads(num_threads);
    for (int t = 0; t < T; t++) {
        #pragma omp parallel for collapse(2)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                C_new[i][j] = C[i][j] + D * DELTA_T * (
                    (C[i+1][j] + C[i-1][j] + C[i][j+1] + C[i][j-1] - 4 * C[i][j]) / (DELTA_X * DELTA_X)
                );
            }
        }
        double difmedio = 0.0;
        #pragma omp parallel for collapse(2) reduction(+:difmedio)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                difmedio += fabs(C_new[i][j] - C[i][j]);
                C[i][j] = C_new[i][j];
            }
        }
        if ((t % 100) == 0)
            printf("Interação %d - Diferença média=%g\n", t, difmedio/((N-2)*(N-2)));
    }
}

int main(int argc, char *argv[]) {
    int num_threads = 1; // Padrão 1 núcleo
    if (argc > 1) {
        num_threads = atoi(argv[1]);
    }

    // Concentração inicial
    double **C = (double **)malloc(N * sizeof(double *));
    double **C_new = (double **)malloc(N * sizeof(double *));
    if (C == NULL || C_new == NULL) {
        fprintf(stderr, "Falha na alocação de memória\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        C[i] = (double *)malloc(N * sizeof(double));
        C_new[i] = (double *)malloc(N * sizeof(double));
        if (C[i] == NULL || C_new[i] == NULL) {
            fprintf(stderr, "Falha na alocação de memória\n");
            return 1;
        }
        for (int j = 0; j < N; j++) {
            C[i][j] = 0.0;
            C_new[i][j] = 0.0;
        }
    }
    C[N/2][N/2] = 1.0; // Inicializar concentração alta no centro

    // Executar a simulação
    diff_eq(C, C_new, num_threads);

    // Exibir resultado final no centro da grade
    printf("Concentração final no centro: %f\n", C[N/2][N/2]);

    // Liberar memória
    for (int i = 0; i < N; i++) {
        free(C[i]);
        free(C_new[i]);
    }
    free(C);
    free(C_new);

    return 0;
}