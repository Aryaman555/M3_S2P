#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int process_rank, num_processes;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    if (process_rank == 0) {
        // Master process
        char message[] = "Hello, World!";
        for (int dest_rank = 1; dest_rank < num_processes; dest_rank++) {
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, dest_rank, 0, MPI_COMM_WORLD);
        }
    } else {
        // Worker processes
        char received_message[100]; 
        MPI_Recv(received_message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received message: %s\n", process_rank, received_message);
    }

    MPI_Finalize();
    return 0;
}
