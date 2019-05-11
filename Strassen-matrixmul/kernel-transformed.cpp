
struct __dst_alloc_list_base_t 
{
  unsigned int prev;
  unsigned int next;
}
;
// type __didxtypedef_lldL__typedef_declaration was ::lld*

struct __dst_alloc_list__dmemUi 
{
  struct __dst_alloc_list_base_t _link;
  unsigned int _data;
}
;
struct __dst_alloc_list__dmemUi __dmemUi[1 << ARRAY_LOG];
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
unsigned char __dst_alloc_node_split__dmemUi[(1 << (ARRAY_LOG - 1)) / 8];
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
struct __dst_alloc_list_base_t __dst_alloc_buckets__dmemUi[ARRAY_LOG] = {{1, 1}};
static __dst_alloc_bucket_size_t __dst_alloc_bucket_for_request__dmemUi(
        __dst_alloc_size_t request) {
    __dst_alloc_bucket_size_t bucket = ARRAY_LOG - 1;
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
    return 1 + ((bucket_index - (1 << bucket) + 1) << (ARRAY_LOG - bucket));
}
static __dst_alloc_size_t __dst_alloc_node_for_index__dmemUi(
        __dst_alloc_size_t global_index,
        __dst_alloc_bucket_size_t bucket) {
    return ((global_index - 1) >> (ARRAY_LOG - bucket)) + (1 << bucket) - 1;
}
void __dst_alloc_init__dmemUi() {
    for (int i = 0; i < ARRAY_LOG; i++) {
        __dst_alloc_buckets__dmemUi[i].prev = 0;
        __dst_alloc_buckets__dmemUi[i].next = 0;
    }
    __dst_alloc_list_push__dmemUi(0, 1);
}
__dst_alloc_size_t __dst_alloc_malloc__dmemUi(__dst_alloc_size_t request) {
    request = request / sizeof(unsigned int);
    if (request > (1 << ARRAY_LOG)) return 0;
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
typedef unsigned int __didxtypedef_lldL__typedef_declaration;
// type __didx__Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe__ was ::lld***
typedef unsigned int __didx__Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe__;
// type __didx__Pb____Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe____Pe__ was ::lld****
typedef unsigned int __didx__Pb____Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe____Pe__;
// type __didx__Pb__typedef_lldL__typedef_declaration__Pe__ was ::lld**
typedef unsigned int __didx__Pb__typedef_lldL__typedef_declaration__Pe__;
// CPP program to implement Strassen’s Matrix 
// Multiplication Algorithm 
// from https://www.geeksforgeeks.org/strassens-matrix-multiplication-algorithm-implementation/
#include <cstdlib>
typedef long long lld;

struct __dst_alloc_list__dmemtypedef_lldL__typedef_declaration 
{
  struct __dst_alloc_list_base_t _link;
  lld _data;
}
;
struct __dst_alloc_list__dmemtypedef_lldL__typedef_declaration __dmemtypedef_lldL__typedef_declaration[1 << ARRAY_LOG];
unsigned int __dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(unsigned int );
void __dst_alloc_free__dmemtypedef_lldL__typedef_declaration(unsigned int );
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
unsigned char __dst_alloc_node_split__dmemtypedef_lldL__typedef_declaration[(1 << (ARRAY_LOG - 1)) / 8];
static unsigned char __dst_alloc_test_parent_split__dmemtypedef_lldL__typedef_declaration(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    return (__dst_alloc_node_split__dmemtypedef_lldL__typedef_declaration[index / 8] >> (index % 8)) & 1;
}
static void __dst_alloc_flip_parent_split__dmemtypedef_lldL__typedef_declaration(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemtypedef_lldL__typedef_declaration[index / 8] ^= 1 << (index % 8);
}
static void __dst_alloc_clr_parent_split__dmemtypedef_lldL__typedef_declaration(__dst_alloc_size_t index) {
    index = (index - 1) / 2;
    __dst_alloc_node_split__dmemtypedef_lldL__typedef_declaration[index / 8] &= ~(1 << (index % 8));
}
struct __dst_alloc_list_base_t __dst_alloc_buckets__dmemtypedef_lldL__typedef_declaration[ARRAY_LOG] = {{1, 1}};
static __dst_alloc_bucket_size_t __dst_alloc_bucket_for_request__dmemtypedef_lldL__typedef_declaration(
        __dst_alloc_size_t request) {
    __dst_alloc_bucket_size_t bucket = ARRAY_LOG - 1;
    __dst_alloc_size_t size = 2;
    while (size < request) {
        size <<= 1;
        bucket -= 1;
    }
    return bucket;
}
static void __dst_alloc_list_push__dmemtypedef_lldL__typedef_declaration(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dst_alloc_buckets__dmemtypedef_lldL__typedef_declaration[bucket].prev;
    __dmemtypedef_lldL__typedef_declaration[entry]._link.prev = prev;
    __dmemtypedef_lldL__typedef_declaration[entry]._link.next = 0;
    if (prev == 0) __dst_alloc_buckets__dmemtypedef_lldL__typedef_declaration[bucket].next = entry;
    else __dmemtypedef_lldL__typedef_declaration[prev]._link.next = entry;
    __dst_alloc_buckets__dmemtypedef_lldL__typedef_declaration[bucket].prev = entry;
}
static void __dst_alloc_list_remove__dmemtypedef_lldL__typedef_declaration(
        __dst_alloc_bucket_size_t bucket,
        __dst_alloc_size_t entry) {
    __dst_alloc_size_t prev = __dmemtypedef_lldL__typedef_declaration[entry]._link.prev;
    __dst_alloc_size_t next = __dmemtypedef_lldL__typedef_declaration[entry]._link.next;
    if (prev == 0) __dst_alloc_buckets__dmemtypedef_lldL__typedef_declaration[bucket].next = next;
    else __dmemtypedef_lldL__typedef_declaration[prev]._link.next = next;
    if (next == 0) __dst_alloc_buckets__dmemtypedef_lldL__typedef_declaration[bucket].prev = prev;
    else __dmemtypedef_lldL__typedef_declaration[next]._link.prev = prev;
}
static __dst_alloc_size_t __dst_alloc_list_pop__dmemtypedef_lldL__typedef_declaration(
        __dst_alloc_bucket_size_t bucket) {
    __dst_alloc_size_t back = __dst_alloc_buckets__dmemtypedef_lldL__typedef_declaration[bucket].prev;
    if (back == 0) return 0;
    __dst_alloc_list_remove__dmemtypedef_lldL__typedef_declaration(bucket, back);
    return back;
}
static __dst_alloc_size_t __dst_alloc_index_for_node__dmemtypedef_lldL__typedef_declaration(
        __dst_alloc_size_t bucket_index,
        __dst_alloc_bucket_size_t bucket) {
    return 1 + ((bucket_index - (1 << bucket) + 1) << (ARRAY_LOG - bucket));
}
static __dst_alloc_size_t __dst_alloc_node_for_index__dmemtypedef_lldL__typedef_declaration(
        __dst_alloc_size_t global_index,
        __dst_alloc_bucket_size_t bucket) {
    return ((global_index - 1) >> (ARRAY_LOG - bucket)) + (1 << bucket) - 1;
}
void __dst_alloc_init__dmemtypedef_lldL__typedef_declaration() {
    for (int i = 0; i < ARRAY_LOG; i++) {
        __dst_alloc_buckets__dmemtypedef_lldL__typedef_declaration[i].prev = 0;
        __dst_alloc_buckets__dmemtypedef_lldL__typedef_declaration[i].next = 0;
    }
    __dst_alloc_list_push__dmemtypedef_lldL__typedef_declaration(0, 1);
}
__dst_alloc_size_t __dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(__dst_alloc_size_t request) {
    request = request / sizeof(::lld);
    if (request > (1 << ARRAY_LOG)) return 0;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemtypedef_lldL__typedef_declaration(request);
    __dst_alloc_bucket_size_t original_bucket = bucket;
    while ((__dst_alloc_bucket_size_t)(bucket + 1) != 0) {
        __dst_alloc_size_t ptr = __dst_alloc_list_pop__dmemtypedef_lldL__typedef_declaration(bucket);
        if (!ptr) {
            bucket--; continue;
        }
        __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemtypedef_lldL__typedef_declaration(ptr, bucket);
        if (i != 0) __dst_alloc_flip_parent_split__dmemtypedef_lldL__typedef_declaration(i);
        while (bucket < original_bucket) {
            i = ((i) * 2 + 1);
            __dst_alloc_clr_parent_split__dmemtypedef_lldL__typedef_declaration(i);
            __dst_alloc_flip_parent_split__dmemtypedef_lldL__typedef_declaration(i);
            bucket++;
            __dst_alloc_list_push__dmemtypedef_lldL__typedef_declaration(bucket, __dst_alloc_index_for_node__dmemtypedef_lldL__typedef_declaration(((i) + 1), bucket));
        }
        __dmemtypedef_lldL__typedef_declaration[ptr]._link.prev = request;
        return ptr + 1;
    }
    return 0;
}
void __dst_alloc_free__dmemtypedef_lldL__typedef_declaration(__dst_alloc_size_t ptr) {
    if (ptr == 0) return;
    ptr -= 1;
    __dst_alloc_bucket_size_t bucket =
        __dst_alloc_bucket_for_request__dmemtypedef_lldL__typedef_declaration(__dmemtypedef_lldL__typedef_declaration[ptr]._link.prev);
    __dst_alloc_size_t i = __dst_alloc_node_for_index__dmemtypedef_lldL__typedef_declaration(ptr, bucket);
    while (i != 0) {
        __dst_alloc_flip_parent_split__dmemtypedef_lldL__typedef_declaration(i);
        if (__dst_alloc_test_parent_split__dmemtypedef_lldL__typedef_declaration(i)) break;
        __dst_alloc_list_remove__dmemtypedef_lldL__typedef_declaration(bucket, __dst_alloc_index_for_node__dmemtypedef_lldL__typedef_declaration(((((i) - 1) ^ 1) + 1), bucket));
        i = (((i) - 1) / 2);
        bucket--;
    }
    __dst_alloc_list_push__dmemtypedef_lldL__typedef_declaration(bucket, __dst_alloc_index_for_node__dmemtypedef_lldL__typedef_declaration(i, bucket));
}
bool g_fallback = false;
__didx__Pb__typedef_lldL__typedef_declaration__Pe__ Strassen(__didx__Pb__typedef_lldL__typedef_declaration__Pe__ a,__didx__Pb__typedef_lldL__typedef_declaration__Pe__ b,int n,int l,int m);
extern "C" {

void process_top(int n,int l,int m,lld *mat1,lld *mat2,lld *mat3,bool *fallback)
{
  
#pragma HLS INTERFACE m_axi port=mat1 offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=mat2 offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=mat3 offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=fallback offset=slave bundle=gmem
  
#pragma HLS INTERFACE s_axilite port=n bundle=control
  
#pragma HLS INTERFACE s_axilite port=l bundle=control
  
#pragma HLS INTERFACE s_axilite port=m bundle=control
  
#pragma HLS INTERFACE s_axilite port=mat1 bundle=control
  
#pragma HLS INTERFACE s_axilite port=mat2 bundle=control
  
#pragma HLS INTERFACE s_axilite port=mat3 bundle=control
  
#pragma HLS INTERFACE s_axilite port=fallback bundle=control
  
#pragma HLS INTERFACE s_axilite port=return bundle=control
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ matA = (__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * n));
  if (!matA) {
     *fallback = true;
    return ;
  }
  for (int i = 0; i < n; i++) {
    (&(__dmemUi + matA + i - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * l)));
    if (!(&(__dmemUi + matA + i - 1U) -> _data)[0U]) {
       *fallback = true;
      return ;
    }
    for (int j = 0; j < l; j++) 
      (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + matA + i - 1U) -> _data)[0U] + j - 1U) -> _data)[0U] = mat1[i * l + j];
  }
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ matB = (__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * l));
  for (int i = 0; i < l; i++) {
    (&(__dmemUi + matB + i - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * m)));
    if (!(&(__dmemUi + matB + i - 1U) -> _data)[0U]) {
       *fallback = true;
      return ;
    }
    for (int j = 0; j < m; j++) 
      (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + matB + i - 1U) -> _data)[0U] + j - 1U) -> _data)[0U] = mat2[i * m + j];
  }
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ matC = Strassen(matA,matB,n,l,m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      mat3[i * m + j] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + matC + i - 1U) -> _data)[0U] + j - 1U) -> _data)[0U];
    }
    __dst_alloc_free__dmemtypedef_lldL__typedef_declaration((&(__dmemUi + matC + i - 1U) -> _data)[0U]);
  }
  __dst_alloc_free__dmemUi(matC);
  *fallback = g_fallback;
}
}
// Strassen's Algorithm for matrix multiplication 
// Complexity: O(n^2.808)

