#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>


void fill_tabs(float *tab_loc, float *tab_res, float *tab_calc, int nloc, int ncalc)  
{
    int i;
    for( i = 0 ; i < nloc ; i++ )
    {
         tab_loc[i] = 1.0f;
         tab_res[i] = 0.0f;
    }
}

void reduce_nocomm(int Nloc, int Ncalc, float *tab_loc, float *tab_res, float *tab_calc) 
{
    int i;
    for( i = 0 ; i < Nloc ; i++ )
    {    
	    tab_res[i] = 0.0f;
    }
}

void allreduce_blocking(int Nloc, int Ncalc, float *tab_loc, float *tab_res, float *tab_calc) 
{
    int i;
    for( i = 0 ; i < Nloc ; i++ )
    {    
	    tab_res[i] = 0.0f;
    }
}


void allreduce_nonblocking(int Nloc, int Ncalc, float *tab_loc, float *tab_res, float *tab_calc) 
{
    int i;
    for( i = 0 ; i < Nloc ; i++ )
    {    
	    tab_res[i] = 0.0f;
    }
}


void allreduce_nonblocking_pipelined2(int Nloc, int Ncalc, float *tab_loc, float *tab_res, float *tab_calc) 
{
    int i;
    for( i = 0 ; i < Nloc ; i++ )
    {    
	    tab_res[i] = 0.0f;
    }

    MPI_Waitall(2,req,test);
}


void allreduce_nonblocking_pipelined4(int Nloc, int Ncalc, float *tab_loc, float *tab_res, float *tab_calc) 
{
    int i;
    for( i = 0 ; i < Nloc ; i++ )
    {    
	    tab_res[i] = 0.0f;
    }
}


int main(int argc, char **argv) 
{
    // DEBUT DE LA PHASE PARALLELE
    MPI_Init(&argc, &argv);
    
    int Nglob, Nloc, Ncalc;
    float *tab_loc, *tab_res;
    float *tab_calc = NULL;
    float err;

    // RECUPERATION DU RANG
    int rang;
    MPI_Comm_rank(MPI_COMM_WORLD, &(rang));

    // RECUPERATION DU NOMBRE DE PROCESSUS MPI
    int nproc;
    MPI_Comm_size(MPI_COMM_WORLD, &(nproc));

    Nloc = atoi(argv[1]);;
    int compute_factor = atoi(argv[2]);;
    Nglob = nproc * Nloc;
    Ncalc = compute_factor * Nloc;

    tab_loc  = (float*)malloc(Nloc*sizeof(float));
    tab_res  = (float*)malloc(Nloc*sizeof(float));

    fill_tabs(tab_loc, tab_res, tab_calc, Nloc, Ncalc);

    int i=0;
    int itermax=10;

    double t01=0.;
    double t02=0.;
    double time0=0.;
    for (i=0; i<itermax;i++)
    {
        t01 = MPI_Wtime();
        reduce_nocomm(Nloc, Ncalc, tab_loc, tab_res, tab_calc);
        t02 = MPI_Wtime();
        time0 += (t02 - t01);
    }

    double t11=0.;
    double t12=0.;
    double time1=0.;
    for (i=0; i<itermax;i++)
    {
        t11 = MPI_Wtime();
        allreduce_blocking(Nloc, Ncalc, tab_loc, tab_res, tab_calc);
        t12 = MPI_Wtime();
        time1 += (t12 - t11);
    }

    double t21=0.;
    double t22=0.;
    double time2=0.;
    for (i=0; i<itermax;i++)
    {
        t21 = MPI_Wtime();
        allreduce_nonblocking(Nloc, Ncalc, tab_loc, tab_res, tab_calc);
        t22 = MPI_Wtime();
        time2 += (t22 - t21);
    }

    double t31=0.;
    double t32=0.;
    double time3=0.;
    for (i=0; i<itermax;i++)
    {
        t31 = MPI_Wtime();
        allreduce_nonblocking_pipelined2(Nloc, Ncalc, tab_loc, tab_res, tab_calc);
        t32 = MPI_Wtime();
        time3 += (t32 - t31);
    }

    double t41=0.;
    double t42=0.;
    double time4=0.;
    for (i=0; i<itermax;i++)
    {
        t41 = MPI_Wtime();
        allreduce_nonblocking_pipelined4(Nloc, Ncalc, tab_loc, tab_res, tab_calc);
        t42 = MPI_Wtime();
        time4 += (t42 - t41);
    }

    if (rang == 0)
    {
        printf("compute duration    %.12e \n", time0);
        printf("reduction1 duration %.12e \n", time1);
        printf("reduction2 duration %.12e \n", time2);
        printf("reduction3 duration %.12e \n", time3);
        printf("reduction4 duration %.12e \n", time4);
        fflush(stdout);
    }

    free(tab_loc);
    free(tab_res);

    MPI_Finalize();

    return 0;
}

