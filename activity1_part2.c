#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int process_rank, process_count;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    if (process_rank == 0) {
        // Master process
        char greeting[] = "Hello, World!";
        // Broadcast the greeting message to all worker processes
        MPI_Bcast(greeting, strlen(greeting) + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    } else {
        // Worker processes
        char received_message[100]; // Assuming max message length is 100 characters
        // Receive the broadcast message from the master process
        MPI_Bcast(received_message, 100, MPI_CHAR, 0, MPI_COMM_WORLD);
        printf("Process %d received broadcast message: %s\n", process_rank, received_message);
    }

    MPI_Finalize();
    return 0;
}
