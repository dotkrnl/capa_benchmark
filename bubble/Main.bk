#include "bubble.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[]) 
{
	int n, c, d, swap, retval=0;

	FILE* f = fopen(argv[1], "r");

    	int numbers[K]; // assuming there are only 5 numbers in the file
    	int i=0;
    	while( fscanf(f, "%d\n", &n) > 0 && i<K ) // parse %d followed by ','
    	{
        	numbers[i] = n;
//		printf("%d, %d\n",i, numbers[i]);
        	i++;
    	}

    	fclose(f);

	data_t array[K];
	for (c = 0; c < K; c++) 
	{
		array[c] = numbers[c];
	}
	printf("Begin sort\n!");
        bubbleSort(array);

        return retval;

}

