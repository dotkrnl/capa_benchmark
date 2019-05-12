
struct __dst_alloc_list_base_t 
{
  unsigned int prev;
  unsigned int next;
}
;
// type __didx__Pb__class_node__Pe__ was struct ::node{int substring_index;__didxclass_node fail;__didxclass_node(next)[26];}**

struct __dst_alloc_list__dmemUi 
{
  struct __dst_alloc_list_base_t _link;
  unsigned int _data;
}
;
struct __dst_alloc_list__dmemUi __dmemUi[1024U];
unsigned int __dst_alloc_malloc__dmemUi(unsigned int );
void __dst_alloc_free__dmemUi(unsigned int );
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
unsigned char __dst_alloc_node_split__dmemUi[(1 << (10 - 1)) / 8];
static unsigned char __dst_alloc_test_parent_split__dmemUi(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    return (__dst_alloc_node_split__dmemUi[index / 8] >> (index % 8)) & 1;
}
static void __dst_alloc_flip_parent_split__dmemUi(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemUi[index / 8] ^= 1 << (index % 8);
}
static void __dst_alloc_clr_parent_split__dmemUi(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemUi[index / 8] &= ~(1 << (index % 8));
}
struct __dst_alloc_list_base_t __dst_alloc_buckets__dmemUi[10] = {{1, 1}};
static __dst_alloc_bucket_size_t __dst_alloc_bucket_for_request__dmemUi(
        __dst_alloc_size_t request) {
    __dst_alloc_bucket_size_t bucket = 10 - 1;
    __dst_alloc_size_t size = 2;
    while (size < request) {
        size <<= 1;
        bucket -= 1;
    }
    return bucket;
}
static void __dst_alloc_list_push__dmemUi(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dst_alloc_buckets__dmemUi[bucket].prev;
    __dmemUi[entry]._link.prev = prev;
    __dmemUi[entry]._link.next = 0;
    if (prev == 0) __dst_alloc_buckets__dmemUi[bucket].next = entry;
    else __dmemUi[prev]._link.next = entry;
    __dst_alloc_buckets__dmemUi[bucket].prev = entry;
}
static void __dst_alloc_list_remove__dmemUi(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dmemUi[entry]._link.prev;
    __dst_alloc_size_t next = __dmemUi[entry]._link.next;
    if (prev == 0) __dst_alloc_buckets__dmemUi[bucket].next = next;
    else __dmemUi[prev]._link.next = next;
    if (next == 0) __dst_alloc_buckets__dmemUi[bucket].prev = prev;
    else __dmemUi[next]._link.prev = prev;
}
static __dst_alloc_size_t __dst_alloc_list_pop__dmemUi(
        __dst_alloc_bucket_size_t bucket) {
    __dst_alloc_size_t back = __dst_alloc_buckets__dmemUi[bucket].prev;
    if (back == 0) return 0;
    __dst_alloc_list_remove__dmemUi(bucket, back);
    return back;
}
static __dst_alloc_size_t __dst_alloc_index_for_node__dmemUi(
        __dst_alloc_size_t bucket_index,
        __dst_alloc_bucket_size_t bucket) {
    return 1 + ((bucket_index - (1 << bucket) + 1) << (10 - bucket));
}
static __dst_alloc_size_t __dst_alloc_node_for_index__dmemUi(
        __dst_alloc_size_t global_index,
        __dst_alloc_bucket_size_t bucket) {
    return ((global_index - 1) >> (10 - bucket)) + (1 << bucket) - 1;
}
void __dst_alloc_init__dmemUi() {
    for (int i = 0; i < 10; i++) {
        __dst_alloc_buckets__dmemUi[i].prev = 0;
        __dst_alloc_buckets__dmemUi[i].next = 0;
    }
    __dst_alloc_list_push__dmemUi(0, 1);
}
__dst_alloc_size_t __dst_alloc_malloc__dmemUi(__dst_alloc_size_t request) {
    request = request / sizeof(unsigned int);
    if (request > (1 << 10)) return 0;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemUi(request);
    __dst_alloc_bucket_size_t original_bucket = bucket;
    while ((__dst_alloc_bucket_size_t)(bucket + 1) != 0) {
        __dst_alloc_size_t ptr = __dst_alloc_list_pop__dmemUi(bucket);
        if (!ptr) {
            bucket--; continue;
        }
        __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemUi(ptr, bucket);
        if (i != 0) __dst_alloc_flip_parent_split__dmemUi(i);
        while (bucket < original_bucket) {
            i = ((i) * 2 + 1);
            __dst_alloc_clr_parent_split__dmemUi(i);
            __dst_alloc_flip_parent_split__dmemUi(i);
            bucket++;
            __dst_alloc_list_push__dmemUi(bucket, __dst_alloc_index_for_node__dmemUi(((i) + 1), bucket));
        }
        __dmemUi[ptr]._link.prev = request;
        return ptr + 1;
    }
    return 0;
}
void __dst_alloc_free__dmemUi(__dst_alloc_size_t ptr) {
    if (ptr == 0) return;
    ptr -= 1;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemUi(__dmemUi[ptr]._link.prev);
    __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemUi(ptr, bucket);
    while (i != 0) {
        __dst_alloc_flip_parent_split__dmemUi(i);
        if (__dst_alloc_test_parent_split__dmemUi(i)) break;
        __dst_alloc_list_remove__dmemUi(bucket, __dst_alloc_index_for_node__dmemUi(((((i) - 1) ^ 1) + 1), bucket));
        i = (((i) - 1) / 2);
        bucket--;
    }
    __dst_alloc_list_push__dmemUi(bucket, __dst_alloc_index_for_node__dmemUi(i, bucket));
}

