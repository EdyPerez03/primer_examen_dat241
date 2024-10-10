#include <stdio.h>
#include <mpi.h>
#include <string.h>

#define MAX_LEN 100
#define ARRAY_SIZE 10

int main(int argc, char** argv) {
    int rank, size;
    char strings[ARRAY_SIZE][MAX_LEN] = {
        "Cero", "Uno", "Dos", "Tres", "Cuatro",
        "Cinco", "Seis", "Siete", "Ocho", "Nueve"
    };

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 3) {
        if (rank == 0) {
            printf("Este programa requiere exactamente 3 procesos.\n");
        }
        MPI_Finalize();
        return 0;
    }

    // Proceso 0 envía datos a los otros procesos
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                if (i == 1 && j % 2 == 0) { // Proceso 1 (pares)
                    MPI_Send(strings[j], MAX_LEN, MPI_CHAR, i, 0, MPI_COMM_WORLD);
                }
                else if (i == 2 && j % 2 != 0) { // Proceso 2 (impares)
                    MPI_Send(strings[j], MAX_LEN, MPI_CHAR, i, 0, MPI_COMM_WORLD);
                }
            }
        }
    }
    else {
        // Proceso 1 y 2 reciben datos
        for (int j = (rank - 1); j < ARRAY_SIZE; j += 2) {
            char received_string[MAX_LEN];
            MPI_Recv(received_string, MAX_LEN, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Proceso %d recibio: %s\n", rank, received_string);
        }
    }

    // Finalizar MPI
    MPI_Finalize();
    return 0;
}
