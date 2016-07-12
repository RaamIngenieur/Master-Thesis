
#include <iostream>
#include <png++/png.hpp>
#include <stdlib.h>
#include <thread>
#include <fstream>
#include "immintrin.h"
using namespace std;


class ucarray
{
public:
	unsigned char *P;
	ucarray(int r, int c);
	~ucarray();
	void imagetoarray(png::image<png::gray_pixel>* input);
	void operator=(const ucarray& other);
	void arraytoimage(png::image<png::gray_pixel>* output);
	void arrayerode(ucarray &b);
	void arraydilate(ucarray &b);
private:
	int row, column;

};


ucarray::ucarray(int r, int c)
{
	row = r;
	column = c;
	P = (unsigned char*)malloc(row * column * sizeof(unsigned char));
	if (P == NULL)
	{
		fprintf(stderr, "out of memory\n");
	}

}

ucarray::~ucarray()
{
	std::cout << "UCarray freed";
	free(P);
}

void ucarray::imagetoarray(png::image<png::gray_pixel>* input)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			*(P + i*column +j) = (*input)[i][j];
		}
	}
}

void ucarray::arraytoimage(png::image<png::gray_pixel>* output)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			(*output)[i][j] = *(P + i*column +j);
		}
	}
}

void ucarray:: operator =(const ucarray&  other)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			*(P+i*column+j) = *(other.P+i*column+j);
		}
	}
}

void ucarray::arrayerode(ucarray &b)
{
	unsigned char min;
	for (int i = 1; i <= row - 2; i++)
	{
		for (int j = 1; j <= column - 2; j++)
		{
			min = *(P+i*column+j);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (*(P+(i + k)*column+j + l) < min)
					{
						min = *(P + (i + k)*column + j + l);
					}
				}
			}
			*(b.P+i*column+j) = min;
		}
	}
}

void ucarray::arraydilate(ucarray &b)
{
	unsigned char max;
	for (int i = 1; i <= row - 2; i++)
	{
		for (int j = 1; j <= column - 2; j++)
		{
			max = *(P + i*column + j);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (*(P + (i + k)*column + j + l) > max)
					{
						max = *(P + (i + k)*column + j + l);
					}
				}
			}
			*(b.P + i*column + j) = max;
		}
	}
}

void initializeuiarray(unsigned int * P, int r, int c)
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				*(P+i*c*6+j*6+k) = 0;
			}

		}
	}
}

