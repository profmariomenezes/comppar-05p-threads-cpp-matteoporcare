#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiply_by_row(int **A, int **B, int **C, int M, int N, int X) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < X; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int M = 1000, N = 1000, X = 1000; // Dimensões das matrizes
    int **A, **B, **C;

    A = (int **)malloc(M * sizeof(int *));
    B = (int **)malloc(N * sizeof(int *));
    C = (int **)malloc(M * sizeof(int *));
    for (int i = 0; i < M; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(X * sizeof(int));
    }
    for (int i = 0; i < N; i++) {
        B[i] = (int *)malloc(X * sizeof(int));
    }

    srand(time(0));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < X; j++) {
            B[i][j] = rand() % 10;
        }
    }

    clock_t start = clock();
    multiply_by_row(A, B, C, M, N, X);
    clock_t end = clock();
    printf("Tempo de execução (linha): %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    for (int i = 0; i < M; i++) {
        free(A[i]);
        free(C[i]);
    }
    for (int i = 0; i < N; i++) {
        free(B[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
