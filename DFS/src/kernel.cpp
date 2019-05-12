#include <stdlib.h>
#include <stdio.h>

struct btnode
{
    int value;
    struct btnode *left, *right;
};
typedef struct btnode node;

/* function declarations */
void insert(node *, node *);
void dfs_traverse(node *);

/*global declarations */
node *root = NULL;
int val, front = 0, rear = -1, i;
int queue[20];
bool g_fallback = false;

extern "C" {
void process_top(int n, int *input, int *output, int *fallback)
{
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=fallback offset=slave bundle=gmem
#pragma HLS INTERFACE s_axilite port=n bundle=control
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=fallback bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control
    node *newitem = NULL ;
    int num = 10,i=0;
    while(i<n){
        newitem = (node*)malloc(sizeof(node));
        if (newitem == NULL) g_fallback = true;
        newitem->left = newitem->right = NULL;
        newitem->value = input[i];
        if (root == NULL)
            root = newitem;
        else
        {
            insert(newitem, root);
        }
        i++;
    }
    dfs_traverse(root);
    for (i = 0;i < n;i++)
        output[i] = queue[i];
    fallback[0] = g_fallback;
}
};

/* inserting nodes of a tree */
void insert(node * newitem , node *root)
{
    if (newitem->value>root->value)
    {
        if (root->right == NULL)
            root->right = newitem;
        else
            insert (newitem, root->right);
    }
    if (newitem->value < root->value)
    {
        if (root->left  ==  NULL)
            root->left = newitem;
        else
            insert (newitem, root->left);
    }
}

/* displaying elements using BFS traversal */
void dfs_traverse(node *root)
{
    if (root->left != NULL)
        dfs_traverse(root->left);
    queue[++rear] = root->value;
    if (root->right != NULL)
        dfs_traverse(root->right);
}
