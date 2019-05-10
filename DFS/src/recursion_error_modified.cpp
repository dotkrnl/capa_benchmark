#include <stdlib.h>
#define MAX_LENGTH 100
struct btnode
{
    int value;
    int left, right;
};
typedef struct btnode node;

node tree[MAX_LENGTH];
int freeMemory[MAX_LENGTH];
int noOffreeMemory;
int _NULL = -1;
void initFreeMem(){
    noOffreeMemory = MAX_LENGTH;
    for(int i=0;i<noOffreeMemory;i++){
        tree[i].left = _NULL;
        tree[i].right = _NULL;
        freeMemory[i] = i;
    }
}
int selfMalloc(){
    if(noOffreeMemory<1){
        return _NULL;
    } else{
        noOffreeMemory--;
        return freeMemory[noOffreeMemory];
    }
}

/* function declarations */
void insert(int, int );
void dfs_traverse(int );

/*global declarations */
int root = -1;
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
    initFreeMem();
    int newitem = _NULL ;
    int num = 10,i=0;
    while(i<n){
        newitem = selfMalloc();
        tree[newitem].left = tree[newitem].right = _NULL;
        tree[newitem].value = input[i];
        if (root == _NULL)
            root = newitem;
        else
        {
            insert(newitem, root);
        }
        i++;
    }

    queue[++rear] = tree[root].value;
    dfs_traverse(root);
    for (i = 0;i <= rear;i++)
        output[i] = queue[i];
    output[rear + 1] = tree[tree[tree[tree[root].right].right].right].value;
}
}

/* inserting nodes of a tree */
void insert(int  newitem , int root)
{
    if (tree[newitem].value> tree[root].value)
    {
        if ( tree[root].right == _NULL)
             tree[root].right = newitem;
        else
            insert (newitem,  tree[root].right);
    }
    if (tree[newitem].value <  tree[root].value)
    {
        if ( tree[root].left  ==  _NULL)
             tree[root].left = newitem;
        else
            insert (newitem,  tree[root].left);
    }
}

/* displaying elements using BFS traversal */
void dfs_traverse(int root)
{
    val = tree[root].value;
    if ((front <= rear)&&(tree[root].value == queue[front]))
    {
        if (tree[root].left != _NULL)
            queue[++rear] = tree[tree[root].left].value;
        if (tree[root].right != _NULL || tree[root].right  ==  _NULL)
            queue[++rear] = tree[tree[root].right].value;
        front++;
    }
    if (tree[root].left != _NULL)
    {
        dfs_traverse(tree[root].left);
    }
    if (tree[root].right != _NULL)
    {
        dfs_traverse(tree[root].right);
    }
}
