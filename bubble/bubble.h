
#ifndef _BUBBLE_FUNC_H_
#define _BUBBLE_FUNC_H_
//typedef ap_uint<12> data_in;
//typedef ap_uint<1> data_b;
//typedef int  data_in;
#define data_in int
#define data_b int
#define data_t int

#define K 400
void bubbleSort(data_t num[]);
void swap(data_t arr[], data_in i, data_in j);
#endif
