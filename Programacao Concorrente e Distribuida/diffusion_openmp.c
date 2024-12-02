
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 2000      // Tamanho da grade
#define T 1000      // Número de iterações no tempo
#define D 0.1       // Coeficiente de difusão
#define DELTA_T 0.01
#define DELTA_X 1.0

void diff_eq(double **C, double **C_new) {
    for (int t = 0; t < T; t++) {
        #pragma omp parallel for collapse(2)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                C_new[i][j] = C[i][j] + D * DELTA_T * (
                    (C[i+1][j] + C[i-1][j] + C[i][j+1] + C[i][j-1] - 4 * C[i][j]) / (DELTA_X * DELTA_X)
                );
            }
        }

        // Atualizar matriz para a próxima iteração
        double difmedio = 0.0;
        #pragma omp parallel for reduction(+:difmedio) collapse(2)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                difmedio += fabs(C_new[i][j] - C[i][j]);
                C[i][j] = C_new[i][j];
            }
        }

        if ((t % 100) == 0)
            printf("Iteração %d - Diferença média = %g\n", t, difmedio / ((N - 2) * (N - 2)));
    }
}

int main() {
    // Concentração inicial
    double **C = (double **)malloc(N * sizeof(double *));
    double **C_new = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        C[i] = (double *)malloc(N * sizeof(double));
        C_new[i] = (double *)malloc(N * sizeof(double));
        for (int j = 0; j < N; j++) {
            C[i][j] = 0.0;
            C_new[i][j] = 0.0;
        }
    }

    // Inicializar uma concentração alta no centro
    C[N / 2][N / 2] = 1.0;

    // Executar as iterações no tempo para a equação de difusão
    double start_time = omp_get_wtime();
    diff_eq(C, C_new);
    double end_time = omp_get_wtime();

    // Exibir resultado final e tempo de execução
    printf("Concentração final no centro: %f\n", C[N / 2][N / 2]);
    printf("Tempo de execução: %f segundos\n", end_time - start_time);

    // Liberar memória
    for (int i = 0; i < N; i++) {
        free(C[i]);
        free(C_new[i]);
    }
    free(C);
    free(C_new);

    return 0;
}
