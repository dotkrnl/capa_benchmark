
struct __dst_alloc_list_base_t 
{
  unsigned int prev;
  unsigned int next;
}
;
// type __didxL105R was ::NODE*
typedef unsigned int __didxL105R;
#include <stdio.h>
#include <stdlib.h>
bool g_fallback = false;
typedef struct {
int info;}DATA;
typedef struct node {
DATA data;
__didxL105R next;}NODE;

struct __dst_alloc_list__dmemL105R 
{
  struct __dst_alloc_list_base_t _link;
  NODE _data;
}
;
struct __dst_alloc_list__dmemL105R __dmemL105R[1 << ARRAY_LOG];
unsigned int __dst_alloc_malloc__dmemL105R(unsigned int );
void __dst_alloc_free__dmemL105R(unsigned int );
# 1 "<stdin>"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "<stdin>"
# 54 "<stdin>"
typedef unsigned int __dst_alloc_size_t;
typedef unsigned char __dst_alloc_bucket_size_t;
# 73 "<stdin>"
unsigned char __dst_alloc_node_split__dmemL105R[(1 << (ARRAY_LOG - 1)) / 8];
static unsigned char __dst_alloc_test_parent_split__dmemL105R(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    return (__dst_alloc_node_split__dmemL105R[index / 8] >> (index % 8)) & 1;
}
static void __dst_alloc_flip_parent_split__dmemL105R(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemL105R[index / 8] ^= 1 << (index % 8);
}
static void __dst_alloc_clr_parent_split__dmemL105R(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemL105R[index / 8] &= ~(1 << (index % 8));
}
struct __dst_alloc_list_base_t __dst_alloc_buckets__dmemL105R[ARRAY_LOG] = {{1, 1}};
static __dst_alloc_bucket_size_t __dst_alloc_bucket_for_request__dmemL105R(
        __dst_alloc_size_t request) {
    __dst_alloc_bucket_size_t bucket = ARRAY_LOG - 1;
    __dst_alloc_size_t size = 2;
    while (size < request) {
        size <<= 1;
        bucket -= 1;
    }
    return bucket;
}
static void __dst_alloc_list_push__dmemL105R(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dst_alloc_buckets__dmemL105R[bucket].prev;
    __dmemL105R[entry]._link.prev = prev;
    __dmemL105R[entry]._link.next = 0;
    if (prev == 0) __dst_alloc_buckets__dmemL105R[bucket].next = entry;
    else __dmemL105R[prev]._link.next = entry;
    __dst_alloc_buckets__dmemL105R[bucket].prev = entry;
}
static void __dst_alloc_list_remove__dmemL105R(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dmemL105R[entry]._link.prev;
    __dst_alloc_size_t next = __dmemL105R[entry]._link.next;
    if (prev == 0) __dst_alloc_buckets__dmemL105R[bucket].next = next;
    else __dmemL105R[prev]._link.next = next;
    if (next == 0) __dst_alloc_buckets__dmemL105R[bucket].prev = prev;
    else __dmemL105R[next]._link.prev = prev;
}
static __dst_alloc_size_t __dst_alloc_list_pop__dmemL105R(
        __dst_alloc_bucket_size_t bucket) {
    __dst_alloc_size_t back = __dst_alloc_buckets__dmemL105R[bucket].prev;
    if (back == 0) return 0;
    __dst_alloc_list_remove__dmemL105R(bucket, back);
    return back;
}
static __dst_alloc_size_t __dst_alloc_index_for_node__dmemL105R(
        __dst_alloc_size_t bucket_index,
        __dst_alloc_bucket_size_t bucket) {
    return 1 + ((bucket_index - (1 << bucket) + 1) << (ARRAY_LOG - bucket));
}
static __dst_alloc_size_t __dst_alloc_node_for_index__dmemL105R(
        __dst_alloc_size_t global_index,
        __dst_alloc_bucket_size_t bucket) {
    return ((global_index - 1) >> (ARRAY_LOG - bucket)) + (1 << bucket) - 1;
}
void __dst_alloc_init__dmemL105R() {
    for (int i = 0; i < ARRAY_LOG; i++) {
        __dst_alloc_buckets__dmemL105R[i].prev = 0;
        __dst_alloc_buckets__dmemL105R[i].next = 0;
    }
    __dst_alloc_list_push__dmemL105R(0, 1);
}
__dst_alloc_size_t __dst_alloc_malloc__dmemL105R(__dst_alloc_size_t request) {
    request = request / sizeof(::NODE);
    if (request > (1 << ARRAY_LOG)) return 0;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemL105R(request);
    __dst_alloc_bucket_size_t original_bucket = bucket;
    while ((__dst_alloc_bucket_size_t)(bucket + 1) != 0) {
        __dst_alloc_size_t ptr = __dst_alloc_list_pop__dmemL105R(bucket);
        if (!ptr) {
            bucket--; continue;
        }
        __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemL105R(ptr, bucket);
        if (i != 0) __dst_alloc_flip_parent_split__dmemL105R(i);
        while (bucket < original_bucket) {
            i = ((i) * 2 + 1);
            __dst_alloc_clr_parent_split__dmemL105R(i);
            __dst_alloc_flip_parent_split__dmemL105R(i);
            bucket++;
            __dst_alloc_list_push__dmemL105R(bucket, __dst_alloc_index_for_node__dmemL105R(((i) + 1), bucket));
        }
        __dmemL105R[ptr]._link.prev = request;
        return ptr + 1;
    }
    return 0;
}
void __dst_alloc_free__dmemL105R(__dst_alloc_size_t ptr) {
    if (ptr == 0) return;
    ptr -= 1;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemL105R(__dmemL105R[ptr]._link.prev);
    __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemL105R(ptr, bucket);
    while (i != 0) {
        __dst_alloc_flip_parent_split__dmemL105R(i);
        if (__dst_alloc_test_parent_split__dmemL105R(i)) break;
        __dst_alloc_list_remove__dmemL105R(bucket, __dst_alloc_index_for_node__dmemL105R(((((i) - 1) ^ 1) + 1), bucket));
        i = (((i) - 1) / 2);
        bucket--;
    }
    __dst_alloc_list_push__dmemL105R(bucket, __dst_alloc_index_for_node__dmemL105R(i, bucket));
}