struct __dst_alloc_list__dmemc 
{
  struct __dst_alloc_list_base_t _link;
  char _data;
}
;
struct __dst_alloc_list__dmemc __dmemc[1024U];
unsigned int __dst_alloc_malloc__dmemc(unsigned int );
void __dst_alloc_free__dmemc(unsigned int );
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
unsigned char __dst_alloc_node_split__dmemc[(1 << (10 - 1)) / 8];
static unsigned char __dst_alloc_test_parent_split__dmemc(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    return (__dst_alloc_node_split__dmemc[index / 8] >> (index % 8)) & 1;
}
static void __dst_alloc_flip_parent_split__dmemc(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemc[index / 8] ^= 1 << (index % 8);
}
static void __dst_alloc_clr_parent_split__dmemc(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemc[index / 8] &= ~(1 << (index % 8));
}
struct __dst_alloc_list_base_t __dst_alloc_buckets__dmemc[10] = {{1, 1}};
static __dst_alloc_bucket_size_t __dst_alloc_bucket_for_request__dmemc(
        __dst_alloc_size_t request) {
    __dst_alloc_bucket_size_t bucket = 10 - 1;
    __dst_alloc_size_t size = 2;
    while (size < request) {
        size <<= 1;
        bucket -= 1;
    }
    return bucket;
}
static void __dst_alloc_list_push__dmemc(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dst_alloc_buckets__dmemc[bucket].prev;
    __dmemc[entry]._link.prev = prev;
    __dmemc[entry]._link.next = 0;
    if (prev == 0) __dst_alloc_buckets__dmemc[bucket].next = entry;
    else __dmemc[prev]._link.next = entry;
    __dst_alloc_buckets__dmemc[bucket].prev = entry;
}
static void __dst_alloc_list_remove__dmemc(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dmemc[entry]._link.prev;
    __dst_alloc_size_t next = __dmemc[entry]._link.next;
    if (prev == 0) __dst_alloc_buckets__dmemc[bucket].next = next;
    else __dmemc[prev]._link.next = next;
    if (next == 0) __dst_alloc_buckets__dmemc[bucket].prev = prev;
    else __dmemc[next]._link.prev = prev;
}
static __dst_alloc_size_t __dst_alloc_list_pop__dmemc(
        __dst_alloc_bucket_size_t bucket) {
    __dst_alloc_size_t back = __dst_alloc_buckets__dmemc[bucket].prev;
    if (back == 0) return 0;
    __dst_alloc_list_remove__dmemc(bucket, back);
    return back;
}
static __dst_alloc_size_t __dst_alloc_index_for_node__dmemc(
        __dst_alloc_size_t bucket_index,
        __dst_alloc_bucket_size_t bucket) {
    return 1 + ((bucket_index - (1 << bucket) + 1) << (10 - bucket));
}
static __dst_alloc_size_t __dst_alloc_node_for_index__dmemc(
        __dst_alloc_size_t global_index,
        __dst_alloc_bucket_size_t bucket) {
    return ((global_index - 1) >> (10 - bucket)) + (1 << bucket) - 1;
}
void __dst_alloc_init__dmemc() {
    for (int i = 0; i < 10; i++) {
        __dst_alloc_buckets__dmemc[i].prev = 0;
        __dst_alloc_buckets__dmemc[i].next = 0;
    }
    __dst_alloc_list_push__dmemc(0, 1);
}
__dst_alloc_size_t __dst_alloc_malloc__dmemc(__dst_alloc_size_t request) {
    request = request / sizeof(char);
    if (request > (1 << 10)) return 0;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemc(request);
    __dst_alloc_bucket_size_t original_bucket = bucket;
    while ((__dst_alloc_bucket_size_t)(bucket + 1) != 0) {
        __dst_alloc_size_t ptr = __dst_alloc_list_pop__dmemc(bucket);
        if (!ptr) {
            bucket--; continue;
        }
        __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemc(ptr, bucket);
        if (i != 0) __dst_alloc_flip_parent_split__dmemc(i);
        while (bucket < original_bucket) {
            i = ((i) * 2 + 1);
            __dst_alloc_clr_parent_split__dmemc(i);
            __dst_alloc_flip_parent_split__dmemc(i);
            bucket++;
            __dst_alloc_list_push__dmemc(bucket, __dst_alloc_index_for_node__dmemc(((i) + 1), bucket));
        }
        __dmemc[ptr]._link.prev = request;
        return ptr + 1;
    }
    return 0;
}
void __dst_alloc_free__dmemc(__dst_alloc_size_t ptr) {
    if (ptr == 0) return;
    ptr -= 1;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemc(__dmemc[ptr]._link.prev);
    __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemc(ptr, bucket);
    while (i != 0) {
        __dst_alloc_flip_parent_split__dmemc(i);
        if (__dst_alloc_test_parent_split__dmemc(i)) break;
        __dst_alloc_list_remove__dmemc(bucket, __dst_alloc_index_for_node__dmemc(((((i) - 1) ^ 1) + 1), bucket));
        i = (((i) - 1) / 2);
        bucket--;
    }
    __dst_alloc_list_push__dmemc(bucket, __dst_alloc_index_for_node__dmemc(i, bucket));
}
typedef unsigned int __didx__Pb__class_node__Pe__;
// type __didxc was char *
typedef unsigned int __didxc;
// type __didxclass_node was struct ::node{int substring_index;struct node *fail;struct node *next[26];}*
typedef unsigned int __didxclass_node;
#include <cassert>
#include <cstdlib>
/*
 * Trie tree with Aho-Corasick state machine.
 *
 * de la Briandais, René (1959). File searching using variable length keys.
 * Proc. Western J. Computer Conf. pp. 295–298. Cited by Brass.
 *
 * Aho, Alfred V.; Corasick, Margaret J. (June 1975). "Efficient string
 * matching: An aid to bibliographic search". Communications of the ACM.
 * 18 (6): 333–340. doi:10.1145/360825.360855. MR 0371172.
 */

