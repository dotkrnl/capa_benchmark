#include <stdlib.h>

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

extern "C" {
void process_top(int n, int *input, int *output)
{
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem
#pragma HLS INTERFACE s_axilite port=n bundle=control
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control
    node *newitem = NULL ;
    int num = 10,i=0;
    while(i<n){
        newitem = (node*)malloc(sizeof(node));
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
    queue[++rear] = root->value;
    dfs_traverse(root);
    for (i = 0;i <= rear;i++)
        output[i] = queue[i];
    output[rear + 1] = root->right->right->right->value;
}
}

/* inserting nodes of a tree */
void insert(node * newitem , node *root)
{
    if (newitem->value>root->value)
    {
        if (root->right == NULL)
            root->right = newitem;
    }
    if (newitem->value < root->value)
    {
        if (root->left  ==  NULL)
            root->left = newitem;
    }
}

/* displaying elements using BFS traversal */
void dfs_traverse(node *root)
{
    val = root->value;
    if ((front <= rear)&&(root->value == queue[front]))
    {
        if (root->left != NULL)
            queue[++rear] = root->left->value;
        if (root->right != NULL || root->right  ==  NULL)
            queue[++rear] = root->right->value;
        front++;
    }
}