void init(__didxL105R *head)
{
   *head = 0L;
}

int *output_list(__didxL105R head,int *curr)
{
  __didxL105R temp;
  for (temp = head; temp; temp = (&(__dmemL105R + temp + 0U - 1U) -> _data) -> next) {
     *(curr++) = (&(__dmemL105R + temp + 0U - 1U) -> _data) -> data . info;
  }
  return curr;
}

__didxL105R add(__didxL105R node,DATA data)
{
  __didxL105R temp = (__didxL105R )(__dst_alloc_malloc__dmemL105R(sizeof(NODE )));
  if (temp == 0L) {
    g_fallback = true;
    return 0L;
  }
  (&(__dmemL105R + temp + 0U - 1U) -> _data) -> data = data;
  (&(__dmemL105R + temp + 0U - 1U) -> _data) -> next = node;
  node = temp;
  return node;
}

void add_at(__didxL105R node,DATA data)
{
  __didxL105R temp = (__didxL105R )(__dst_alloc_malloc__dmemL105R(sizeof(NODE )));
  if (temp == 0L) {
    g_fallback = true;
    return ;
  }
  (&(__dmemL105R + temp + 0U - 1U) -> _data) -> data = data;
  (&(__dmemL105R + temp + 0U - 1U) -> _data) -> next = (&(__dmemL105R + node + 0U - 1U) -> _data) -> next;
  (&(__dmemL105R + node + 0U - 1U) -> _data) -> next = temp;
}

void remove_node(__didxL105R head)
{
  __didxL105R temp = (&(__dmemL105R + head + 0U - 1U) -> _data) -> next;
  (&(__dmemL105R + head + 0U - 1U) -> _data) -> next = (&(__dmemL105R + (&(__dmemL105R + head + 0U - 1U) -> _data) -> next + 0U - 1U) -> _data) -> next;
  __dst_alloc_free__dmemL105R(temp);
}

