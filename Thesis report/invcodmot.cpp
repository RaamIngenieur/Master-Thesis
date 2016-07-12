...
	for (int i = 1; i <= row - 2; i++)
	{
		for (int j = 1; j <= column - 2; j++)
		{
			min = *(Pix+i*column+j);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (*(Pix+(i + k)*column+j + l) < min)
					{
						min = *(Pix + (i + k)*column + j + l);
					}
				}
			}
			*(b.Pix+i*column+j) = min;
		}
	}
...


...
	for (int i = 1; i <= row - 2; i++)
	{
		for (int j = 1; j <= column - 2; j++)
		{
			Pix1 = Pix+(i-1)*column+j-1;
			min = *Pix1;
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (*Pix1 < min)
					{
						min = *Pix1;
					}
					Pix1++
				}
				Pix1=Pix1+column-3;
			}
			*(b.Pix+i*column+j) = min;
		}
	}
...
