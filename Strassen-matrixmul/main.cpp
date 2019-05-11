#include "kernel.h"
#include <cstdio>

int main() 
{ 
	lld* matA = new lld[2 * 3]; 
	matA[0 * 3 + 0] = 1; 
	matA[0 * 3 + 1] = 2; 
	matA[0 * 3 + 2] = 3; 
	matA[1 * 3 + 0] = 4; 
	matA[1 * 3 + 1] = 5; 
	matA[1 * 3 + 2] = 6; 

	lld* matB = new lld[3 * 2];
	matB[0 * 2 + 0] = 7; 
	matB[0 * 2 + 1] = 8; 
	matB[1 * 2 + 0] = 9; 
	matB[1 * 2 + 1] = 10; 
	matB[2 * 2 + 0] = 11; 
	matB[2 * 2 + 1] = 12; 

	lld* matC = new lld[2 * 2]; 

	bool fallback;
	process_top(2, 3, 2, matA, matB, matC, &fallback);
	if (fallback) {
		printf("fallback to host!\n");
		return 1;
	}

	for (int i = 0; i < 2; i++) { 
		for (int j = 0; j < 2; j++) { 
			printf("%lld ", matC[i * 2 + j]); 
		} 
		printf("\n"); 
	} 

	return 0; 
}