__didx__Pb__typedef_lldL__typedef_declaration__Pe__ MatrixMultiply(__didx__Pb__typedef_lldL__typedef_declaration__Pe__ a,__didx__Pb__typedef_lldL__typedef_declaration__Pe__ b,int n,int l,int m)
{
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ c = (__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * n));
  if (!c) {
    g_fallback = true;
    return 0L;
  }
  for (int i = 0; i < n; i++) 
    (&(__dmemUi + c + i - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * m)));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + c + i - 1U) -> _data)[0U] + j - 1U) -> _data)[0U] = 0;
      for (int k = 0; k < l; k++) {
        (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + c + i - 1U) -> _data)[0U] + j - 1U) -> _data)[0U] += (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + a + i - 1U) -> _data)[0U] + k - 1U) -> _data)[0U] * (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + b + k - 1U) -> _data)[0U] + j - 1U) -> _data)[0U];
      }
    }
  }
  return c;
}

struct __rect_packed_type_L981R__L982R 
{
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ local0;
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ local1;
  int local2;
  int local3;
  int local4;
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ local5;
  int local6;
  int local7;
  int local8;
  int local9;
  __didx__Pb____Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe____Pe__ local10;
  int local11;
  int local12;
  int local13;
  int local14;
  int local15;
  int local16;
  __didx__Pb____Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe____Pe__ local17;
  int local18;
  int local19;
  int local20;
  int local21;
  int local22;
  int local23;
  __didx__Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe__ local24;
  int local25;
  int local26;
  int local27;
  int local28;
  int local29;
  int local30;
  int local31;
  int local32;
  int local33;
  int local34;
  int local35;
  int local36;
  int local37;
  int local38;
  int local39;
  int local40;
  int local41;
  int local42;
  int local43;
  int local44;
  int local45;
  __didx__Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe__ local46;
  int local47;
  int local48;
  int local49;
  int local50;
  int local51;
  int local52;
  int local53;
  int local54;
  int local55;
  int local56;
  int local57;
  int local58;
  int local59;
  unsigned int _location;
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ _return;
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ _ret0;
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ _ret1;
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ _ret2;
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ _ret3;
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ _ret4;
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ _ret5;
  __didx__Pb__typedef_lldL__typedef_declaration__Pe__ _ret6;
}
;

