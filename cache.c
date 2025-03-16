#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BLOCK_SIZE 64

void multiply_with_blocking(int **A, int **B, int **C, int M, int N, int X) {
    for (int i = 0; i < M; i += BLOCK_SIZE) {
        for (int j = 0; j < X; j += BLOCK_SIZE) {
            for (int k = 0; k < N; k += BLOCK_SIZE) {
                for (int ii = i; ii < i + BLOCK_SIZE && ii < M; ii++) {
                    for (int jj = j; jj < j + BLOCK_SIZE && jj < X; jj++) {
                        for (int kk = k; kk < k + BLOCK_SIZE && kk < N; kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
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
    multiply_with_blocking(A, B, C, M, N, X);
    clock_t end = clock();
    printf("Tempo de execução (bloco): %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

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
