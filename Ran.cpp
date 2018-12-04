#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
  int i,id,p;
  srand (time(NULL));

  double random_val;
  int seed;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&id);
  MPI_Comm_size(MPI_COMM_WORLD,&p);

  seed = rand() % 123456789;
  seed=seed+id;


  random_val = ((double)seed)/(double)RAND_MAX;
  printf("Del proceso numero %d el numero random es %f\n", id, random_val);



  MPI_Finalize();
  return 0;
}
