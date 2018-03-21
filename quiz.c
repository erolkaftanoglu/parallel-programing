#include <stdio.h>
#include <mpi.h>
#define CHUNK 8
#define CHUNK2 8

int main(void) {
  
	MPI_Init(NULL,NULL);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int local[CHUNK][CHUNK] = {0};

	int array[8][8];
	int i,j, sum = 1;
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			array[i][j] = sum;
			sum++;
			//printf("%d -", array[i][j]);
		}
		//printf("\n");
	} 

	int local[8] = {0};
	int local2[8] = {0};
	int y,toplam, sonuc;

	for (y = 0; y < CHUNK; y++) {
			local[y] = array[rank][y];
	}
	for (x = 0;x < CHUNK; x++) {
			local2[x] = array[rank][x];
	}

	// ic carpim yapıp, toplam ile toplanması gerekiyor

	MPI_Reduce ( &toplam, &sonuc, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );

	if ( rank == 0 )
     printf("Sonuc = %d\n", sonuc);

  MPI_Finalize();

  return 0;
} 