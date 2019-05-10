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
  struct node *fail;
  struct node *next[26];
}
;

struct node *new_node()
{
  struct node *curr = (struct node *)(malloc(sizeof(struct node )));
  curr -> substring_index = - 1;
  curr -> fail = 0L;
  for (int i = 0; i < 26; i++) {
    curr -> next[i] = 0L;
  }
  return curr;
}
int node_count = 1;
/*
 * Insert a new trie node with string as content.
 * The node will be inserted to the trie specified by root.
 *
 * Return: the '%' location of the string.
 */

struct __rect_packed_type_L988R__L989R 
{
  struct node *local0;
  char *local1;
  int local2;
  char local3;
  int local4;
  unsigned int _location;
  int _return;
}
;

int insert_node(struct node *root,char *str,int substring_index)
{
  struct __rect_packed_type_L988R__L989R __rect_packed_var_L988R__L989R[1024U];
  unsigned int __rect_packed_top_L988R__L989R = 0U;
  __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . _location = 1U;
  __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local0 = root;
  __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local1 = str;
  __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local2 = substring_index;
  ++__rect_packed_top_L988R__L989R;
  __rect_func_L0_L988R__L989R:
  if (0U == __rect_packed_top_L988R__L989R) 
    return __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . _return;
  --__rect_packed_top_L988R__L989R;
  if (1U == __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . _location) 
    goto __rect_func_L1_L988R__L989R;
  if (2U == __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . _location) 
    goto __rect_func_L2_L988R__L989R;
  __rect_func_L1_L988R__L989R:
  __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local3 =  *__rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local1;
  if (__rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local3 == '%') {
    __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local0 -> substring_index = __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local2;
    __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . _return = 0;
    goto __rect_func_L0_L988R__L989R;
  }
   else {
    __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local3 >= 'a' && __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local3 <= 'z'?(static_cast < void  >  (0)) : __assert_fail("ch >= 'a' && ch <= 'z'","kernel.cpp",45,__PRETTY_FUNCTION__);
    __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local4 = __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local3 - 'a';
    if (!__rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local0 -> next[__rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local4]) {
      __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local0 -> next[__rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local4] = new_node();
      node_count += 1;
    }
    __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . _location = 2U;
    __rect_packed_var_L988R__L989R[1 + __rect_packed_top_L988R__L989R] . local2 = __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local2;
    __rect_packed_var_L988R__L989R[1 + __rect_packed_top_L988R__L989R] . local1 = __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local1 + 1;
    __rect_packed_var_L988R__L989R[1 + __rect_packed_top_L988R__L989R] . local0 = __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local0 -> next[__rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . local4];
    ++__rect_packed_top_L988R__L989R;
    __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . _location = 1U;
    goto __rect_func_L1_L988R__L989R;
    __rect_func_L2_L988R__L989R:
    int __rect_ret0_L988R__L989R = __rect_packed_var_L988R__L989R[1 + __rect_packed_top_L988R__L989R] . _return;
    __rect_packed_var_L988R__L989R[0 + __rect_packed_top_L988R__L989R] . _return = __rect_ret0_L988R__L989R + 1;
    goto __rect_func_L0_L988R__L989R;
  }
  goto __rect_func_L0_L988R__L989R;
}
/*
 * Build Aho-Corasick state machine.
 */

void build_AhoCorasick(struct node *root,int node_count)
{
  struct node **queue = (struct node **)(malloc(sizeof(struct node *) * node_count));
// initialize queue
  int head = 0;
  int tail = 1;
  queue[0] = root;
  for (; head < tail; head++) {
    struct node *curr = queue[head];
    for (int i = 0; i < 26; i++) {
// non-existent node
      if (!curr -> next[i]) 
        continue; 
// Aho-Corasick fail link
      curr -> next[i] -> fail = root;
      for (struct node *p = curr -> fail; p; p = p -> fail) {
        if (p -> next[i]) {
          curr -> next[i] -> fail = p -> next[i];
          break; 
        }
      }
// add to queue
      queue[tail++] = curr -> next[i];
    }
  }
  free(queue);
}
/*
 * Query on Aho-Corasick state machine and write matched indexes.
 */

