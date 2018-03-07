#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "time.h"

enum Players {Federer, Nadal, Referee};

int main (void) {
    srand(time(NULL));

    int size, name, i, number = 0, TAG = 100;

    MPI_Status status;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &name);


    int playCount = 10;

    int first = (int) rand() % 2;
    if(first == Federer && name == Federer) {
        number = 1 + rand() % 11;
        printf("Once Federer %d , sayisini cekti \n",number);
    } else if(first == Nadal && name == Federer) {
        number = 1 + rand() %11;
        printf("once Nadal %d, sayisini cekti \n", number );

    } else if(first == Nadal && name == Federer) {
        number = 1 + rand() % 11;
        printf("sonra federer %d sayisi", number);
    } else if(first == Federer && name == Nadal) {
        number = 1 + rand() % 11;
        printf("sonra Federer %d sayisi Nadal", number);
    } 
    MPI_Finalize();

}