struct __rect_packed_type_L1213R__L1214R 
{
  __didxL105R local0;
  __didxL105R local1;
  __didxL105R local2;
  unsigned int _location;
  __didxL105R _return;
}
;

__didxL105R reverse_rec(__didxL105R ptr,__didxL105R previous)
{
  struct __rect_packed_type_L1213R__L1214R __rect_packed_var_L1213R__L1214R[1 << ARRAY_LOG];
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
{
  }
  NODE *temp;
  if ((&(__dmemL105R + __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0 + 0U - 1U) -> _data) -> next == 0L) {
    (&(__dmemL105R + __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0 + 0U - 1U) -> _data) -> next = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local1;
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _return = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0;
    goto __rect_func_L0_L1213R__L1214R;
  }
   else {
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _location = 2U;
    __rect_packed_var_L1213R__L1214R[1 + __rect_packed_top_L1213R__L1214R] . local1 = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0;
    __rect_packed_var_L1213R__L1214R[1 + __rect_packed_top_L1213R__L1214R] . local0 = (&(__dmemL105R + __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0 + 0U - 1U) -> _data) -> next;
    ++__rect_packed_top_L1213R__L1214R;
    if (__rect_packed_top_L1213R__L1214R == 1 << ARRAY_LOG) 
      g_fallback = true;
    0;
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _location = 1U;
    goto __rect_func_L1_L1213R__L1214R;
    __rect_func_L2_L1213R__L1214R:
{
    }
    __didxL105R __rect_ret0_L1213R__L1214R = __rect_packed_var_L1213R__L1214R[1 + __rect_packed_top_L1213R__L1214R] . _return;
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local2 = __rect_ret0_L1213R__L1214R;
    (&(__dmemL105R + __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local0 + 0U - 1U) -> _data) -> next = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local1;
    __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . _return = __rect_packed_var_L1213R__L1214R[0 + __rect_packed_top_L1213R__L1214R] . local2;
    goto __rect_func_L0_L1213R__L1214R;
  }
  goto __rect_func_L0_L1213R__L1214R;
}

__didxL105R sort_list(__didxL105R head)
{
  __didxL105R tmpPtr = head;
  __didxL105R tmpNxt = (&(__dmemL105R + head + 0U - 1U) -> _data) -> next;
  DATA tmp;
  while(tmpNxt != 0L){
    while(tmpNxt != tmpPtr){
      if ((&(__dmemL105R + tmpNxt + 0U - 1U) -> _data) -> data . info < (&(__dmemL105R + tmpPtr + 0U - 1U) -> _data) -> data . info) {
        tmp = (&(__dmemL105R + tmpPtr + 0U - 1U) -> _data) -> data;
        (&(__dmemL105R + tmpPtr + 0U - 1U) -> _data) -> data = (&(__dmemL105R + tmpNxt + 0U - 1U) -> _data) -> data;
        (&(__dmemL105R + tmpNxt + 0U - 1U) -> _data) -> data = tmp;
      }
      tmpPtr = (&(__dmemL105R + tmpPtr + 0U - 1U) -> _data) -> next;
    }
    tmpPtr = head;
    tmpNxt = (&(__dmemL105R + tmpNxt + 0U - 1U) -> _data) -> next;
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
  __didxL105R head;
  __didxL105R node;
  DATA element;
  init(&head);
  for (i = 0; i < n; i++) {
    element . info = input[i];
    head = add(head,element);
  }
  int *curr = output;
  curr = output_list(head,curr);
   *(curr++) = - 1;
  node = (&(__dmemL105R + (&(__dmemL105R + (&(__dmemL105R + head + 0U - 1U) -> _data) -> next + 0U - 1U) -> _data) -> next + 0U - 1U) -> _data) -> next;
  element . info = 2000;
  add_at(node,element);
  curr = output_list(head,curr);
   *(curr++) = - 1;
  node = (&(__dmemL105R + (&(__dmemL105R + head + 0U - 1U) -> _data) -> next + 0U - 1U) -> _data) -> next;
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