void query_AhoCorasick(struct node *root,char *query,int *substring_indexes,int *query_indexes)
{
  struct node *curr = root;
  for (int offset = 0; ; offset++) {
    char ch = query[offset];
    if (ch == '%') 
      break; 
    ch >= 'a' && ch <= 'z'?(static_cast < void  >  (0)) : __assert_fail("ch >= 'a' && ch <= 'z'","kernel.cpp",99,__PRETTY_FUNCTION__);
    int idx = ch - 'a';
// follow fail link if not matched in curr
    while(!curr -> next[idx] && curr != root)
      curr = curr -> fail;
// if matched next char
    if (curr -> next[idx]) 
      curr = curr -> next[idx];
// follow fail link to check matches
    for (struct node *follow = curr; follow != root; follow = follow -> fail) {
      if (follow -> substring_index != - 1) {
         *(substring_indexes++) = follow -> substring_index;
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

struct __rect_packed_type_L994R__L995R 
{
  struct node *local0;
  int local1;
  unsigned int _location;
}
;

void delete_tree(struct node *root)
{
  struct __rect_packed_type_L994R__L995R __rect_packed_var_L994R__L995R[1024U];
  unsigned int __rect_packed_top_L994R__L995R = 0U;
  __rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . _location = 1U;
  __rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . local0 = root;
  ++__rect_packed_top_L994R__L995R;
  __rect_func_L0_L994R__L995R:
  if (0U == __rect_packed_top_L994R__L995R) 
    return ;
  --__rect_packed_top_L994R__L995R;
  if (1U == __rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . _location) 
    goto __rect_func_L1_L994R__L995R;
  if (2U == __rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . _location) 
    goto __rect_func_L2_L994R__L995R;
  __rect_func_L1_L994R__L995R:
  if (!__rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . local0) {
    goto __rect_func_L0_L994R__L995R;
  }
  for (__rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . local1 = 0; __rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . local1 < 26; __rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . local1++) {
    __rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . _location = 2U;
    __rect_packed_var_L994R__L995R[1 + __rect_packed_top_L994R__L995R] . local0 = __rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . local0 -> next[__rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . local1];
    ++__rect_packed_top_L994R__L995R;
    __rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . _location = 1U;
    goto __rect_func_L1_L994R__L995R;
    __rect_func_L2_L994R__L995R:
    0;
  }
  free(__rect_packed_var_L994R__L995R[0 + __rect_packed_top_L994R__L995R] . local0);
  goto __rect_func_L0_L994R__L995R;
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

void AhoCorasick_search(int substring_length,char *substrings,char *query,int *substring_indexes,int *query_indexes)
{
  
#pragma HLS INTERFACE m_axi port=substrings offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=query offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=substring_indexes offset=slave bundle=gmem
  
#pragma HLS INTERFACE m_axi port=query_indexes offset=slave bundle=gmem
  
#pragma HLS INTERFACE s_axilite port=substring_length bundle=control
  
#pragma HLS INTERFACE s_axilite port=substrings bundle=control
  
#pragma HLS INTERFACE s_axilite port=query bundle=control
  
#pragma HLS INTERFACE s_axilite port=substring_indexes bundle=control
  
#pragma HLS INTERFACE s_axilite port=query_indexes bundle=control
  
#pragma HLS INTERFACE s_axilite port=return bundle=control
  char *substring_buf = (char *)(malloc(sizeof(char ) * substring_length));
  for (int i = 0; i < substring_length; i++) {
    substring_buf[i] = substrings[i];
  }
  struct node *root = new_node();
  for (int offset = 0; offset < substring_length; ) {
    offset += insert_node(root,substring_buf + offset,offset) + 1;
  }
  build_AhoCorasick(root,node_count);
  query_AhoCorasick(root,query,substring_indexes,query_indexes);
  delete_tree(root);
}
}
