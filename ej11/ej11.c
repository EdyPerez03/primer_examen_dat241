#include <stdio.h>
#include <stdlib.h> // Necesario para malloc y free
#include <mpi.h>

#define N 10

int main(int argc, char** argv) {
    int rank, size;
    int a[N], b[N], * c; // 'c' se declara como puntero para usar malloc
    int* recvcounts, * displs; // Punteros para recibir los counts y displacements

    // Inicializa MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Inicializa los vectores en el proceso maestro
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            a[i] = i + 1; // Vector a
            b[i] = (i + 1) * 2; // Vector b
        }
    }

    // Envío de los vectores a todos los procesos
    MPI_Bcast(a, N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Asigna memoria para el vector c
    c = (int*)malloc(N * sizeof(int));

    // Suma de vectores
    for (int i = rank; i < N; i += size) {
        c[i] = a[i] + b[i];
    }

    // El número de elementos a reunir debe ser consistente para cada proceso
    int local_count = N / size + (rank < N % size ? 1 : 0); // Maneja casos donde N no es divisible por size

    // Asignación dinámica para recvcounts y displs
    recvcounts = (int*)malloc(size * sizeof(int));
    displs = (int*)malloc(size * sizeof(int));

    // Calcular recvcounts y displs
    for (int i = 0; i < size; i++) {
        recvcounts[i] = N / size + (i < N % size ? 1 : 0);
        displs[i] = (i > 0) ? displs[i - 1] + recvcounts[i - 1] : 0;
    }

    // Nuevo buffer para recibir los datos en el proceso maestro
    int* recv_buffer = (int*)malloc(N * sizeof(int)); // Buffer para almacenar los resultados reunidos

    // Reúne el resultado en el proceso maestro
    MPI_Gatherv(c, local_count, MPI_INT, recv_buffer, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    // Imprime el resultado en el proceso maestro
    if (rank == 0) {
        printf("Resultado de la suma:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", recv_buffer[i]); // Usa recv_buffer aquí
        }
        printf("\n");
    }

    // Libera la memoria asignada
    free(c);
    free(recvcounts);
    free(displs);
    free(recv_buffer);

    // Finaliza MPI
    MPI_Finalize();
    return 0;
}
