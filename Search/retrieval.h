#ifndef _RETRIEVAL_H_
#define _RETRIEVAL_H_

#include <math.h>

const float eps = 0.0000000001;

float l2norm(float query[], float data[], int dim)
{
	float dist = 0.0;
	for (int j = 0; j < dim; j++)
	{
		dist += ((query[j] - data[j])*(query[j] - data[j]));
	}
	dist = sqrt(dist);
	return dist;
}

float l1norm(float query[], float data[], int dim)
{
	float dist = 0.0;
	for (int j = 0; j < dim; j++)
	{
		dist += fabs(query[j] - data[j]);
	}
	return dist;
}

float l0norm(float query[], float data[], int dim)
{
	float dist = 0.0;
	for (int j = 0; j < dim; j++)
	{
		if (fabs(query[j] - data[j]) < eps)
		{
			dist += 1;
		}
	}
	return dist;
}

#endif
