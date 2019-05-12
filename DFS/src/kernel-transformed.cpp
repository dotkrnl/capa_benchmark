
struct __dst_alloc_list_base_t 
{
  unsigned int prev;
  unsigned int next;
}
;
// type __didxL104R was ::node*
typedef unsigned int __didxL104R;
#include <stdlib.h>
#include <stdio.h>

struct btnode 
{
  int value;
  __didxL104R left;
  __didxL104R right;
}
;
typedef struct btnode node;
/* function declarations */

struct __dst_alloc_list__dmemL104R 
{
  struct __dst_alloc_list_base_t _link;
  node _data;
}
;
struct __dst_alloc_list__dmemL104R __dmemL104R[1 << ARRAY_LOG];
unsigned int __dst_alloc_malloc__dmemL104R(unsigned int );
void __dst_alloc_free__dmemL104R(unsigned int );
typedef unsigned int __dst_alloc_size_t;
typedef unsigned char __dst_alloc_bucket_size_t;
unsigned char __dst_alloc_node_split__dmemL104R[(1 << ARRAY_LOG - 1) / 8];

static unsigned char __dst_alloc_test_parent_split__dmemL104R(__dst_alloc_size_t index)
{
  index = (index - 1) / 2;
  return (__dst_alloc_node_split__dmemL104R[index / 8] >> index % 8 & 1);
}

static void __dst_alloc_flip_parent_split__dmemL104R(__dst_alloc_size_t index)
{
  index = (index - 1) / 2;
  __dst_alloc_node_split__dmemL104R[index / 8] ^= 1 << index % 8;
}

static void __dst_alloc_clr_parent_split__dmemL104R(__dst_alloc_size_t index)
{
  index = (index - 1) / 2;
  __dst_alloc_node_split__dmemL104R[index / 8] &= ~(1 << index % 8);
}
struct __dst_alloc_list_base_t __dst_alloc_buckets__dmemL104R[ARRAY_LOG] = {{(1), (1)}};

static __dst_alloc_bucket_size_t __dst_alloc_bucket_for_request__dmemL104R(__dst_alloc_size_t request)
{
  __dst_alloc_bucket_size_t bucket = (ARRAY_LOG - 1);
  __dst_alloc_size_t size = 2;
  while(size < request){
    size <<= 1;
    bucket -= 1;
  }
  return bucket;
}

static void __dst_alloc_list_push__dmemL104R(__dst_alloc_bucket_size_t bucket,__dst_alloc_size_t entry)
{
  __dst_alloc_size_t prev = __dst_alloc_buckets__dmemL104R[bucket] . prev;
  __dmemL104R[entry] . _link . prev = prev;
  __dmemL104R[entry] . _link . next = 0;
  if (prev == 0) 
    __dst_alloc_buckets__dmemL104R[bucket] . next = entry;
   else 
    __dmemL104R[prev] . _link . next = entry;
  __dst_alloc_buckets__dmemL104R[bucket] . prev = entry;
}

static void __dst_alloc_list_remove__dmemL104R(__dst_alloc_bucket_size_t bucket,__dst_alloc_size_t entry)
{
  __dst_alloc_size_t prev = __dmemL104R[entry] . _link . prev;
  __dst_alloc_size_t next = __dmemL104R[entry] . _link . next;
  if (prev == 0) 
    __dst_alloc_buckets__dmemL104R[bucket] . next = next;
   else 
    __dmemL104R[prev] . _link . next = next;
  if (next == 0) 
    __dst_alloc_buckets__dmemL104R[bucket] . prev = prev;
   else 
    __dmemL104R[next] . _link . prev = prev;
}

static __dst_alloc_size_t __dst_alloc_list_pop__dmemL104R(__dst_alloc_bucket_size_t bucket)
{
  __dst_alloc_size_t back = __dst_alloc_buckets__dmemL104R[bucket] . prev;
  if (back == 0) 
    return 0;
  __dst_alloc_list_remove__dmemL104R(bucket,back);
  return back;
}

static __dst_alloc_size_t __dst_alloc_index_for_node__dmemL104R(__dst_alloc_size_t bucket_index,__dst_alloc_bucket_size_t bucket)
{
  return 1 + (bucket_index - (1 << bucket) + 1 << ARRAY_LOG - bucket);
}

static __dst_alloc_size_t __dst_alloc_node_for_index__dmemL104R(__dst_alloc_size_t global_index,__dst_alloc_bucket_size_t bucket)
{
  return (global_index - 1 >> ARRAY_LOG - bucket) + (1 << bucket) - 1;
}

