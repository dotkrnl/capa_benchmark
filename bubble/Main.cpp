#include "bubble.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[]) {
  int n, c, d, swap ,retval=0;
//  std::fstream file;
//  file.open("random.text");
//  int number;
//  while (file >> number) {
//    numbers.push_back(number);
//    file.get();
//  }
//  file.close();

// FILE* f = fopen("random.text", "r");
//
    int numbers[K]; // assuming there are only 5 numbers in the file
//int i=0;
//    while( fscanf(f, "%d,", &n) > 0 ) // parse %d followed by ','
//    {
//        numbers[i] = n;
//        		i++;
//    }
//
//    fclose(f);
  srand(time(NULL));
  printf("here in genration");
 for(c = 0 ; c <K ; ++c){

	 numbers[c] = (rand() % (800 + 1 - 0));
 }

 // n = numbers.size();
  n = K;
  data_t array[n];
  for (c = 0; c < n; c++) {
    array[c] = numbers[c];
  }

/*  for (c = 0; c < n; c++)
    printf("Array: %d \n", array[c]);
   printf("Enter number of elements\n");
   scanf("%d", &n);

   printf("Enter %d integers\n", n);

   for (c = 0; c < n; c++)
     scanf("%d", &array[c]);
*/
   data_in  dnum = (unsigned int) n;
  bubbleSort(array, dnum);
  for (c = 1; c < n; c++){
    if(array[c-1] < array[c]){
        retval = 1;
    }
// 	printf("Array: %f \n", array[c]);
  }
  if(retval == 0){
  printf("Results are good \n");
  } else {
  printf("Mismatch: retval=%d \n", retval);
  }
  return retval;

}