struct node 
{
  int substring_index;
  __didxclass_node fail;
  __didxclass_node next[26];
}
;

struct __dst_alloc_list__dmemclass_node 
{
  struct __dst_alloc_list_base_t _link;
  struct node _data;
}
;
struct __dst_alloc_list__dmemclass_node __dmemclass_node[1024U];
unsigned int __dst_alloc_malloc__dmemclass_node(unsigned int );
void __dst_alloc_free__dmemclass_node(unsigned int );
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
unsigned char __dst_alloc_node_split__dmemclass_node[(1 << (10 - 1)) / 8];
static unsigned char __dst_alloc_test_parent_split__dmemclass_node(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    return (__dst_alloc_node_split__dmemclass_node[index / 8] >> (index % 8)) & 1;
}
static void __dst_alloc_flip_parent_split__dmemclass_node(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemclass_node[index / 8] ^= 1 << (index % 8);
}
static void __dst_alloc_clr_parent_split__dmemclass_node(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemclass_node[index / 8] &= ~(1 << (index % 8));
}
struct __dst_alloc_list_base_t __dst_alloc_buckets__dmemclass_node[10] = {{1, 1}};
static __dst_alloc_bucket_size_t __dst_alloc_bucket_for_request__dmemclass_node(
        __dst_alloc_size_t request) {
    __dst_alloc_bucket_size_t bucket = 10 - 1;
    __dst_alloc_size_t size = 2;
    while (size < request) {
        size <<= 1;
        bucket -= 1;
    }
    return bucket;
}
static void __dst_alloc_list_push__dmemclass_node(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dst_alloc_buckets__dmemclass_node[bucket].prev;
    __dmemclass_node[entry]._link.prev = prev;
    __dmemclass_node[entry]._link.next = 0;
    if (prev == 0) __dst_alloc_buckets__dmemclass_node[bucket].next = entry;
    else __dmemclass_node[prev]._link.next = entry;
    __dst_alloc_buckets__dmemclass_node[bucket].prev = entry;
}
static void __dst_alloc_list_remove__dmemclass_node(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dmemclass_node[entry]._link.prev;
    __dst_alloc_size_t next = __dmemclass_node[entry]._link.next;
    if (prev == 0) __dst_alloc_buckets__dmemclass_node[bucket].next = next;
    else __dmemclass_node[prev]._link.next = next;
    if (next == 0) __dst_alloc_buckets__dmemclass_node[bucket].prev = prev;
    else __dmemclass_node[next]._link.prev = prev;
}
static __dst_alloc_size_t __dst_alloc_list_pop__dmemclass_node(
        __dst_alloc_bucket_size_t bucket) {
    __dst_alloc_size_t back = __dst_alloc_buckets__dmemclass_node[bucket].prev;
    if (back == 0) return 0;
    __dst_alloc_list_remove__dmemclass_node(bucket, back);
    return back;
}
static __dst_alloc_size_t __dst_alloc_index_for_node__dmemclass_node(
        __dst_alloc_size_t bucket_index,
        __dst_alloc_bucket_size_t bucket) {
    return 1 + ((bucket_index - (1 << bucket) + 1) << (10 - bucket));
}
static __dst_alloc_size_t __dst_alloc_node_for_index__dmemclass_node(
        __dst_alloc_size_t global_index,
        __dst_alloc_bucket_size_t bucket) {
    return ((global_index - 1) >> (10 - bucket)) + (1 << bucket) - 1;
}
void __dst_alloc_init__dmemclass_node() {
    for (int i = 0; i < 10; i++) {
        __dst_alloc_buckets__dmemclass_node[i].prev = 0;
        __dst_alloc_buckets__dmemclass_node[i].next = 0;
    }
    __dst_alloc_list_push__dmemclass_node(0, 1);
}
__dst_alloc_size_t __dst_alloc_malloc__dmemclass_node(__dst_alloc_size_t request) {
    request = request / sizeof(struct ::node);
    if (request > (1 << 10)) return 0;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemclass_node(request);
    __dst_alloc_bucket_size_t original_bucket = bucket;
    while ((__dst_alloc_bucket_size_t)(bucket + 1) != 0) {
        __dst_alloc_size_t ptr = __dst_alloc_list_pop__dmemclass_node(bucket);
        if (!ptr) {
            bucket--; continue;
        }
        __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemclass_node(ptr, bucket);
        if (i != 0) __dst_alloc_flip_parent_split__dmemclass_node(i);
        while (bucket < original_bucket) {
            i = ((i) * 2 + 1);
            __dst_alloc_clr_parent_split__dmemclass_node(i);
            __dst_alloc_flip_parent_split__dmemclass_node(i);
            bucket++;
            __dst_alloc_list_push__dmemclass_node(bucket, __dst_alloc_index_for_node__dmemclass_node(((i) + 1), bucket));
        }
        __dmemclass_node[ptr]._link.prev = request;
        return ptr + 1;
    }
    return 0;
}
void __dst_alloc_free__dmemclass_node(__dst_alloc_size_t ptr) {
    if (ptr == 0) return;
    ptr -= 1;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemclass_node(__dmemclass_node[ptr]._link.prev);
    __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemclass_node(ptr, bucket);
    while (i != 0) {
        __dst_alloc_flip_parent_split__dmemclass_node(i);
        if (__dst_alloc_test_parent_split__dmemclass_node(i)) break;
        __dst_alloc_list_remove__dmemclass_node(bucket, __dst_alloc_index_for_node__dmemclass_node(((((i) - 1) ^ 1) + 1), bucket));
        i = (((i) - 1) / 2);
        bucket--;
    }
    __dst_alloc_list_push__dmemclass_node(bucket, __dst_alloc_index_for_node__dmemclass_node(i, bucket));
}
int node_count = 1;
bool g_fallback = false;

