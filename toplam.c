#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "mpi.h"
#define N 80
#define CHUNK 20

void printVector(int vctr[], int n, int name) {
     int i;
     for (i = 0; i < n; i++) 
          printf("Process %d: a[%d] = %d\n", name, i, vctr[i]);
}

int main(void) {

MPI_Init(NULL, NULL);

int rank, size, i, toplam = 0, sonuc = 0;

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

srand(time(NULL)+rank);

int local[CHUNK] = {0};

for (i = 0; i < CHUNK; i++)
     local[i] = (int)(rand()%11);

for (i = 0; i < CHUNK; i++)
     toplam += local[i];

MPI_Reduce ( &toplam, &sonuc, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );

if ( rank == 0 )
     printf("Sonuc = %d\n", sonuc);

MPI_Finalize();

}