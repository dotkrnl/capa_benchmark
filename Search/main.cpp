#include <stdio.h>
#include <stdlib.h>
#include "inputdata.h"
#include "retrieval.h"
#include <time.h> 

int main()
{
	// Generate data;
	srand(time(NULL));
	for (int i = 0; i<number; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			database[i][j] = (float)rand() / (float)RAND_MAX - 0.5;
		}
	}

	float query[dim];
	for (int j = 0; j < dim; j++)
	{
		query[j] = (float)rand() / (float)RAND_MAX - 0.5;
	}

	// Calculate distance
	
	for (int i = 0; i < number; i++)
	{
		distance[i] = l2norm(query, database[i], dim);
	}

	// Top 1 neareast neighbor
	int index = 0;
	float minDist = distance[0];
	for (int i = 0; i < number; i++)
	{
		if (distance[i] > minDist)
		{
			minDist = distance[i];
			index = i;
		}
	}

	// Find the top 1
	printf("Find the top 1, index %d, distance %f", index, minDist);
	return 0;
}