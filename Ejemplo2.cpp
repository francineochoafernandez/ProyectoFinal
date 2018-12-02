#include <iostream>
#include <mpi.h>
using namespace std;

int main (int argc, char *argv[])
{

  int ierr= MPI_Init(&argc, &argv);
  int procid, numprocs;
  ierr= MPI_Comm_rank(MPI_COMM_WORLD, &procid);
  ierr= MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  if(numprocs!=2)
  {
    printf("\nERROR!: el número de procesos no es 2.\n");
    return MPI_Abort(MPI_COMM_WORLD,1);
  }
  if(procid==0)
  {
    //procid 0 enviara el numero 3.14 a procid 1
    double pi=3.14159265358979;
    MPI_Send(&pi,1,MPI_DOUBLE,1,0,MPI_COMM_WORLD);
    printf("\nProcid %d envio el valor %lf a procid 1.\n",procid,pi);
  }
  else
  {
    //procid 1 espera a recibir un double de procid 0
    double value;
    MPI_Status status;
    ierr=MPI_Recv(&value,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&status);
    if(ierr==MPI_SUCCESS)
      printf("\nProcid %d recibió el valor %lf.\n",procid,value );
    else
      printf("\nProcid %d no recibió exitósamente un valor.\n",procid );

  }

  ierr=MPI_Finalize();
  return 0;
}
