#include "bubble.h"
#include <stdio.h>
#include "ap_int.h"
// Begin function swap returning void
void swap(ap_uint<8> arr[], ap_uint<10> i, ap_uint<10> j, ap_uint<1> sw) {
  ap_uint<8> temp;
  if (sw == 1) // ascending order simply changes to <
  // the 'if' part
  {
    temp = arr[j]; // swap elements
    arr[j] = arr[j + 1];
    arr[j + 1] = temp;
    // flag = 1;               // indicates that a swap occurred.
  }
}
// End function swap

// Begin function bubbleSort returning void
void bubbleSort(ap_uint<7> num[], ap_uint<8> numLength) {
ap_uint<10> i, j;

ap_uint<8> num_l[K];
for(int q =0;q< K;q++){
	num_l[q] =  num[q];
}

  for(i = 1; i <= K ; i++) {
    for(j = 1; j < K ; j++) {
    	printf("%d",num_l[j]);
    	printf("\n");
      ap_uint<1> sw = num_l[j] > num_l[j-1] ? 1 : 0;
      swap(num_l, i, j-1, sw);
    }
  }

for(int q =0;q< K;q++){
        num[q] =  num_l[q];
}
  return; //arrays are passed to functions by address; nothing is returned
}
// End function bubbleSort