void __dst_alloc_init__dmemL104R()
{
  for (int i = 0; i < ARRAY_LOG; i++) {
    __dst_alloc_buckets__dmemL104R[i] . prev = 0;
    __dst_alloc_buckets__dmemL104R[i] . next = 0;
  }
  __dst_alloc_list_push__dmemL104R(0,1);
}

unsigned int __dst_alloc_malloc__dmemL104R(__dst_alloc_size_t request)
{
  request = (request / sizeof(node ));
  if (request > (1 << ARRAY_LOG)) 
    return 0;
  __dst_alloc_bucket_size_t bucket = __dst_alloc_bucket_for_request__dmemL104R(request);
  __dst_alloc_bucket_size_t original_bucket = bucket;
  while(((__dst_alloc_bucket_size_t )(bucket + 1)) != 0){
    __dst_alloc_size_t ptr = __dst_alloc_list_pop__dmemL104R(bucket);
    if (!ptr) {
      bucket--;
      continue; 
    }
    __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemL104R(ptr,bucket);
    if (i != 0) 
      __dst_alloc_flip_parent_split__dmemL104R(i);
    while(bucket < original_bucket){
      i = i * 2 + 1;
      __dst_alloc_clr_parent_split__dmemL104R(i);
      __dst_alloc_flip_parent_split__dmemL104R(i);
      bucket++;
      __dst_alloc_list_push__dmemL104R(bucket,(__dst_alloc_index_for_node__dmemL104R(i + 1,bucket)));
    }
    __dmemL104R[ptr] . _link . prev = request;
    return ptr + 1;
  }
  return 0;
}

void __dst_alloc_free__dmemL104R(__dst_alloc_size_t ptr)
{
  if (ptr == 0) 
    return ;
  ptr -= 1;
  __dst_alloc_bucket_size_t bucket = __dst_alloc_bucket_for_request__dmemL104R(__dmemL104R[ptr] . _link . prev);
  __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemL104R(ptr,bucket);
  while(i != 0){
    __dst_alloc_flip_parent_split__dmemL104R(i);
    if ((__dst_alloc_test_parent_split__dmemL104R(i))) 
      break; 
    __dst_alloc_list_remove__dmemL104R(bucket,(__dst_alloc_index_for_node__dmemL104R((i - 1 ^ 1) + 1,bucket)));
    i = (i - 1) / 2;
    bucket--;
  }
  __dst_alloc_list_push__dmemL104R(bucket,(__dst_alloc_index_for_node__dmemL104R(i,bucket)));
}
void insert(__didxL104R ,__didxL104R );
void dfs_traverse(__didxL104R );
/*global declarations */
__didxL104R root = 0L;
int val;
int front = 0;
int rear = - 1;
int i;
int queue[20];
bool g_fallback = false;
extern "C" {

void process_top(int n,int *input,int *output,int *fallback)
{
  
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=fallback offset=slave bundle=gmem
  
#pragma HLS INTERFACE s_axilite port=n bundle=control
  
#pragma HLS INTERFACE s_axilite port=input bundle=control
  
#pragma HLS INTERFACE s_axilite port=output bundle=control
  
#pragma HLS INTERFACE s_axilite port=fallback bundle=control
  
#pragma HLS INTERFACE s_axilite port=return bundle=control
  __didxL104R newitem = 0L;
  int num = 10;
  int i = 0;
  while(i < n){
    newitem = ((__didxL104R )(__dst_alloc_malloc__dmemL104R((sizeof(node )))));
    if (newitem == 0L) 
      g_fallback = true;
    (&(__dmemL104R + newitem + 0U - 1U) -> _data) -> left = (&(__dmemL104R + newitem + 0U - 1U) -> _data) -> right = 0L;
    (&(__dmemL104R + newitem + 0U - 1U) -> _data) -> value = input[i];
    if (root == 0L) 
      root = newitem;
     else {
      insert(newitem,root);
    }
    i++;
  }
  dfs_traverse(root);
  for (i = 0; i < n; i++) 
    output[i] = queue[i];
  fallback[0] = g_fallback;
}
}
/* inserting nodes of a tree */

struct __rect_packed_type_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R 
{
  __didxL104R local0;
  __didxL104R local1;
  unsigned int _location;
}
;

