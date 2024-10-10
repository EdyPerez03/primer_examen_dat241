#include <stdio.h>
#include <mpi.h>

#define N 10

int main(int argc, char** argv) {
    int rank, size;
    int a[N], b[N], c[N]; // El vector c también debe ser de tamaño N

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

    // Suma de vectores
    for (int i = rank; i < N; i += size) {
        c[i] = a[i] + b[i];
    }

    // El número de elementos a reunir debe ser consistente para cada proceso
    int local_count = N / size + (rank < N % size ? 1 : 0); // Para manejar casos donde N no es divisible por size

    // Reúne el resultado en el proceso maestro
    int recvcounts[size]; // Cantidades a recibir
    int displs[size]; // Desplazamientos

    // Calcular recvcounts y displs
    for (int i = 0; i < size; i++) {
        recvcounts[i] = N / size + (i < N % size ? 1 : 0);
        displs[i] = (i > 0) ? displs[i - 1] + recvcounts[i - 1] : 0;
    }

    MPI_Gatherv(c, local_count, MPI_INT, c, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    // Imprime el resultado en el proceso maestro
    if (rank == 0) {
        printf("Resultado de la suma:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", c[i]);
        }
        printf("\n");
    }

    // Finaliza MPI
    MPI_Finalize();
    return 0;
}