__didxclass_node new_node()
{
  __didxclass_node curr = (__didxclass_node )(__dst_alloc_malloc__dmemclass_node(sizeof(struct node )));
  if (!curr) {
    g_fallback = true;
    return 0L;
  }
  (&(__dmemclass_node + curr + 0U - 1U) -> _data) -> substring_index = - 1;
  (&(__dmemclass_node + curr + 0U - 1U) -> _data) -> fail = 0L;
  for (int i = 0; i < 26; i++) {
    (&(__dmemclass_node + curr + 0U - 1U) -> _data) -> next[i] = 0L;
  }
  return curr;
}
/*
 * Insert a new trie node with string as content.
 * The node will be inserted to the trie specified by root.
 *
 * Return: the '%' location of the string.
 */

int insert_node(__didxclass_node root,__didxc str,int substring_index)
{
  char ch =  *(&(__dmemc + str + 0U - 1U) -> _data);
  if (ch == '%') {
    (&(__dmemclass_node + root + 0U - 1U) -> _data) -> substring_index = substring_index;
    return 0;
  }
   else {
    ch >= 'a' && ch <= 'z'?(static_cast < void  >  (0)) : __assert_fail("ch >= 'a' && ch <= 'z'","kernel.cpp",47,__PRETTY_FUNCTION__);
    int idx = ch - 'a';
    if (!(&(__dmemclass_node + root + 0U - 1U) -> _data) -> next[idx]) {
      (&(__dmemclass_node + root + 0U - 1U) -> _data) -> next[idx] = new_node();
      node_count += 1;
    }
    return insert_node((&(__dmemclass_node + root + 0U - 1U) -> _data) -> next[idx],str + 1,substring_index) + 1;
  }
}
/*
 * Build Aho-Corasick state machine.
 */

