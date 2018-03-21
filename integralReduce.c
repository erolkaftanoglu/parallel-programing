#include <stdio.h>
#include "math.h"
#include "mpi.h"
#define N 50000000000
#define PI acos(-1)

double f(double x)
{
    return 4.0 / (1.0 + x * x);
}

int main(void)
{
    double totalTimeStart = 0.0;
    double totalTimeFinish = 0.0;
    
    double commTimeStart = 0.0;
    double commTimeFinish = 0.0;

    MPI_Init(NULL, NULL);

    totalTimeStart = MPI_Wtime();
    commTimeStart = MPI_Wtime();
    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double a = 0.0, b = 1.0, toplam = 0.0, sonuc = 0.0;
    double h = (b - a) / (double)N;
    int chunk = N / size;

    int i;

    for (i = rank * chunk; i < (rank + 1) * chunk; i++)
    {
        toplam += f(i * h);
    }

    toplam *= h;

    commTimeStart = MPI_Wtime();
    // printf("%d no'lu process -> toplam = %1.10f\n", rank, toplam);
    MPI_Reduce(&toplam, &sonuc, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    commTimeFinish = MPI_Wtime();

    if (rank == 0)
    {
        //printf("Gercek PI   = %1.20f\n", PI);
       // printf("Yaklasik PI = %1.20f\n", sonuc);
    }

    /*
if ( rank != 0 ) {
     MPI_Send(&toplam, 1, MPI_DOUBLE, 0, 100, MPI_COMM_WORLD);
} else {
     double t1, t2, t3;
     MPI_Recv(&t1, 1, MPI_DOUBLE, 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
     MPI_Recv(&t2, 1, MPI_DOUBLE, 2, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
     MPI_Recv(&t3, 1, MPI_DOUBLE, 3, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
     double sonuc = toplam + t1 + t2 + t3;
     //printf("Gercek PI   = %1.10f\n", PI);          
     //printf("Yaklasik PI = %1.10f\n", sonuc);
}
*/

    totalTimeFinish = MPI_Wtime();

    if(rank == 0) {
        //printf("Time: %f | %f | %f \n", totalTimeStart, totalTimeFinish, (totalTimeFinish-totalTimeStart));
        //printf("TimeC: %f | %f | %f \n", commTimeStart, commTimeFinish,(totalTimeFinish-totalTimeStart));
        
    }
    //printf("Time: %f | %f | %f \n", totalTimeStart, totalTimeFinish, (totalTimeFinish-totalTimeStart));
    printf("%d no'lu process -> total time = %f \n", rank, (totalTimeFinish-totalTimeStart));
    printf("%d no'lu process -> comm time = %f \n", rank, (commTimeFinish-commTimeStart));
    

    MPI_Finalize();
}