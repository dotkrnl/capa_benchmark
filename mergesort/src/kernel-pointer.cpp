
struct __dst_alloc_list_base_t 
{
  unsigned int prev;
  unsigned int next;
}
;
// type __didxclass_Node was struct ::Node{int data;struct Node *next;}*
typedef unsigned int __didxclass_Node;
// C code for linked list merged sort
#include<stdlib.h>
bool g_fallback = false;
/* Link list node */

struct Node 
{
  int data;
  __didxclass_Node next;
}
;
/* function prototypes */

struct __dst_alloc_list__dmemclass_Node 
{
  struct __dst_alloc_list_base_t _link;
  struct Node _data;
}
;
struct __dst_alloc_list__dmemclass_Node __dmemclass_Node[1024U];
unsigned int __dst_alloc_malloc__dmemclass_Node(unsigned int );
void __dst_alloc_free__dmemclass_Node(unsigned int );
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
unsigned char __dst_alloc_node_split__dmemclass_Node[(1 << (10 - 1)) / 8];
static unsigned char __dst_alloc_test_parent_split__dmemclass_Node(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    return (__dst_alloc_node_split__dmemclass_Node[index / 8] >> (index % 8)) & 1;
}
static void __dst_alloc_flip_parent_split__dmemclass_Node(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemclass_Node[index / 8] ^= 1 << (index % 8);
}
static void __dst_alloc_clr_parent_split__dmemclass_Node(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemclass_Node[index / 8] &= ~(1 << (index % 8));
}
struct __dst_alloc_list_base_t __dst_alloc_buckets__dmemclass_Node[10] = {{1, 1}};
static __dst_alloc_bucket_size_t __dst_alloc_bucket_for_request__dmemclass_Node(
        __dst_alloc_size_t request) {
    __dst_alloc_bucket_size_t bucket = 10 - 1;
    __dst_alloc_size_t size = 2;
    while (size < request) {
        size <<= 1;
        bucket -= 1;
    }
    return bucket;
}
static void __dst_alloc_list_push__dmemclass_Node(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dst_alloc_buckets__dmemclass_Node[bucket].prev;
    __dmemclass_Node[entry]._link.prev = prev;
    __dmemclass_Node[entry]._link.next = 0;
    if (prev == 0) __dst_alloc_buckets__dmemclass_Node[bucket].next = entry;
    else __dmemclass_Node[prev]._link.next = entry;
    __dst_alloc_buckets__dmemclass_Node[bucket].prev = entry;
}
static void __dst_alloc_list_remove__dmemclass_Node(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dmemclass_Node[entry]._link.prev;
    __dst_alloc_size_t next = __dmemclass_Node[entry]._link.next;
    if (prev == 0) __dst_alloc_buckets__dmemclass_Node[bucket].next = next;
    else __dmemclass_Node[prev]._link.next = next;
    if (next == 0) __dst_alloc_buckets__dmemclass_Node[bucket].prev = prev;
    else __dmemclass_Node[next]._link.prev = prev;
}
static __dst_alloc_size_t __dst_alloc_list_pop__dmemclass_Node(
        __dst_alloc_bucket_size_t bucket) {
    __dst_alloc_size_t back = __dst_alloc_buckets__dmemclass_Node[bucket].prev;
    if (back == 0) return 0;
    __dst_alloc_list_remove__dmemclass_Node(bucket, back);
    return back;
}
static __dst_alloc_size_t __dst_alloc_index_for_node__dmemclass_Node(
        __dst_alloc_size_t bucket_index,
        __dst_alloc_bucket_size_t bucket) {
    return 1 + ((bucket_index - (1 << bucket) + 1) << (10 - bucket));
}
static __dst_alloc_size_t __dst_alloc_node_for_index__dmemclass_Node(
        __dst_alloc_size_t global_index,
        __dst_alloc_bucket_size_t bucket) {
    return ((global_index - 1) >> (10 - bucket)) + (1 << bucket) - 1;
}
void __dst_alloc_init__dmemclass_Node() {
    for (int i = 0; i < 10; i++) {
        __dst_alloc_buckets__dmemclass_Node[i].prev = 0;
        __dst_alloc_buckets__dmemclass_Node[i].next = 0;
    }
    __dst_alloc_list_push__dmemclass_Node(0, 1);
}
__dst_alloc_size_t __dst_alloc_malloc__dmemclass_Node(__dst_alloc_size_t request) {
    request = request / sizeof(struct ::Node);
    if (request > (1 << 10)) return 0;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemclass_Node(request);
    __dst_alloc_bucket_size_t original_bucket = bucket;
    while ((__dst_alloc_bucket_size_t)(bucket + 1) != 0) {
        __dst_alloc_size_t ptr = __dst_alloc_list_pop__dmemclass_Node(bucket);
        if (!ptr) {
            bucket--; continue;
        }
        __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemclass_Node(ptr, bucket);
        if (i != 0) __dst_alloc_flip_parent_split__dmemclass_Node(i);
        while (bucket < original_bucket) {
            i = ((i) * 2 + 1);
            __dst_alloc_clr_parent_split__dmemclass_Node(i);
            __dst_alloc_flip_parent_split__dmemclass_Node(i);
            bucket++;
            __dst_alloc_list_push__dmemclass_Node(bucket, __dst_alloc_index_for_node__dmemclass_Node(((i) + 1), bucket));
        }
        __dmemclass_Node[ptr]._link.prev = request;
        return ptr + 1;
    }
    return 0;
}
void __dst_alloc_free__dmemclass_Node(__dst_alloc_size_t ptr) {
    if (ptr == 0) return;
    ptr -= 1;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemclass_Node(__dmemclass_Node[ptr]._link.prev);
    __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemclass_Node(ptr, bucket);
    while (i != 0) {
        __dst_alloc_flip_parent_split__dmemclass_Node(i);
        if (__dst_alloc_test_parent_split__dmemclass_Node(i)) break;
        __dst_alloc_list_remove__dmemclass_Node(bucket, __dst_alloc_index_for_node__dmemclass_Node(((((i) - 1) ^ 1) + 1), bucket));
        i = (((i) - 1) / 2);
        bucket--;
    }
    __dst_alloc_list_push__dmemclass_Node(bucket, __dst_alloc_index_for_node__dmemclass_Node(i, bucket));
}
__didxclass_Node SortedMerge(__didxclass_Node a,__didxclass_Node b);
/* sorts the linked list by changing next pointers (not data) */

