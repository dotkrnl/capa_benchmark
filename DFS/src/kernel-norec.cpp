#include <stdlib.h>
#include <stdio.h>

struct btnode 
{
  int value;
  struct btnode *left;
  struct btnode *right;
}
;
typedef struct btnode node;
/* function declarations */
void insert(node *,node *);
void dfs_traverse(node *);
/*global declarations */
node *root = 0L;
int val;
int front = 0;
int rear = - 1;
int i;
int queue[20];
bool g_fallback = false;
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
  node *newitem = 0L;
  int num = 10;
  int i = 0;
  while(i < n){
    newitem = ((node *)(malloc(sizeof(node ))));
    if (newitem == 0L) 
      g_fallback = true;
    newitem -> left = newitem -> right = 0L;
    newitem -> value = input[i];
    if (root == 0L) 
      root = newitem;
     else {
      insert(newitem,root);
    }
    i++;
  }
  queue[++rear] = root -> value;
  dfs_traverse(root);
  for (i = 0; i < n; i++) 
    output[i] = queue[i];
   *fallback = g_fallback;
}
}
/* inserting nodes of a tree */

struct __rect_packed_type_L1202R__L1203R 
{
  node *local0;
  node *local1;
  unsigned int _location;
}
;

void insert(node *newitem,node *root)
{
  struct __rect_packed_type_L1202R__L1203R __rect_packed_var_L1202R__L1203R[1024U];
  unsigned int __rect_packed_top_L1202R__L1203R = 0U;
  __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . _location = 1U;
  __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local0 = newitem;
  __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local1 = root;
  ++__rect_packed_top_L1202R__L1203R;
  __rect_func_L0_L1202R__L1203R:
  if (0U == __rect_packed_top_L1202R__L1203R) 
    return ;
  --__rect_packed_top_L1202R__L1203R;
  if (1U == __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . _location) 
    goto __rect_func_L1_L1202R__L1203R;
  if (2U == __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . _location) 
    goto __rect_func_L2_L1202R__L1203R;
  if (3U == __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . _location) 
    goto __rect_func_L3_L1202R__L1203R;
  __rect_func_L1_L1202R__L1203R:
  if (__rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local0 -> value > __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local1 -> value) {
    if (__rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local1 -> right == 0L) 
      __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local1 -> right = __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local0;
     else {
      __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . _location = 2U;
      __rect_packed_var_L1202R__L1203R[1 + __rect_packed_top_L1202R__L1203R] . local1 = __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local1 -> right;
      __rect_packed_var_L1202R__L1203R[1 + __rect_packed_top_L1202R__L1203R] . local0 = __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local0;
      ++__rect_packed_top_L1202R__L1203R;
      if (__rect_packed_top_L1202R__L1203R == 1024U) 
g_fallback = true;
        0;
      __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . _location = 1U;
      goto __rect_func_L1_L1202R__L1203R;
      __rect_func_L2_L1202R__L1203R:
      0;
    }
  }
  if (__rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local0 -> value < __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local1 -> value) {
    if (__rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local1 -> left == 0L) 
      __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local1 -> left = __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local0;
     else {
      __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . _location = 3U;
      __rect_packed_var_L1202R__L1203R[1 + __rect_packed_top_L1202R__L1203R] . local1 = __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local1 -> left;
      __rect_packed_var_L1202R__L1203R[1 + __rect_packed_top_L1202R__L1203R] . local0 = __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . local0;
      ++__rect_packed_top_L1202R__L1203R;
      if (__rect_packed_top_L1202R__L1203R == 1024U) 
g_fallback = true;
        0;
      __rect_packed_var_L1202R__L1203R[0 + __rect_packed_top_L1202R__L1203R] . _location = 1U;
      goto __rect_func_L1_L1202R__L1203R;
      __rect_func_L3_L1202R__L1203R:
      0;
    }
  }
  goto __rect_func_L0_L1202R__L1203R;
}
/* displaying elements using BFS traversal */

struct __rect_packed_type_L1204R__L1205R 
{
  node *local0;
  unsigned int _location;
}
;

void dfs_traverse(node *root)
{
  struct __rect_packed_type_L1204R__L1205R __rect_packed_var_L1204R__L1205R[1024U];
  unsigned int __rect_packed_top_L1204R__L1205R = 0U;
  __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . _location = 1U;
  __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . local0 = root;
  ++__rect_packed_top_L1204R__L1205R;
  __rect_func_L0_L1204R__L1205R:
  if (0U == __rect_packed_top_L1204R__L1205R) 
    return ;
  --__rect_packed_top_L1204R__L1205R;
  if (1U == __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . _location) 
    goto __rect_func_L1_L1204R__L1205R;
  if (2U == __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . _location) 
    goto __rect_func_L2_L1204R__L1205R;
  if (3U == __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . _location) 
    goto __rect_func_L3_L1204R__L1205R;
  __rect_func_L1_L1204R__L1205R:
  if (__rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . local0 -> left != 0L) {
    queue[++rear] = __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . local0 -> left -> value;
    __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . _location = 2U;
    __rect_packed_var_L1204R__L1205R[1 + __rect_packed_top_L1204R__L1205R] . local0 = __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . local0 -> left;
    ++__rect_packed_top_L1204R__L1205R;
    if (__rect_packed_top_L1204R__L1205R == 1024U) 
g_fallback = true;
      0;
    __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . _location = 1U;
    goto __rect_func_L1_L1204R__L1205R;
    __rect_func_L2_L1204R__L1205R:
    0;
  }
  if (__rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . local0 -> right != 0L) {
    queue[++rear] = __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . local0 -> right -> value;
    __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . _location = 3U;
    __rect_packed_var_L1204R__L1205R[1 + __rect_packed_top_L1204R__L1205R] . local0 = __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . local0 -> right;
    ++__rect_packed_top_L1204R__L1205R;
    if (__rect_packed_top_L1204R__L1205R == 1024U) 
g_fallback = true;
      0;
    __rect_packed_var_L1204R__L1205R[0 + __rect_packed_top_L1204R__L1205R] . _location = 1U;
    goto __rect_func_L1_L1204R__L1205R;
    __rect_func_L3_L1204R__L1205R:
    0;
  }
  goto __rect_func_L0_L1204R__L1205R;
}