__didx__Pb__typedef_lldL__typedef_declaration__Pe__ Strassen(__didx__Pb__typedef_lldL__typedef_declaration__Pe__ a,__didx__Pb__typedef_lldL__typedef_declaration__Pe__ b,int n,int l,int m)
{
  struct __rect_packed_type_L981R__L982R __rect_packed_var_L981R__L982R[1 << ARRAY_LOG];
  unsigned int __rect_packed_top_L981R__L982R = 0U;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local0 = a;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local1 = b;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 = n;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3 = l;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4 = m;
  ++__rect_packed_top_L981R__L982R;
  __rect_func_L0_L981R__L982R:
  if (0U == __rect_packed_top_L981R__L982R) 
    return __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return;
  --__rect_packed_top_L981R__L982R;
  if (1U == __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location) 
    goto __rect_func_L1_L981R__L982R;
  if (2U == __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location) 
    goto __rect_func_L2_L981R__L982R;
  if (3U == __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location) 
    goto __rect_func_L3_L981R__L982R;
  if (4U == __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location) 
    goto __rect_func_L4_L981R__L982R;
  if (5U == __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location) 
    goto __rect_func_L5_L981R__L982R;
  if (6U == __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location) 
    goto __rect_func_L6_L981R__L982R;
  if (7U == __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location) 
    goto __rect_func_L7_L981R__L982R;
  if (8U == __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location) 
    goto __rect_func_L8_L981R__L982R;
  __rect_func_L1_L981R__L982R:
  if (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 == 1 || __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3 == 1 || __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4 == 1) {
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = MatrixMultiply(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local0,__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local1,__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2,__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3,__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4);
    goto __rect_func_L0_L981R__L982R;
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5 = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2)));
  if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5) {
    g_fallback = true;
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
    goto __rect_func_L0_L981R__L982R;
  }
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local6 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local6 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local6++) {
    (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local6 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4)));
    if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local6 - 1U) -> _data)[0U]) {
      g_fallback = true;
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
      goto __rect_func_L0_L981R__L982R;
    }
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7 = (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 >> 1) + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 & 1);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8 = (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3 >> 1) + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3 & 1);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9 = (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4 >> 1) + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4 & 1);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 = ((__didx__Pb____Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe____Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld ***) * 2)));
  if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10) {
    g_fallback = true;
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
    goto __rect_func_L0_L981R__L982R;
  }
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11++) {
    (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 - 1U) -> _data)[0U] = ((__didx__Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld **) * 2)));
    if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 - 1U) -> _data)[0U]) {
      g_fallback = true;
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
      goto __rect_func_L0_L981R__L982R;
    }
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12++) {
      (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13++) {
        (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!(&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local14 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local14 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local14++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local15 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13 + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 & 1) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local16 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local14 + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 & 1) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local14 - 1U) -> _data)[0U] = (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local15 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 && __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local16 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3?(&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local0 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local15 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local16 - 1U) -> _data)[0U] : 0);
        }
      }
    }
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 = ((__didx__Pb____Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe____Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld ***) * 2)));
  if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17) {
    g_fallback = true;
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
    goto __rect_func_L0_L981R__L982R;
  }
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18++) {
    (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 - 1U) -> _data)[0U] = ((__didx__Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld **) * 2)));
    if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 - 1U) -> _data)[0U]) {
      g_fallback = true;
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
      goto __rect_func_L0_L981R__L982R;
    }
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19++) {
      (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20++) {
        (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!(&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local21 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local21 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local21++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local22 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20 + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 & 1) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local23 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local21 + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 & 1) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local21 - 1U) -> _data)[0U] = (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local22 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3 && __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local23 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4?(&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local1 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local22 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local23 - 1U) -> _data)[0U] : 0);
        }
      }
    }
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 = ((__didx__Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld **) * 10)));
  if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24) {
    g_fallback = true;
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
    goto __rect_func_L0_L981R__L982R;
  }
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 < 10; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25++) {
    switch(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25){
      case 0:
      (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
      if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26++) {
        (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27++) {
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 0 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27 - 1U) -> _data)[0U] - (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 1 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27 - 1U) -> _data)[0U];
        }
      }
      break; 
      case 1:
      (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28++) {
        (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29++) {
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 0 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 0 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29 - 1U) -> _data)[0U];
        }
      }
      break; 
      case 2:
      (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30++) {
        (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31++) {
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 1 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 1 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31 - 1U) -> _data)[0U];
        }
      }
      break; 
      case 3:
      (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
      if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32++) {
        (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33++) {
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 1 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33 - 1U) -> _data)[0U] - (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 0 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33 - 1U) -> _data)[0U];
        }
      }
      break; 
      case 4:
      (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34++) {
        (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35++) {
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 0 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 1 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35 - 1U) -> _data)[0U];
        }
      }
      break; 
      case 5:
      (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
      if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36++) {
        (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37++) {
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 0 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 1 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37 - 1U) -> _data)[0U];
        }
      }
      break; 
      case 6:
      (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38++) {
        (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39++) {
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 0 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39 - 1U) -> _data)[0U] - (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 1 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39 - 1U) -> _data)[0U];
        }
      }
      break; 
      case 7:
      (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
      if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40++) {
        (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41++) {
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 1 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 1 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41 - 1U) -> _data)[0U];
        }
      }
      break; 
      case 8:
      (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42++) {
        (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43++) {
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 0 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43 - 1U) -> _data)[0U] - (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 1 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43 - 1U) -> _data)[0U];
        }
      }
      break; 
      case 9:
      (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] = ((__didx__Pb__typedef_lldL__typedef_declaration__Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
      if (!(&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44++) {
        (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44 - 1U) -> _data)[0U] = ((__didxtypedef_lldL__typedef_declaration )(__dst_alloc_malloc__dmemtypedef_lldL__typedef_declaration(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!(&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44 - 1U) -> _data)[0U]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45++) {
          (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 0 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 0 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45 - 1U) -> _data)[0U];
        }
      }
      break; 
    }
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 = ((__didx__Pb____Pb__typedef_lldL__typedef_declaration__Pe____Pe__ )(__dst_alloc_malloc__dmemUi(sizeof(lld **) * 7)));
  if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46) {
    g_fallback = true;
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
    goto __rect_func_L0_L981R__L982R;
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 2U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + 0 - 1U) -> _data)[0U];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 0 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1 << ARRAY_LOG) 
    g_fallback = true;
  0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L2_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret0 = __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return;
  (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 0 - 1U) -> _data)[0U] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 3U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 1 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + 1 - 1U) -> _data)[0U];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1 << ARRAY_LOG) 
    g_fallback = true;
  0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L3_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret1 = __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return;
  (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 1 - 1U) -> _data)[0U] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret1;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 4U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + 0 - 1U) -> _data)[0U] + 0 - 1U) -> _data)[0U];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + 2 - 1U) -> _data)[0U];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1 << ARRAY_LOG) 
    g_fallback = true;
  0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L4_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret2 = __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return;
  (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 2 - 1U) -> _data)[0U] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret2;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 5U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + 3 - 1U) -> _data)[0U];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + 1 - 1U) -> _data)[0U] + 1 - 1U) -> _data)[0U];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1 << ARRAY_LOG) 
    g_fallback = true;
  0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L5_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret3 = __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return;
  (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 3 - 1U) -> _data)[0U] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret3;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 6U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + 5 - 1U) -> _data)[0U];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + 4 - 1U) -> _data)[0U];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1 << ARRAY_LOG) 
    g_fallback = true;
  0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L6_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret4 = __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return;
  (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 4 - 1U) -> _data)[0U] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret4;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 7U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + 7 - 1U) -> _data)[0U];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + 6 - 1U) -> _data)[0U];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1 << ARRAY_LOG) 
    g_fallback = true;
  0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L7_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret5 = __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return;
  (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 5 - 1U) -> _data)[0U] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret5;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 8U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + 9 - 1U) -> _data)[0U];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + 8 - 1U) -> _data)[0U];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1 << ARRAY_LOG) 
    g_fallback = true;
  0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L8_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret6 = __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return;
  (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 6 - 1U) -> _data)[0U] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _ret6;
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47++) {
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48++) {
      (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 4 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 3 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U] - (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 5 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U];
      if (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4) 
        (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9) - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 1 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U];
      if (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2) 
        (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5 + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7) - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 2 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 3 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U];
      if (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 && __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4) 
        (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5 + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7) - 1U) -> _data)[0U] + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9) - 1U) -> _data)[0U] = (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 4 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U] + (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 0 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U] - (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 2 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U] - (&(__dmemtypedef_lldL__typedef_declaration + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + 6 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 - 1U) -> _data)[0U];
    }
  }
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49++) {
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local50 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local50 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local50++) {
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local51 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local51 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local51++) {
        __dst_alloc_free__dmemtypedef_lldL__typedef_declaration((&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local50 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local51 - 1U) -> _data)[0U]);
      }
      __dst_alloc_free__dmemUi((&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local50 - 1U) -> _data)[0U]);
    }
    __dst_alloc_free__dmemUi((&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49 - 1U) -> _data)[0U]);
  }
  __dst_alloc_free__dmemUi(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10);
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52++) {
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local53 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local53 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local53++) {
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local54 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local54 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local54++) {
        __dst_alloc_free__dmemtypedef_lldL__typedef_declaration((&(__dmemUi + (&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local53 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local54 - 1U) -> _data)[0U]);
      }
      __dst_alloc_free__dmemUi((&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local53 - 1U) -> _data)[0U]);
    }
    __dst_alloc_free__dmemUi((&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52 - 1U) -> _data)[0U]);
  }
  __dst_alloc_free__dmemUi(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17);
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55 < 10; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55++) {
    switch(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55){
      case 0:
      ;
      case 3:
      ;
      case 5:
      ;
      case 7:
      ;
      case 9:
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local56 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local56 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local56++) {
        __dst_alloc_free__dmemtypedef_lldL__typedef_declaration((&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local56 - 1U) -> _data)[0U]);
      }
      break; 
      case 1:
      ;
      case 2:
      ;
      case 4:
      ;
      case 6:
      ;
      case 8:
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local57 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local57 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local57++) {
        __dst_alloc_free__dmemtypedef_lldL__typedef_declaration((&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local57 - 1U) -> _data)[0U]);
      }
      break; 
    }
    __dst_alloc_free__dmemUi((&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55 - 1U) -> _data)[0U]);
  }
  __dst_alloc_free__dmemUi(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24);
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local58 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local58 < 7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local58++) {
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local59 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local59 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 >> 1; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local59++) {
      __dst_alloc_free__dmemtypedef_lldL__typedef_declaration((&(__dmemUi + (&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local58 - 1U) -> _data)[0U] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local59 - 1U) -> _data)[0U]);
    }
    __dst_alloc_free__dmemUi((&(__dmemUi + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local58 - 1U) -> _data)[0U]);
  }
  __dst_alloc_free__dmemUi(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5;
  goto __rect_func_L0_L981R__L982R;
  goto __rect_func_L0_L981R__L982R;
}
