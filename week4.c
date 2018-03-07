#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main (void) {
    int size, rank, i, status1,si_status2;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        double dizi_0[100];
        for (i = 0; i < 100; i++) {
            dizi_0[i] = (double) i + 1.0;
        }
        MPI_Send(dizi_0, 50, MPI_DOUBLE,1,113, MPI_WORLD);
        MPI_Send(&dizi_0[50], 25, MPI_DOUBLE,1,113, MPI_WORLD);
    } else if (rank == 1) {
        double dizi_1[50] = {0};
        MPI_Recv(&dizi_1,50,MPI_DOUBLE,1,113, MPI_WORLD,  &status1)
    }
    
}