#include <stdio.h>
#include <stdlib.h>
#include "inputdata.h"
#include "rgb2yuv.h"
#include <time.h> 

int main()
{
	printf("Generating testing data!\n");
	srand(time(NULL));
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			for (int d = 0; d < depth; d++)
			{
				imagedata[h][w][d] = rand() % 256;
			}
		}
	}
	printf("Start conversion!\n");
	for (int h=0;h<height;h++)
	{
		for (int w=0;w<width;w++)
		{
			int r, g, b;
			float y, u, v;

			r = imagedata[h][w][0];
			g = imagedata[h][w][1];
			b = imagedata[h][w][2];
			
			rgb2yuv(r, g, b, y, u, v);

			outputdata[h][w][0] = y;
			outputdata[h][w][1] = u;
			outputdata[h][w][2] = v;
		}
	}
	printf("Done!\n");
	return 0;
}