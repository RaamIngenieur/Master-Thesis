void SHDR2L13(unsigned int* r, __m128i  *left, __m128i  *right, int row, int column)
{
	unsigned int *hdis,*hdisl,*x,*w, y;
	int dmin=0, dmax=100;

	__m128i  *lp,*rp, z;
	unsigned long *sb;
	hdis = (unsigned int*)malloc(row*column*sizeof(unsigned int));
	x = (unsigned int*)malloc(row*column*sizeof(unsigned int));
	sb = (unsigned long*)&z;
	//unsigned long ms,ls;
	hdisl = hdis +6*(column + 1);

	for (int i = 6; i < row - 6; i++)
	{
		for (int j = 6; j < column - 6; j++)
		{
			*hdisl = 28561;
			hdisl++;
		}
		hdisl=hdisl+12;
	}

	for (int drange = dmax; drange >= dmin; drange--)
	{
		lp = left +drange;
		rp = right ;
		w=x;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column - drange; j++)
			{
				z = _mm_xor_si128 (*lp, *rp);
				*w= __builtin_popcountl(*sb);
				*w+= __builtin_popcountl(*(sb+1));
				lp++;
				rp++;
				w++;
			}
			lp= lp+ drange;
			rp= rp+ drange;
			w= w+ drange;
		}

		for (int i = 6; i < row - 6; i++)
		{
			for (int j = 6; j < column - drange - 6; j++)
			{
				y = 0;
				w = x + (i-6)*column + j-6;
				hdisl = hdis + i*column + j;
				for (int k = 12; k >= 0; k--)
				{
					for (int l = 12; l >= 0; l--)
					{
						y+= *w;
						if (y>*hdisl) break;
						w++;
					}
					if (y>*hdisl) break;
					w = w + (column - 13);
				}

				if (y<*hdisl)
				{
					*hdisl = y;
					*(r+i*column + j) = drange;
				}
			}
		}
	}
}