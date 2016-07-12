
#include <stdlib.h>
#include <iostream>
#include <png++/png.hpp>
#include <thread>
#include <fstream>
#include "nema.h"
#include <sys/time.h>


using namespace std;


void imagetoucarray(png::image<png::gray_pixel>* image,unsigned char * array,int row,int column)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      *(array + i*column +j) = (*image)[i][j];
    }
  }
}

void initialize2duiarray(unsigned int * array, int row, int column,unsigned int val)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      *(array+i*column+j) = val;
    }
  }
}

void initializefarray(float* P, int r, int c)
{
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
    {
      *(P+i*c+j) = 0;
    }
  }
}

void arrayftoimage(png::image<png::gray_pixel>* input, float* P, int row, int column)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      (*input)[i][j] = (unsigned char)(*(P+i*column+j));
    }
  }
}

unsigned int bitCount(unsigned int c)
{
  c = c - ((c >> 1) & 0x55555555);
  c = (c & 0x33333333) + ((c >> 2) & 0x33333333);
  return (((c + (c >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

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

void uiarraytoimage(png::image<png::gray_pixel>* image, unsigned int *array,int row, int column)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
       (*image)[i][j]=*(array + i*column +j);
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
  png::image< png::gray_pixel > imageR("frame_1_right.png");
  unsigned char *lchar,*lchar1,*rchar,*rchar1;
  int row, column, dmin, dmax;
  unsigned int *lct, *rct, *hdis, *exoradd, *result, *HammDistY;

  row = imageL.get_height();
  column = imageL.get_width();

  Nema nema;

  nema.init(row,column);

  lchar = (unsigned char*)nema.nema_malloc(row * column * sizeof(unsigned char));
  lchar1 = (unsigned char*)nema.nema_malloc(row * column * sizeof(unsigned char));
  rchar = (unsigned char*)nema.nema_malloc(row * column * sizeof(unsigned char));
  rchar1 = (unsigned char*)nema.nema_malloc(row * column * sizeof(unsigned char));

  imagetoucarray(&imageL,lchar,row,column);
  imagetoucarray(&imageR,rchar,row,column);

  gettimeofday(&tim, NULL);
  t3 = tim.tv_sec + (tim.tv_usec / 1000000.0);

  nema.erode(lchar,lchar1,row,column);
  //nema.wait_for_interrupt();
  nema.erode(rchar,rchar1,row,column);
  //nema.wait_for_interrupt();


  nema.dilate(lchar1,lchar,row,column);
 // nema.wait_for_interrupt();
  nema.dilate(rchar1,rchar,row,column);
 // nema.wait_for_interrupt();

  nema.nema_free((void*)lchar1);
  nema.nema_free((void*)rchar1);

  gettimeofday(&tim, NULL);
  t4 = tim.tv_sec + (tim.tv_usec / 1000000.0) - t3;

  lct = (unsigned int*)nema.nema_malloc(row * column * 4 * sizeof(unsigned int ));
  rct = (unsigned int*)nema.nema_malloc(row * column * 4 * sizeof(unsigned int));
  if (lct == NULL||rct == NULL)
  {
    fprintf(stderr, "out of memory\n");
  }

  gettimeofday(&tim, NULL);
  t3 = tim.tv_sec + (tim.tv_usec / 1000000.0);

  nema.c11(lchar,lct,row,column);
  //nema.wait_for_interrupt();
  nema.c11(rchar,rct,row,column);
  //nema.wait_for_interrupt();

  gettimeofday(&tim, NULL);
  t4 += tim.tv_sec + (tim.tv_usec / 1000000.0) - t3;


  nema.nema_free((void*)lchar);
  nema.nema_free((void*)rchar);

  hdis = (unsigned int*)nema.nema_malloc(row * column * sizeof(unsigned int ));
  exoradd = (unsigned int*)nema.nema_malloc(row * column * sizeof(unsigned int ));
  HammDistY = (unsigned int*)nema.nema_malloc(row * column * sizeof(unsigned int ));
  result = (unsigned int*)nema.nema_malloc(row * column * sizeof(unsigned int));
  if (hdis == NULL||result == NULL)
  {
    fprintf(stderr, "out of memory\n");
  }

  initialize2duiarray(hdis,row,column,20449);

  dmin=0;
  dmax=100;

  gettimeofday(&tim, NULL);
  t3 = tim.tv_sec + (tim.tv_usec / 1000000.0);
  for (int drange = dmax; drange >= dmin; drange--)
  {
    nema.exoradd(exoradd, lct, rct, row, column, drange);
    //  nema.wait_for_interrupt();

    nema.shdy(exoradd,HammDistY,row,column,drange);
    //  nema.wait_for_interrupt();

    nema.shd(HammDistY,hdis,result,row,column,drange);
    //  nema.wait_for_interrupt();
  }

  nema.wait_for_interrupt();

  gettimeofday(&tim, NULL);
  t4 += tim.tv_sec + (tim.tv_usec / 1000000.0) - t3;


  //imagetouiarray(&imageL,result,row,column);

  uiarraytoimage(&imageL,result,row,column);


  imageL.write("output.png");

  nema.nema_free((void*) lct);
  nema.nema_free((void*) rct);
  nema.nema_free((void*) result);

  nema.shutDown();

  gettimeofday(&tim, NULL);
  t2 = tim.tv_sec + (tim.tv_usec / 1000000.0) - t1;

  cout<<endl<<"Total nema run time : "<<t4<<endl;
    cout<<endl<<"Total program run time : "<<t2<<endl;
//  cout<<endl<<"Total preprocessing run time : "<<t4<<endl;

}
