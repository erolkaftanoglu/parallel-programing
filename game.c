#include <mpi.h>
#include <stdio.h>
#include "mpi.h"

enum Players { Federer, Nadal };

int main (void) {
    int size, name, i, number = 0, TAG = 100;
    MPI_Status status;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int playCount = 10;
    for(i = 1; 1<=10; i++) {
        if(name == Federer) {
            number++;
            MPI_Send(&number, 1, MPI_INT, Nadal, TAG+i, MPI_COMM_WORLD);
            MPI_Recv(&number, 1, MPI_INT, Nadal, TAG+playCount+i, MPI_COMM_WORLD, &status);
        } else if(name == Nadal){
            MPI_Recv(&number, 1, MPI_INT, Nadal, TAG+i, MPI_COMM_WORLD, &status);
            number++;
            MPI_Send(&number, 1, MPI_INT, Nadal, TAG+playCount+i, MPI_COMM_WORLD);
        }

    }
    MPI_Finalize();

}