void insert(__didxL104R newitem,__didxL104R root)
{
  volatile struct __rect_packed_type_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[1 << ARRAY_LOG];
  volatile unsigned int __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R = 0U;
  __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . _location = 1U;
  __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local0 = newitem;
  __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 = root;
  ++__rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R;
  __rect_func_L0_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R:
  if (0U == __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R) 
    return ;
  --__rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R;
  if (1U == __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . _location) 
    goto __rect_func_L1_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R;
  if (2U == __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . _location) 
    goto __rect_func_L2_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R;
  if (3U == __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . _location) 
    goto __rect_func_L3_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R;
  __rect_func_L1_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R:
  if ((&(__dmemL104R + __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local0 + 0U - 1U) -> _data) -> value > (&(__dmemL104R + __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 + 0U - 1U) -> _data) -> value) {
    if (((&(__dmemL104R + __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 + 0U - 1U) -> _data) -> right) == 0L) 
      (&(__dmemL104R + __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 + 0U - 1U) -> _data) -> right = __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local0;
     else {
      if (__rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R + 1U == 1 << ARRAY_LOG) 
g_fallback = true;
        0;
      __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . _location = 2U;
      __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[1 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 = (&(__dmemL104R + __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 + 0U - 1U) -> _data) -> right;
      __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[1 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local0 = __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local0;
      ++__rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R;
      __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . _location = 1U;
      goto __rect_func_L1_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R;
      __rect_func_L2_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R:
      0;
    }
  }
  if ((&(__dmemL104R + __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local0 + 0U - 1U) -> _data) -> value < (&(__dmemL104R + __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 + 0U - 1U) -> _data) -> value) {
    if (((&(__dmemL104R + __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 + 0U - 1U) -> _data) -> left) == 0L) 
      (&(__dmemL104R + __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 + 0U - 1U) -> _data) -> left = __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local0;
     else {
      if (__rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R + 1U == 1 << ARRAY_LOG) 
g_fallback = true;
        0;
      __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . _location = 3U;
      __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[1 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 = (&(__dmemL104R + __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local1 + 0U - 1U) -> _data) -> left;
      __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[1 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local0 = __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . local0;
      ++__rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R;
      __rect_packed_var_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R[0 + __rect_packed_top_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R] . _location = 1U;
      goto __rect_func_L1_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R;
      __rect_func_L3_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R:
      0;
    }
  }
  goto __rect_func_L0_insert___Fb_v_Gb__L1R__sep__L1R__Fe___L1228R;
}
/* displaying elements using BFS traversal */

struct __rect_packed_type_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R 
{
  __didxL104R local0;
  unsigned int _location;
}
;

void dfs_traverse(__didxL104R root)
{
  volatile struct __rect_packed_type_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[1 << ARRAY_LOG];
  volatile unsigned int __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R = 0U;
  __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . _location = 1U;
  __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . local0 = root;
  ++__rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R;
  __rect_func_L0_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R:
  if (0U == __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R) 
    return ;
  --__rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R;
  if (1U == __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . _location) 
    goto __rect_func_L1_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R;
  if (2U == __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . _location) 
    goto __rect_func_L2_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R;
  if (3U == __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . _location) 
    goto __rect_func_L3_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R;
  __rect_func_L1_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R:
  if (((&(__dmemL104R + __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . local0 + 0U - 1U) -> _data) -> left) != 0L) {
    if (__rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R + 1U == 1 << ARRAY_LOG) 
g_fallback = true;
      0;
    __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . _location = 2U;
    __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[1 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . local0 = (&(__dmemL104R + __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . local0 + 0U - 1U) -> _data) -> left;
    ++__rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R;
    __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . _location = 1U;
    goto __rect_func_L1_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R;
    __rect_func_L2_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R:
    0;
  }
  queue[++rear] = (&(__dmemL104R + __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . local0 + 0U - 1U) -> _data) -> value;
  if (((&(__dmemL104R + __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . local0 + 0U - 1U) -> _data) -> right) != 0L) {
    if (__rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R + 1U == 1 << ARRAY_LOG) 
g_fallback = true;
      0;
    __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . _location = 3U;
    __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[1 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . local0 = (&(__dmemL104R + __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . local0 + 0U - 1U) -> _data) -> right;
    ++__rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R;
    __rect_packed_var_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R[0 + __rect_packed_top_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R] . _location = 1U;
    goto __rect_func_L1_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R;
    __rect_func_L3_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R:
    0;
  }
  goto __rect_func_L0_dfs_traverse___Fb_v_Gb__L1R__Fe___L1229R;
}
