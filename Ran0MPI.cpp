#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

using namespace std;

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876


float ran0(long *idum)
{
  long k;
  float ans;

  *idum ^= MASK;
  k=(*idum)/IQ;
  *idum=IA*(*idum-k*IQ)-IR*k;

  if (*idum < 0) *idum += IM;
  ans=AM*(*idum);
  *idum ^= MASK;

  return ans;
}


int main(int argc, char *argv[])
{int i,id,p;

  double random_val;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&id);
  MPI_Comm_size(MPI_COMM_WORLD,&p);

  long seed= 123456789 + id;
  long *idum=&seed;

random_val=ran0(idum);

  //random_val = (double)ran0(idum)/(double)RAND_MAX;
  printf("Del proceso numero %d el numero random es %f\n", id, random_val);



MPI_Finalize();
return 0;
}
