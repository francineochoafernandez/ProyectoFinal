#include <iostream>
#include <mpi.h>
using namespace std;

int main (int argc, char *argv[])
{

  int ierr= MPI_Init(&argc, &argv);
  int procid, numprocs;
  ierr= MPI_Comm_rank(MPI_COMM_WORLD, &procid);
  ierr= MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  printf("Hola, se esta en el proceso %i de %i procesos.\n",procid,numprocs);
  ierr=MPI_Finalize();
  return 0;
}
