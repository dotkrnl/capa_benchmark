// CPP program to implement Strassen’s Matrix 
// Multiplication Algorithm 
// from https://www.geeksforgeeks.org/strassens-matrix-multiplication-algorithm-implementation/
#include <cstdlib>
typedef long long lld;
bool g_fallback = false;
lld **Strassen(lld **a,lld **b,int n,int l,int m);
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
  lld **matA = (lld **)(malloc(sizeof(lld *) * n));
  if (!matA) {
     *fallback = true;
    return ;
  }
  for (int i = 0; i < n; i++) {
    matA[i] = ((lld *)(malloc(sizeof(lld ) * l)));
    if (!matA[i]) {
       *fallback = true;
      return ;
    }
    for (int j = 0; j < l; j++) 
      matA[i][j] = mat1[i * l + j];
  }
  lld **matB = (lld **)(malloc(sizeof(lld *) * l));
  for (int i = 0; i < l; i++) {
    matB[i] = ((lld *)(malloc(sizeof(lld ) * m)));
    if (!matB[i]) {
       *fallback = true;
      return ;
    }
    for (int j = 0; j < m; j++) 
      matB[i][j] = mat2[i * m + j];
  }
  lld **matC = Strassen(matA,matB,n,l,m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      mat3[i * m + j] = matC[i][j];
    }
    free(matC[i]);
  }
  free(matC);
  *fallback = g_fallback;
}
}
// Strassen's Algorithm for matrix multiplication 
// Complexity: O(n^2.808)

lld **MatrixMultiply(lld **a,lld **b,int n,int l,int m)
{
  lld **c = (lld **)(malloc(sizeof(lld *) * n));
  if (!c) {
    g_fallback = true;
    return 0L;
  }
  for (int i = 0; i < n; i++) 
    c[i] = ((lld *)(malloc(sizeof(lld ) * m)));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      c[i][j] = 0;
      for (int k = 0; k < l; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return c;
}

struct __rect_packed_type_L981R__L982R 
{
  lld **local0;
  lld **local1;
  int local2;
  int local3;
  int local4;
  lld **local5;
  int local6;
  int local7;
  int local8;
  int local9;
  lld ****local10;
  int local11;
  int local12;
  int local13;
  int local14;
  int local15;
  int local16;
  lld ****local17;
  int local18;
  int local19;
  int local20;
  int local21;
  int local22;
  int local23;
  lld ***local24;
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
  lld ***local46;
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
  lld **_return;
  lld **_ret0;
  lld **_ret1;
  lld **_ret2;
  lld **_ret3;
  lld **_ret4;
  lld **_ret5;
  lld **_ret6;
}
;

lld **Strassen(lld **a,lld **b,int n,int l,int m)
{
  struct __rect_packed_type_L981R__L982R __rect_packed_var_L981R__L982R[1024U];
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
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5 = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2)));
  if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5) {
    g_fallback = true;
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
    goto __rect_func_L0_L981R__L982R;
  }
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local6 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local6 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local6++) {
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local6] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4)));
    if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local6]) {
      g_fallback = true;
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
      goto __rect_func_L0_L981R__L982R;
    }
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7 = (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 >> 1) + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 & 1);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8 = (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3 >> 1) + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3 & 1);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9 = (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4 >> 1) + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4 & 1);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10 = ((lld ****)(malloc(sizeof(lld ***) * 2)));
  if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10) {
    g_fallback = true;
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
    goto __rect_func_L0_L981R__L982R;
  }
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11++) {
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11] = ((lld ***)(malloc(sizeof(lld **) * 2)));
    if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11]) {
      g_fallback = true;
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
      goto __rect_func_L0_L981R__L982R;
    }
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12++) {
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local14 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local14 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local14++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local15 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13 + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11 & 1) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local16 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local14 + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12 & 1) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local11][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local12][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local13][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local14] = (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local15 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 && __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local16 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3?__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local0[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local15][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local16] : 0);
        }
      }
    }
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17 = ((lld ****)(malloc(sizeof(lld ***) * 2)));
  if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17) {
    g_fallback = true;
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
    goto __rect_func_L0_L981R__L982R;
  }
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18++) {
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18] = ((lld ***)(malloc(sizeof(lld **) * 2)));
    if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18]) {
      g_fallback = true;
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
      goto __rect_func_L0_L981R__L982R;
    }
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19++) {
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local21 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local21 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local21++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local22 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20 + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18 & 1) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local23 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local21 + (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19 & 1) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local18][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local19][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local20][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local21] = (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local22 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local3 && __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local23 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4?__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local1[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local22][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local23] : 0);
        }
      }
    }
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24 = ((lld ***)(malloc(sizeof(lld **) * 10)));
  if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24) {
    g_fallback = true;
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
    goto __rect_func_L0_L981R__L982R;
  }
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25 < 10; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25++) {
    switch(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25){
      case 0:
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[0][1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27] - __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[1][1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local26][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local27];
        }
      }
      break; 
      case 1:
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[0][0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[0][1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local28][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local29];
        }
      }
      break; 
      case 2:
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[1][0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[1][1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local30][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local31];
        }
      }
      break; 
      case 3:
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[1][0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33] - __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[0][0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local32][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local33];
        }
      }
      break; 
      case 4:
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[0][0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[1][1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local34][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local35];
        }
      }
      break; 
      case 5:
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[0][0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[1][1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local36][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local37];
        }
      }
      break; 
      case 6:
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[0][1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39] - __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[1][1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local38][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local39];
        }
      }
      break; 
      case 7:
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[1][0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[1][1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local40][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local41];
        }
      }
      break; 
      case 8:
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[0][0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43] - __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[1][0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local42][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local43];
        }
      }
      break; 
      case 9:
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25] = ((lld **)(malloc(sizeof(lld *) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8)));
      if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25]) {
        g_fallback = true;
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
        goto __rect_func_L0_L981R__L982R;
      }
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44++) {
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44] = ((lld *)(malloc(sizeof(lld ) * __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9)));
        if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44]) {
          g_fallback = true;
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
          goto __rect_func_L0_L981R__L982R;
        }
        for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45++) {
          __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local25][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[0][0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[0][1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local44][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local45];
        }
      }
      break; 
    }
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46 = ((lld ***)(malloc(sizeof(lld **) * 7)));
  if (!__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46) {
    g_fallback = true;
    __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = 0L;
    goto __rect_func_L0_L981R__L982R;
  }
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 2U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[0];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[0][0];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1024U) 
g_fallback = true;
    0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L2_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret0 = (__rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[0] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 3U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[1][1];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[1];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1024U) 
