/*
 * retrieval.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: hczhu
 */


#include "retrieval.h"

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

