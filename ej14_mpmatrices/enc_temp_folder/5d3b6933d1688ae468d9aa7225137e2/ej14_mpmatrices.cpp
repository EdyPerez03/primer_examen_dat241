// ej14_mpmatrices.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4 // Dimensión de la matriz

void multiply(int a[N][N], int b[N][N], int c[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i][j] = 0;
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(int argc, char** argv) {
    int rank, size;
    int a[N][N], b[N][N], c[N][N] = { 0 };

    // Inicializa MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Inicializa las matrices en el proceso maestro
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = i + j; // Matriz A
                b[i][j] = i - j; // Matriz B
            }
        }
    }

    // Envío de la matriz B a todos los procesos
    MPI_Bcast(b, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada proceso calcula su parte de la matriz C
    for (int i = rank; i < N; i += size) {
        for (int j = 0; j < N; j++) {
            c[i][j] = 0;
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    // El proceso maestro recoge los resultados
    MPI_Gather(c, N / size * N, MPI_INT, c, N / size * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Imprime el resultado en el proceso maestro
    if (rank == 0) {
        printf("Resultado de la multiplicación de matrices:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    }

    // Finaliza MPI
    MPI_Finalize();
    return 0;
}
