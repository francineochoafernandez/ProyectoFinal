#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

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
{
  int i,id,p;

  float X[1000000];
  float Y[1000000];
  int N;
  float r,h,s;
  float f,fsum,a,prom,riemann, area, volumen;
  int puntosdentro;

  double random_val;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&id);
  MPI_Comm_size(MPI_COMM_WORLD,&p);

  long seed= 123456789 + id;
  long *idum=&seed;

  r=1;
  h=1;
  s= sqrt(2);
  area=0;
  volumen=0;
  printf("\n  Ingresa el numero de puntos que vas a calcular: \n");
  scanf("%i",&N);


   random_val=ran0(idum);

  for (int i=0; i<N; i++)
  {
    X[i]= 2*random_val - 1;
  }

  for (int i=0; i<N; i++)
  {
    Y[i]= 2*random_val - 1;
  }

// x^2 + y^2 = (z)^2(R)^2
//z=sqrt(x^2+y^2)/R^2
//A=πr(r+ sqrt(h^2+r^2))

  fsum=0;
  for (int i=0; i<N; i++)
  {
     a=(P_PID*X[i]*X[i]*Y[i])/3;
     //a= sqrt(X[i]*X[i] + Y[i]*Y[i]);

    if (r*r > a)
    {
    f=sqrt(r*r - a);
    //f=r*(1-a/h);
    fsum += f;
    puntosdentro++;
    }
  }

  prom= fsum/puntosdentro;
  riemann= P_PID * r * s + P_PID * r * prom;

  area= P_PID * r * s + P_PID * r * r;
  volumen= (P_PID * r * r * h)/3;

  printf("\n  El area de superficie real del cono es:\n");
  printf("%f\n",area );

  printf("\n  El volumen real del cono es:\n");
  printf("%f\n",volumen );

  printf("\n  El area  del cono es:\n");
  printf("%f\n",riemann );

  printf("\n  El volumen  del cono es:\n");
  printf("%f\n",prom );

  printf("\n Numero de puntos:\n");
  printf("%i \n",puntosdentro );


  MPI_Finalize();
 return 0;
}
