// C code for linked list merged sort
#include<stdlib.h>
bool g_fallback = false;
/* Link list node */

struct Node 
{
  int data;
  struct Node *next;
}
;
/* function prototypes */
struct Node *SortedMerge(struct Node *a,struct Node *b);
void FrontBackSplit(struct Node *source,struct Node **frontRef,struct Node **backRef);
/* sorts the linked list by changing next pointers (not data) */

struct __rect_packed_type_L975R__L976R 
{
  struct Node **local0;
  struct Node *local1;
  struct Node *local2;
  struct Node *local3;
  unsigned int _location;
}
;

void MergeSort(struct Node **headRef)
{
  struct __rect_packed_type_L975R__L976R __rect_packed_var_L975R__L976R[1024U];
  unsigned int __rect_packed_top_L975R__L976R = 0U;
  __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . _location = 1U;
  __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local0 = headRef;
  ++__rect_packed_top_L975R__L976R;
  __rect_func_L0_L975R__L976R:
  if (0U == __rect_packed_top_L975R__L976R) 
    return ;
  --__rect_packed_top_L975R__L976R;
  if (1U == __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . _location) 
    goto __rect_func_L1_L975R__L976R;
  if (2U == __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . _location) 
    goto __rect_func_L2_L975R__L976R;
  if (3U == __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . _location) 
    goto __rect_func_L3_L975R__L976R;
  __rect_func_L1_L975R__L976R:
  __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local1 =  *__rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local0;
  struct Node *a;
  struct Node *b;
/* Base case -- length 0 or 1 */
  if (__rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local1 == 0L || __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local1 -> next == 0L) {
    goto __rect_func_L0_L975R__L976R;
  }
/* Split head into 'a' and 'b' sublists */
  FrontBackSplit(__rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local1,&__rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local2,&__rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local3);
/* Recursively sort the sublists */
  __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . _location = 2U;
  __rect_packed_var_L975R__L976R[1 + __rect_packed_top_L975R__L976R] . local0 = &__rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local2;
  ++__rect_packed_top_L975R__L976R;
  if (__rect_packed_top_L975R__L976R == 1024U) 
g_fallback = true;
    0;
  __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . _location = 1U;
  goto __rect_func_L1_L975R__L976R;
  __rect_func_L2_L975R__L976R:
  0;
  __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . _location = 3U;
  __rect_packed_var_L975R__L976R[1 + __rect_packed_top_L975R__L976R] . local0 = &__rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local3;
  ++__rect_packed_top_L975R__L976R;
  if (__rect_packed_top_L975R__L976R == 1024U) 
g_fallback = true;
    0;
  __rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . _location = 1U;
  goto __rect_func_L1_L975R__L976R;
  __rect_func_L3_L975R__L976R:
  0;
/* answer = merge the two sorted lists together */
   *__rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local0 = SortedMerge(__rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local2,__rect_packed_var_L975R__L976R[0 + __rect_packed_top_L975R__L976R] . local3);
  goto __rect_func_L0_L975R__L976R;
}
/* See https://www.geeksforgeeks.org/?p=3622 for details of this
function */

struct __rect_packed_type_L971R__L972R 
{
  struct Node *local0;
  struct Node *local1;
  struct Node *local2;
  unsigned int _location;
  struct Node *_return;
}
;

