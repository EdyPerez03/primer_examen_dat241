#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4 // Tamaño de las matrices

void multiply_matrices(int local_A[N][N], int B[N][N], int C[N][N], int rank, int rows_per_process) {
    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0; // Inicializa el resultado
            for (int k = 0; k < N; k++) {
                C[i][j] += local_A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char** argv) {
    int rank, size;
    int A[N][N], B[N][N], C[N][N]; // Matrices globales
    int local_A[N][N]; // Buffer para filas de A en cada proceso
    int rows_per_process; // Filas que procesará cada proceso

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Inicializar matrices A y B solo en el proceso 0
    if (rank == 0) {
        int count = 1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = count++;
                B[i][j] = count++;
            }
        }

        // Imprimir matrices A y B
        printf("Matriz A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }

        printf("Matriz B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", B[i][j]);
            }
            printf("\n");
        }
    }

    // Enviar la matriz B a todos los procesos
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Calcular cuántas filas de A se enviarán a cada proceso
    rows_per_process = N / size;

    // El proceso 0 envía sus filas de la matriz A a cada proceso
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Send(&A[i * rows_per_process], rows_per_process * N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        // Copiar filas para el propio proceso 0
        for (int i = 0; i < rows_per_process; i++) {
            for (int j = 0; j < N; j++) {
                local_A[i][j] = A[i][j];
            }
        }
    }
    else {
        // Los procesos que no son el 0 reciben sus filas de la matriz A
        MPI_Recv(local_A, rows_per_process * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Multiplicar matrices
    int C_local[N][N]; // Buffer para resultados locales
    multiply_matrices(local_A, B, C_local, rank, rows_per_process);

    // El proceso 0 recibe los resultados de los otros procesos
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&C[i * rows_per_process], rows_per_process * N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        // Copiar las filas calculadas por el propio proceso 0
        for (int i = 0; i < rows_per_process; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = C_local[i][j];
            }
        }
    }
    else {
        // Cada proceso envía sus resultados al proceso 0
        MPI_Send(C_local, rows_per_process * N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Imprimir el resultado solo en el proceso 0
    if (rank == 0) {
        printf("Resultado de la multiplicacion de matrices C = A * B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
