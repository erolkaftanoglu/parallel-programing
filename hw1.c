#include <stdio.h>
#include "math.h"
#include "mpi.h"
#define N 5000000
#define PI acos(-1)

double f( double x ) { 
     return 4.0 / ( 1.0 + x * x);
}

int main(void) {

MPI_Status status;
// MPI_Request request;

MPI_Init(NULL, NULL);

int rank, size;

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

double a = 0.0, b = 1.0, toplam = 0.0;
double h = ( b - a ) / (double)N;
int chunk = N / size;

int i;

for (i = rank * chunk; i < (rank+1)*chunk; i++) {
     toplam += f( i * h );
}

toplam *= h;

printf("%d no'lu process -> toplam = %1.10f\n", rank, toplam);

if ( rank != 0 ) {
     MPI_Send(&toplam, 1, MPI_DOUBLE, 0, 100, MPI_COMM_WORLD);
} else {
     double t1, t2, t3;
     MPI_Recv(&t1, 1, MPI_DOUBLE, 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
     MPI_Recv(&t2, 1, MPI_DOUBLE, 2, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
     MPI_Recv(&t3, 1, MPI_DOUBLE, 3, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
     double sonuc = toplam + t1 + t2 + t3;
     printf("Gercek PI   = %1.10f\n", PI);          
     printf("Yaklasik PI = %1.10f\n", sonuc);
}

MPI_Finalize();

}