struct Node *SortedMerge(struct Node *a,struct Node *b)
{
  struct __rect_packed_type_L971R__L972R __rect_packed_var_L971R__L972R[1024U];
  unsigned int __rect_packed_top_L971R__L972R = 0U;
  __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _location = 1U;
  __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local0 = a;
  __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local1 = b;
  ++__rect_packed_top_L971R__L972R;
  __rect_func_L0_L971R__L972R:
  if (0U == __rect_packed_top_L971R__L972R) 
    return __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _return;
  --__rect_packed_top_L971R__L972R;
  if (1U == __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _location) 
    goto __rect_func_L1_L971R__L972R;
  if (2U == __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _location) 
    goto __rect_func_L2_L971R__L972R;
  if (3U == __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _location) 
    goto __rect_func_L3_L971R__L972R;
  __rect_func_L1_L971R__L972R:
  __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local2 = 0L;
/* Base cases */
  if (__rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local0 == 0L) {
    __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _return = __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local1;
    goto __rect_func_L0_L971R__L972R;
  }
   else if (__rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local1 == 0L) {
    __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _return = __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local0;
    goto __rect_func_L0_L971R__L972R;
  }
/* Pick either a or b, and recur */
  if (__rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local0 -> data <= __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local1 -> data) {
    __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local2 = __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local0;
    __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _location = 2U;
    __rect_packed_var_L971R__L972R[1 + __rect_packed_top_L971R__L972R] . local1 = __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local1;
    __rect_packed_var_L971R__L972R[1 + __rect_packed_top_L971R__L972R] . local0 = __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local0 -> next;
    ++__rect_packed_top_L971R__L972R;
    if (__rect_packed_top_L971R__L972R == 1024U) 
g_fallback = true;
      0;
    __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _location = 1U;
    goto __rect_func_L1_L971R__L972R;
    __rect_func_L2_L971R__L972R:
    struct Node *__rect_ret0_L971R__L972R = __rect_packed_var_L971R__L972R[1 + __rect_packed_top_L971R__L972R] . _return;
    __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local2 -> next = __rect_ret0_L971R__L972R;
  }
   else {
    __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local2 = __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local1;
    __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _location = 3U;
    __rect_packed_var_L971R__L972R[1 + __rect_packed_top_L971R__L972R] . local1 = __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local1 -> next;
    __rect_packed_var_L971R__L972R[1 + __rect_packed_top_L971R__L972R] . local0 = __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local0;
    ++__rect_packed_top_L971R__L972R;
    if (__rect_packed_top_L971R__L972R == 1024U) 
g_fallback = true;
      0;
    __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _location = 1U;
    goto __rect_func_L1_L971R__L972R;
    __rect_func_L3_L971R__L972R:
    struct Node *__rect_ret1_L971R__L972R = __rect_packed_var_L971R__L972R[1 + __rect_packed_top_L971R__L972R] . _return;
    __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local2 -> next = __rect_ret1_L971R__L972R;
  }
  __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . _return = __rect_packed_var_L971R__L972R[0 + __rect_packed_top_L971R__L972R] . local2;
  goto __rect_func_L0_L971R__L972R;
  goto __rect_func_L0_L971R__L972R;
}
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
	and return the two lists using the reference parameters.
	If the length is odd, the extra node should go in the front list.
	Uses the fast/slow pointer strategy. */

void FrontBackSplit(struct Node *source,struct Node **frontRef,struct Node **backRef)
{
  struct Node *fast;
  struct Node *slow;
  slow = source;
  fast = source -> next;
/* Advance 'fast' two nodes, and advance 'slow' one node */
  while(fast != 0L){
    fast = fast -> next;
    if (fast != 0L) {
      slow = slow -> next;
      fast = fast -> next;
    }
  }
/* 'slow' is before the midpoint in the list, so split it in two
	at that point. */
   *frontRef = source;
   *backRef = slow -> next;
  slow -> next = 0L;
}
/* Function to print nodes in a given linked list */

int *printList(struct Node *node,int *output)
{
  while(node != 0L){
     *(output++) = node -> data;
    node = node -> next;
  }
  return output;
}
/* Function to insert a node at the beginging of the linked list */

void push(struct Node **head_ref,int new_data)
{
/* allocate node */
  struct Node *new_node = (struct Node *)(malloc(sizeof(struct Node )));
  if (new_node == 0L) {
    g_fallback = true;
    return ;
  }
/* put in the data */
  new_node -> data = new_data;
/* link the old list off the new node */
  new_node -> next =  *head_ref;
/* move the head to point to the new node */
   *head_ref = new_node;
}
extern "C" {
/* Drier program to test above functions*/

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
/* Start with the empty list */
  struct Node *res = 0L;
  struct Node *a = 0L;
/* Let us create a unsorted linked lists to test the functions */
  for (int i = 0; i < n; i++) {
    push(&a,input[i]);
  }
/* Sort the above created Linked List */
  MergeSort(&a);
  output = printList(a,output);
   *fallback = g_fallback;
}
}
