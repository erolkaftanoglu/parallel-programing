#include <stdio.h>
#include <mpi.h>

int main(void) {

  MPI_Init(NULL,NULL);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int dizi[10] = {1,2,3,4,5,6,78,9,9,0};
  int i, sum = 0;
  switch(rank) {
    case 0: puts("I am the master"); break;
    case 1: for(i = 0; i<10; i++) sum+=dizi[i]; printf("sayilarin toplami %d\n", sum); break;
    case 2: for(i = 0; i<10; i++) sum+=dizi[i]*dizi[i]; printf("sayilarin toplami %d\n", sum); break;
    case 3: for(i = 0; i<10; i++) sum+=dizi[i]*dizi[i]*dizi[i]; printf("sayilarin toplami %d\n", sum); break;
  }

  printf("Process sayisi = %d \n", size);

  MPI_Finalize();


  //printf("Hello world");

  return 0;
} 