__didxclass_Node MergeSort(__didxclass_Node head)
{
/* Base case -- length 0 or 1 */
  if (head == 0L || (&(__dmemclass_Node + head + 0U - 1U) -> _data) -> next == 0L) {
    return head;
  }
  __didxclass_Node fast = (&(__dmemclass_Node + head + 0U - 1U) -> _data) -> next;
  __didxclass_Node slow = head;
/* Advance 'fast' two nodes, and advance 'slow' one node */
  while(fast != 0L){
    fast = (&(__dmemclass_Node + fast + 0U - 1U) -> _data) -> next;
    if (fast != 0L) {
      slow = (&(__dmemclass_Node + slow + 0U - 1U) -> _data) -> next;
      fast = (&(__dmemclass_Node + fast + 0U - 1U) -> _data) -> next;
    }
  }
/* 'slow' is before the midpoint in the list, so split it in two
at that point. */
  __didxclass_Node a = head;
  __didxclass_Node b = (&(__dmemclass_Node + slow + 0U - 1U) -> _data) -> next;
  (&(__dmemclass_Node + slow + 0U - 1U) -> _data) -> next = 0L;
/* Recursively sort the sublists */
  a = MergeSort(a);
  b = MergeSort(b);
/* answer = merge the two sorted lists together */
  return SortedMerge(a,b);
}
/* See https://www.geeksforgeeks.org/?p=3622 for details of this
function */

__didxclass_Node SortedMerge(__didxclass_Node a,__didxclass_Node b)
{
  __didxclass_Node result = 0L;
/* Base cases */
  if (a == 0L) 
    return b;
   else if (b == 0L) 
    return a;
/* Pick either a or b, and recur */
  if ((&(__dmemclass_Node + a + 0U - 1U) -> _data) -> data <= (&(__dmemclass_Node + b + 0U - 1U) -> _data) -> data) {
    result = a;
    (&(__dmemclass_Node + result + 0U - 1U) -> _data) -> next = SortedMerge((&(__dmemclass_Node + a + 0U - 1U) -> _data) -> next,b);
  }
   else {
    result = b;
    (&(__dmemclass_Node + result + 0U - 1U) -> _data) -> next = SortedMerge(a,(&(__dmemclass_Node + b + 0U - 1U) -> _data) -> next);
  }
  return result;
}
/* Function to print nodes in a given linked list */

int *printList(__didxclass_Node node,int *output)
{
  while(node != 0L){
     *(output++) = (&(__dmemclass_Node + node + 0U - 1U) -> _data) -> data;
    node = (&(__dmemclass_Node + node + 0U - 1U) -> _data) -> next;
  }
  return output;
}
/* Function to insert a node at the beginging of the linked list */

void push(__didxclass_Node *head_ref,int new_data)
{
/* allocate node */
  __didxclass_Node new_node = (__didxclass_Node )(__dst_alloc_malloc__dmemclass_Node(sizeof(struct Node )));
  if (new_node == 0L) {
    g_fallback = true;
    return ;
  }
/* put in the data */
  (&(__dmemclass_Node + new_node + 0U - 1U) -> _data) -> data = new_data;
/* link the old list off the new node */
  (&(__dmemclass_Node + new_node + 0U - 1U) -> _data) -> next =  *head_ref;
/* move the head to point to the new node */
   *head_ref = new_node;
}
extern "C" {
/* Drier program to test above functions*/

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
/* Start with the empty list */
  __didxclass_Node res = 0L;
  __didxclass_Node a = 0L;
/* Let us create a unsorted linked lists to test the functions */
  for (int i = 0; i < n; i++) {
    push(&a,input[i]);
  }
/* Sort the above created Linked List */
  a = MergeSort(a);
  output = printList(a,output);
   *fallback = g_fallback;
}
}
