#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc,char **argv){
	MPI_Init(&argc,&argv);

	int mpirank, mpisize;
 	MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
  	MPI_Comm_size(MPI_COMM_WORLD, &mpisize);

	int n;
	if (mpirank == 0){
		n=10;
		MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);	
		printf("Process 0 sent number %d \n",n);
        }
	else if (mpirank == 1){
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Process 1 received number %d from process 0\n",n);
	}
	
	MPI_Finalize();
	return 0;
}
