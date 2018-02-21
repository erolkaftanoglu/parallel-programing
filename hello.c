#include <stdio.h>
#include <mpi.h>

int power (int a, int b) {
  if(a != 0 && b == 0) return 1;
  else {
    int j,multy = 1;
    for(j = 0; j <= b; j++) {
      multy *= a;
    }
    return multy;
  } 
}

int main(void) {

  MPI_Init(NULL,NULL);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int dizi[10] = {1,2,3,4,5,6,78,9,9,0};
  int i, sum = 0;
  for(i = 0; i < 10; i++) 
    sum += power(dizi[i],rank);

  printf("rank: %d, sayilarin: %d kuvetleri: %d  \n", rank, rank, sum);

  MPI_Finalize();


  //printf("Hello world");

  return 0;
} 
