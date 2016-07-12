
#include <iostream>
#include <png++/png.hpp>
#include <stdlib.h>
#include <thread>
#include <fstream>
#include "nema.h"
#include <sys/time.h>


using namespace std;


void imagetouiarray(png::image<png::gray_pixel>* input, unsigned int *P,int row, int column)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      *(P + i*column +j) = (*input)[i][j];
    }
  }
}

void uiarraytoimage(png::image<png::gray_pixel>* input, unsigned int *P,int row, int column)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
       (*input)[i][j]=*(P + i*column +j);
    }
  }
}

int main()
{
  struct timeval tim;
  double t1, t2, t3, t4;
  gettimeofday(&tim, NULL);
  t1 = tim.tv_sec + (tim.tv_usec / 1000000.0);

  png::image< png::gray_pixel > imageL("frame_1_left.png");

  Nema nema;

  int row = imageL.get_height(), column = imageL.get_width();

  nema.init(1,64);

  unsigned int *result;


  result = (unsigned int*)nema.nema_malloc(row * column * sizeof(unsigned int));
  if (result == NULL)
  {
    fprintf(stderr, "out of memory\n");
  }


  imagetouiarray(&imageL,result,row,column);


  gettimeofday(&tim, NULL);
  t3 = tim.tv_sec + (tim.tv_usec / 1000000.0);

  for (int i=4799;i>=0;i--)
  {
    nema.negate(result+64*i,1,64,i==4799);
  }

  nema.wait_for_interrupt();

  gettimeofday(&tim, NULL);
  t4 = tim.tv_sec + (tim.tv_usec / 1000000.0);

  t4 = t4 - t3;

  uiarraytoimage(&imageL,result,row,column);


  imageL.write("output.png");

  nema.nema_free((void*) result);

  nema.shutDown();

  gettimeofday(&tim, NULL);
  t2 = tim.tv_sec + (tim.tv_usec / 1000000.0);

  t2= t2 - t1;

  cout<<endl<<"Total program run time : "<<t2<<endl;
  cout<<endl<<"Nema run time : "<<t4<<endl;

}
