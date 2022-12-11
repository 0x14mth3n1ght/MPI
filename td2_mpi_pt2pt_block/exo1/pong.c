#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc,char **argv){
	MPI_Init(&argc,&argv);

	int mpirank, mpisize;
 	MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
  	MPI_Comm_size(MPI_COMM_WORLD, &mpisize);

	double tab[10];
	if (mpirank == 1){
		int i;
		for (i=0;i<10;i++){
			tab[i] = (1./(double)(i+1.));
		}
		MPI_Send(tab, 10, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);	
		printf("Process 1 sent tab \n");
        }
	else if (mpirank == 0){
		MPI_Recv(tab, 10, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		int i;
		for(i=0;i<10;i++){	
			printf("Process 0 received tab %lf from process 0\n",tab[i]);
		}
	}
	
	MPI_Finalize();
	return 0;
}
