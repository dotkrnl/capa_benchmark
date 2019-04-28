// C program for generating a 
// random number in a given range. 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

// Generates and prints 'count' random 
// numbers in range [lower, upper]. 
void printRandoms(int lower, int upper, int count) 
{ 
	FILE *fp;
	fp = fopen("input_0_180.txt", "w");	
	int i, num; 
	for (i = 0; i < 100; i++) 
	{
		fprintf(fp, "{");
		int j = 0;
		for (j=0; j<8; j++)
		{
			num = (rand() % (upper - lower + 1)) + lower; 
			fprintf(fp, "%d, ", num); 	
		}
		num = (rand() % (upper - lower + 1)) + lower;
		fprintf(fp, "%d}\n", num);
	} 
	fclose(fp);
} 

// Driver code 
int main() 
{ 
	int lower = 0, upper = 180, count = 900; 

	// Use current time as 
	// seed for random generator 
	srand(time(0)); 

	printRandoms(lower, upper, count); 

	return 0; 
} 