void build_AhoCorasick(__didxclass_node root,int node_count)
{
  __didx__Pb__class_node__Pe__ queue = (__didx__Pb__class_node__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(struct node *) * node_count));
  if (!queue) {
    g_fallback = true;
    return ;
  }
// initialize queue
  int head = 0;
  int tail = 1;
  (&(__dmemUi + queue + 0 - 1U) -> _data)[0U] = root;
  for (; head < tail; head++) {
    __didxclass_node curr = (&(__dmemUi + queue + head - 1U) -> _data)[0U];
    for (int i = 0; i < 26; i++) {
// non-existent node
      if (!(&(__dmemclass_node + curr + 0U - 1U) -> _data) -> next[i]) 
        continue; 
// Aho-Corasick fail link
      (&(__dmemclass_node + (&(__dmemclass_node + curr + 0U - 1U) -> _data) -> next[i] + 0U - 1U) -> _data) -> fail = root;
      for (__didxclass_node p = (&(__dmemclass_node + curr + 0U - 1U) -> _data) -> fail; p; p = (&(__dmemclass_node + p + 0U - 1U) -> _data) -> fail) {
        if ((&(__dmemclass_node + p + 0U - 1U) -> _data) -> next[i]) {
          (&(__dmemclass_node + (&(__dmemclass_node + curr + 0U - 1U) -> _data) -> next[i] + 0U - 1U) -> _data) -> fail = (&(__dmemclass_node + p + 0U - 1U) -> _data) -> next[i];
          break; 
        }
      }
// add to queue
      (&(__dmemUi + queue + tail++ - 1U) -> _data)[0U] = (&(__dmemclass_node + curr + 0U - 1U) -> _data) -> next[i];
    }
  }
  __dst_alloc_free__dmemUi(queue);
}
/*
 * Query on Aho-Corasick state machine and write matched indexes.
 */

