#include <stdio.h>
#include <stdlib.h>
bool g_fallback = false;
typedef struct {
int info;}DATA;
typedef struct node {
DATA data;
struct node *next;}NODE;

void init(NODE **head)
{
   *head = 0L;
}

int *output_list(NODE *head,int *curr)
{
  NODE *temp;
  for (temp = head; temp; temp = temp -> next) {
     *(curr++) = temp -> data . info;
  }
  return curr;
}

NODE *add(NODE *node,DATA data)
{
  NODE *temp = (NODE *)(malloc(sizeof(NODE )));
  if (temp == 0L) {
    g_fallback = true;
    return 0L;
  }
  temp -> data = data;
  temp -> next = node;
  node = temp;
  return node;
}

void add_at(NODE *node,DATA data)
{
  NODE *temp = (NODE *)(malloc(sizeof(NODE )));
  if (temp == 0L) {
    g_fallback = true;
    return ;
  }
  temp -> data = data;
  temp -> next = node -> next;
  node -> next = temp;
}

void remove_node(NODE *head)
{
  NODE *temp = head -> next;
  head -> next = head -> next -> next;
  free(temp);
}

struct __rect_packed_type_L1213R__L1214R 
{
  NODE *local0;
  NODE *local1;
  NODE *local2;
  unsigned int _location;
  NODE *_return;
}
;

NODE *reverse_rec(NODE *ptr,NODE *previous)
{
  struct __rect_packed_type_L1213R__L1214R __rect_packed_var_L1213R__L1214R[1024U];
  unsigned int __rect_packed_top_L1213R__L1214R = 0U;
  __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _location = 1U;
  __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0 = ptr;
  __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local1 = previous;
  ++__rect_packed_top_L1213R__L1214R;
  __rect_func_L0_L1213R__L1214R:
  if (0U == __rect_packed_top_L1213R__L1214R) 
    return __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _return;
  --__rect_packed_top_L1213R__L1214R;
  if (1U == __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _location) 
    goto __rect_func_L1_L1213R__L1214R;
  if (2U == __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _location) 
    goto __rect_func_L2_L1213R__L1214R;
  __rect_func_L1_L1213R__L1214R:
  NODE *temp;
  if (__rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0 -> next == 0L) {
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0 -> next = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local1;
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _return = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0;
    goto __rect_func_L0_L1213R__L1214R;
  }
   else {
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _location = 2U;
    __rect_packed_var_L1213R__L1214R[1 + __rect_packed_top_L1213R__L1214R] . local1 = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0;
    __rect_packed_var_L1213R__L1214R[1 + __rect_packed_top_L1213R__L1214R] . local0 = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0 -> next;
    ++__rect_packed_top_L1213R__L1214R;
    if (__rect_packed_top_L1213R__L1214R == 1024U) 
g_fallback = true;
      0;
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _location = 1U;
    goto __rect_func_L1_L1213R__L1214R;
    __rect_func_L2_L1213R__L1214R:
    NODE *__rect_ret0_L1213R__L1214R = __rect_packed_var_L1213R__L1214R[1 + __rect_packed_top_L1213R__L1214R] . _return;
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local2 = __rect_ret0_L1213R__L1214R;
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0 -> next = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local1;
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _return = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local2;
    goto __rect_func_L0_L1213R__L1214R;
  }
  goto __rect_func_L0_L1213R__L1214R;
}

NODE *sort_list(NODE *head)
{
  NODE *tmpPtr = head;
  NODE *tmpNxt = head -> next;
  DATA tmp;
  while(tmpNxt != 0L){
    while(tmpNxt != tmpPtr){
      if (tmpNxt -> data . info < tmpPtr -> data . info) {
        tmp = tmpPtr -> data;
        tmpPtr -> data = tmpNxt -> data;
        tmpNxt -> data = tmp;
      }
      tmpPtr = tmpPtr -> next;
    }
    tmpPtr = head;
    tmpNxt = tmpNxt -> next;
  }
  return tmpPtr;
}
extern "C" {

void process_top(int n,int *input,int *output,bool *fallback)
{
  
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=fallback offset=slave bundle=gmem
  
#pragma HLS INTERFACE s_axilite port=n bundle=control
  
#pragma HLS INTERFACE s_axilite port=input bundle=control
  
#pragma HLS INTERFACE s_axilite port=output bundle=control
  
#pragma HLS INTERFACE s_axilite port=fallback bundle=control
  
#pragma HLS INTERFACE s_axilite port=return bundle=control
  int i;
  NODE *head;
  NODE *node;
  DATA element;
  init(&head);
  for (i = 0; i < n; i++) {
    element . info = input[i];
    head = add(head,element);
  }
  int *curr = output;
  curr = output_list(head,curr);
   *(curr++) = - 1;
  node = head -> next -> next -> next;
  element . info = 2000;
  add_at(node,element);
  curr = output_list(head,curr);
   *(curr++) = - 1;
  node = head -> next -> next;
  remove_node(node);
// Sort The List
  head = sort_list(head);
  curr = output_list(head,curr);
   *(curr++) = - 1;
// Revers The List
  head = reverse_rec(head,0L);
  curr = output_list(head,curr);
   *(curr++) = - 1;
   *fallback = g_fallback;
}
}
