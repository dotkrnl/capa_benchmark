#ifndef _RETRIEVAL_H_
#define _RETRIEVAL_H_

#include <math.h>

const float eps = 0.0000000001;

float l2norm(float query[], float data[], int dim);

float l1norm(float query[], float data[], int dim);

float l0norm(float query[], float data[], int dim);

#endif