void query_AhoCorasick(__didxclass_node root,char *query,int *substring_indexes,int *query_indexes)
{
  __didxclass_node curr = root;
  for (int offset = 0; ; offset++) {
    char ch = query[offset];
    if (ch == '%') 
      break; 
    ch >= 'a' && ch <= 'z'?(static_cast < void  >  (0)) : __assert_fail("ch >= 'a' && ch <= 'z'","kernel.cpp",102,__PRETTY_FUNCTION__);
    int idx = ch - 'a';
// follow fail link if not matched in curr
    while(!(&(__dmemclass_node + curr + 0U - 1U) -> _data) -> next[idx] && curr != root)
      curr = (&(__dmemclass_node + curr + 0U - 1U) -> _data) -> fail;
// if matched next char
    if ((&(__dmemclass_node + curr + 0U - 1U) -> _data) -> next[idx]) 
      curr = (&(__dmemclass_node + curr + 0U - 1U) -> _data) -> next[idx];
// follow fail link to check matches
    for (__didxclass_node follow = curr; follow != root; follow = (&(__dmemclass_node + follow + 0U - 1U) -> _data) -> fail) {
      if ((&(__dmemclass_node + follow + 0U - 1U) -> _data) -> substring_index != - 1) {
         *(substring_indexes++) = (&(__dmemclass_node + follow + 0U - 1U) -> _data) -> substring_index;
         *(query_indexes++) = offset;
      }
    }
  }
// end indexes
   *substring_indexes = - 1;
   *query_indexes = - 1;
}
/* 
 * Delete the whole tree
 */

void delete_tree(__didxclass_node root)
{
  if (!root) 
    return ;
  for (int i = 0; i < 26; i++) 
    delete_tree((&(__dmemclass_node + root + 0U - 1U) -> _data) -> next[i]);
  __dst_alloc_free__dmemclass_node(root);
}
extern "C" {
/*
 * Implementation of Aho-Corasick Algorithm
 *
 * Search substrings in query, and fill matches in result arrays,
 * Assume all strings contain only letters 'a'-'z'.
 *
 * Parameter Format:
 *   substrings: multiple strings (target substrings) each with '%' ending.
 *               e.g. "string1%string2%", substring_length = 7+1+7+1.
 *   query: a string (the query document) with '%' ending
 *   substring_indexes: an output array, the indexes of found substrings.
 *   query_indexes: an output array, the corresponding indexes in query.
 */

void AhoCorasick_search(int *substring_length_p,char *substrings,char *query,int *substring_indexes,int *query_indexes,int *fallback)
{
  
#pragma HLS INTERFACE m_axi port=substring_length_p offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=substrings offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=query offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=substring_indexes offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=query_indexes offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=fallback offset=slave bundle=gmem
  
#pragma HLS INTERFACE s_axilite port=substring_length_p bundle=control
  
#pragma HLS INTERFACE s_axilite port=substrings bundle=control
  
#pragma HLS INTERFACE s_axilite port=query bundle=control
  
#pragma HLS INTERFACE s_axilite port=substring_indexes bundle=control
  
#pragma HLS INTERFACE s_axilite port=query_indexes bundle=control
  
#pragma HLS INTERFACE s_axilite port=fallback bundle=control
  
#pragma HLS INTERFACE s_axilite port=return bundle=control
  int substring_length =  *substring_length_p;
  __didxclass_node root = new_node();
  __didxc substring_buf = (__didxc )(__dst_alloc_malloc__dmemc(sizeof(char ) * substring_length));
  if (!substring_buf) {
    g_fallback = true;
    goto fail;
  }
  for (int i = 0; i < substring_length; i++) {
    (&(__dmemc + substring_buf + i - 1U) -> _data)[0U] = substrings[i];
  }
  for (int offset = 0; offset < substring_length; ) {
    offset += insert_node(root,substring_buf + offset,offset) + 1;
  }
  build_AhoCorasick(root,node_count);
  query_AhoCorasick(root,query,substring_indexes,query_indexes);
  delete_tree(root);
  fail:
   *fallback = g_fallback;
}
}