void census13(unsigned int * P, ucarray &b, int r, int c)
{
	int x;
	unsigned int * Q;

	for (int i = 6; i <= r - 7; i++)
	{
		for (int j = 6; j <= c - 7; j++)
		{
			x = 0;
			Q = P+i*c*6+j*6;

			for (int k = -6; k <= 6; k++)
			{
				for (int l = -6; l <= 6; l++)
				{
					if (~(k == 0 && l == 0))
					{
						*Q = *Q << 1;

						if (*(b.P +(i + k)*c+j + l) < *(b.P+i*c+j))
						{
							*Q = *Q + 1;
						}
						x++;
						if (x%32==0)
						Q = Q + 1;

					}
				}
			}

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

void SHDR2L13(float* r, unsigned int  *left, unsigned int  *right, int row, int column)
{
	unsigned int x, hdis = 28561, dmin = 0, dmax = 100, dif1, dif2, dif3;
	float num, den, pos;
	int y;
	unsigned int  *lp,*rp;

	for (int i = 0; i < row - 12; i++)
	{
		for (int j = 0; j < column - 12; j++)
		{
			for (unsigned int drange = dmin; drange <= dmax; drange++)
			{
				if ((unsigned int)j + 12 + drange < (unsigned int) column)
				{
					y = 0;
					lp = left + (i*column + j + drange) * 6;
					rp = right + (i*column + j) * 6;
					for (int k = 12; k >= 0; k--)
					{
						for (int l = 12; l >= 0; l--)
						{
							for (int m = 5; m >= 0; m--)
							{
								x = *lp^*rp;
								y = y + __builtin_popcount(x);
								//y = y + _mm_countbits_32 (x);
								lp = lp + 1;
								rp = rp + 1;
							}
						}
						lp = lp + (column - 13) * 6;
						rp = rp + (column - 13) * 6;
					}

					if (y<hdis)
					{
						hdis = y;
						pos = drange;
					}


					if (drange == dmin)
					{
						dif1 = y;
						dif2 = 28561;
						dif3 = 28561;
						hdis = y;
					}
					else
					{
						dif3 = dif2;
						dif2 = dif1;
						dif1 = y;
					}
					if ((dif2 <= hdis) && (dif2 <= dif3) && (dif2 <= dif1))
					{
						num = ((float)(dif3 - dif1)) / 2;
						den = (float)(dif3 + dif1 - 2 * dif2);
						hdis = dif2;

						if (num == 0)
						{
							pos = (float)drange - 1;
						}
						else if (den == 0)
						{
							pos = (float)drange + (float)sgn(num) - 1;
						}
						else if (den/sgn(den) >= num/sgn(num))
						{
							pos = (float)drange + ((float)(sgn(num)*sgn(den)))*num / den - 1;
						}
						else
						{
							pos = (float)drange + (float)sgn(num)*sgn(den) - 1;
						}
					}
				}
			}
			*(r+(i+6)*column+j+6) = pos;
			hdis = 28561;
		}
	}
}

void average(float* r, int row, int column)
{
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < column - 1; j++)
		{
			*(r + i*column + j) = (*(r + (i - 1)*column + j - 1) + *(r + (i - 1)*column + j) + *(r + (i - 1)*column + j + 1) + *(r + i*column + j - 1) + *(r + i*column + j)) / 5;
		}
	}
}

void preprocessimage(png::image<png::gray_pixel>* imageS, ucarray &S, ucarray &SO, unsigned int * SC, int r, int c)
{
	S.imagetoarray(imageS);
	std::cout<<(unsigned int)*(S.P);
	S.arrayerode(SO);
	S = SO;
	S.arraydilate(SO);
	//SO.arraytoimage(imageS);
	//imageS->write("output.png");
	initializeuiarray(SC, r, c);
    census13(SC,SO,r,c);
}

int main()
{

	png::image< png::gray_pixel > imageL("frame_1_left.png");
	png::image< png::gray_pixel > imageR("frame_1_right.png");

	int row = imageL.get_height(), column = imageL.get_width();

	ucarray L(row, column), LO(row, column), R(row, column), RO(row, column);
	unsigned int * LC, *RC;

	LC = (unsigned int*)malloc(row * column* 6* sizeof(unsigned int ));
	RC = (unsigned int*)malloc(row * column*6*sizeof(unsigned int));
	if (LC == NULL||RC == NULL)
	{
		fprintf(stderr, "out of memory\n");
	}

	float* O;

	O = (float*)malloc(row * column * sizeof(float));
	if (O == NULL)
	{
		fprintf(stderr, "out of memory\n");
	}



	preprocessimage(&imageL, L, LO, LC, row,column);
	preprocessimage(&imageR, R, RO, RC, row, column);

	initializefarray(O,row,column);

	//SHDR2L13(O,LC,RC,row,column);
	//average (O,row,column);



	std::thread a(SHDR2L13, O, LC, RC, row / 4 + 6, column);
	std::thread b(SHDR2L13, O + (row / 4 - 6)*column, LC + (row / 4 - 6)*column*6, RC + (row / 4 - 6)*column*6, row / 4 + 12, column);
	std::thread c(SHDR2L13, O + (row / 2 - 6)*column, LC + (row / 2 - 6)*column * 6, RC + (row / 2 - 6)*column * 6, row / 4 + 12, column);
	std::thread d(SHDR2L13, O + (3 * row / 4 - 6)*column, LC + (3 * row / 4 - 6)*column * 6, RC + (3 * row / 4 - 6)*column * 6, row / 4 + 6, column);

	a.join();
	std::thread e(average, O, row / 4 + 6, column);
	b.join();
	std::thread f(average, O + (row / 4 - 6)*column, row / 4 + 12, column);
	c.join();
	std::thread g(average, O + (row / 2 - 6)*column, row / 4 + 12, column);
	d.join();
	std::thread h(average, O + (3 * row / 4 - 6)*column, row / 4 + 6, column);

	e.join();
	f.join();
	g.join();
	h.join();


	arrayftoimage(&imageL,O,row,column);

	imageL.write("output.png");

}

