#include "bubble.h"
#include <stdio.h>

void swap(data_t arr[], data_in i, data_in j, data_b sw) {
  data_t temp;
  if (sw == 1) // ascending order simply changes to <
  {
    temp = arr[j]; // swap elements
    arr[j] = arr[j + 1];
    arr[j + 1] = temp;
    // flag = 1;               // indicates that a swap occurred.
  }
}

void bubbleSort(data_t num[], data_in numLength) {
data_in i, j;

data_t num_l[K];
for(int q =0;q< K;q++){
	num_l[q] =  num[q];
}

  for(i = 1; i <= K ; i++) {
    for(j = 1; j < K ; j++) {
    	printf("%d",num_l[j]);
    	printf("\n");
      data_b sw = num_l[j] > num_l[j-1] ? 1 : 0;
      swap(num_l, i, j-1, sw);
    }
  }

for(int q =0;q< K;q++){
        num[q] =  num_l[q];
}
  return; //arrays are passed to functions by address; nothing is returned
}