g_fallback = true;
    0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L3_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret1 = (__rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[1] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret1;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 4U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[0][0];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[2];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1024U) 
g_fallback = true;
    0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L4_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret2 = (__rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[2] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret2;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 5U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[3];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[1][1];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1024U) 
g_fallback = true;
    0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L5_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret3 = (__rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[3] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret3;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 6U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[5];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[4];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1024U) 
g_fallback = true;
    0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L6_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret4 = (__rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[4] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret4;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 7U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[7];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[6];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1024U) 
g_fallback = true;
    0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L7_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret5 = (__rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[5] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret5;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 8U;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local4 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local3 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local2 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7;
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local1 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[9];
  __rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . local0 = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[8];
  ++__rect_packed_top_L981R__L982R;
  if (__rect_packed_top_L981R__L982R == 1024U) 
g_fallback = true;
    0;
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _location = 1U;
  goto __rect_func_L1_L981R__L982R;
  __rect_func_L8_L981R__L982R:
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret6 = (__rect_packed_var_L981R__L982R[1 + __rect_packed_top_L981R__L982R] . _return);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[6] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . __rect_packed_type_L981R__L982R::_ret6;
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47++) {
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48++) {
      __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[4][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[3][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48] - __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[5][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48];
      if (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4) 
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[1][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48];
      if (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2) 
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[2][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[3][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48];
      if (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 && __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local4) 
        __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48 + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local9] = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[4][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48] + __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[0][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48] - __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[2][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48] - __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[6][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local47][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local48];
    }
  }
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49++) {
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local50 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local50 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local50++) {
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local51 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local51 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local51++) {
        free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local50][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local51]);
      }
      free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local50]);
    }
    free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local49]);
  }
  free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local10);
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52++) {
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local53 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local53 < 2; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local53++) {
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local54 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local54 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local54++) {
        free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local53][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local54]);
      }
      free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local53]);
    }
    free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local52]);
  }
  free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local17);
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55 < 10; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55++) {
    switch(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55){
      case 0:;
      case 3:;
      case 5:;
      case 7:;
      case 9:
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local56 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local56 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local8; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local56++) {
        free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local56]);
      }
      break; 
      case 1:;
      case 2:;
      case 4:;
      case 6:;
      case 8:
      for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local57 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local57 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local57++) {
        free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local57]);
      }
      break; 
    }
    free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local55]);
  }
  free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local24);
  for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local58 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local58 < 7; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local58++) {
    for (__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local59 = 0; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local59 < __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local2 >> 1; __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local59++) {
      free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local58][__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local59]);
    }
    free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46[__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local58]);
  }
  free(__rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local46);
  __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . _return = __rect_packed_var_L981R__L982R[0 + __rect_packed_top_L981R__L982R] . local5;
  goto __rect_func_L0_L981R__L982R;
  goto __rect_func_L0_L981R__L982R;
}
