#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include "time.h"
#define POINTNUMBER 1000
#define TAG = 777

int main(void) {
    int size, rank, i, alt = 0, ust = 0;

    double x, y;

    MPI_Status status;

    MPI_Init(NULL,NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    srand(time(NULL));

    for(i = 0; i <= POINTNUMBER; i++) {
        x = (int) (rand() / (double) (RAND_MAX + 1) * 2);
        y = (int) (rand() / (double) (RAND_MAX + 1) * 2);
        if (x*x + y*y < 1) {
            alt++;
        } else if (x*x + y*y > 1) {
            ust++;
        }
    }

    if(rank != 0) {
        MPI_Send(&alt, 1, MPI_INT, 0, TAG+rank, MPI_COMM_WORLD);
        MPI_Send(&ust, 1, MPI_INT, 0, TAG+rank, MPI_COMM_WORLD);
    }else {
        int altDİzi[4], ustDizi[4;
        altDizi[0] = alt;
        ustDizi[0] = ust;

        //alt
        MPI_Recv(&altDizi[1], 1, MPI_INT, 1, TAG+1, MPI_COMM_WORLD, &status);
        MPI_Recv(&altDizi[2], 1, MPI_INT, 2, TAG+2, MPI_COMM_WORLD, &status);
        MPI_Recv(&altDizi[3], 1, MPI_INT, 3, TAG+3, MPI_COMM_WORLD, &status);

        //ust
        MPI_Recv(&ustDizi[1], 1, MPI_INT, 1, TAG+1, MPI_COMM_WORLD, &status);
        MPI_Recv(&ustDizi[2], 1, MPI_INT, 2, TAG+2, MPI_COMM_WORLD, &status);
        MPI_Recv(&ustDizi[3], 1, MPI_INT, 3, TAG+3, MPI_COMM_WORLD, &status);
        
        int altToplam = 0, ustToplam = 0;
        int j;
        for(j=0; i < 4; i++) {
            altToplam += altDizi[i];
            ustToplam += ustDizi[i];
        }
        double pi = 0.0;
        pi = double ((4.0 * altToplam) / ((double)altToplam + (double) ustToplam));
        printf("Yaklasik PI = %1.20f \n", pi);
    }

    MPI_Finalize();
}