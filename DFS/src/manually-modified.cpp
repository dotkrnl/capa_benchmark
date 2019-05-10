#include <stdlib.h>
#define MAX_LENGTH 200000
#define MAX_STACK 200000
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
int queue[MAX_LENGTH];

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

    queue[++rear] = tree[tree[tree[tree[root].right].right].right].value;
    for (i = 0; i < n; i++) output[i] = queue[i];
}
}

struct _insert_recursion_record {
    int newitem;
    int root;
    int _location;
};

/* inserting nodes of a tree */
void insert(int  newitem , int root)
{
    _insert_recursion_record _stack[MAX_STACK];        // head
    int _stack_top = 0;                                // head

    _stack[_stack_top].newitem = newitem;              // head (init)
    _stack[_stack_top].root = root;                    // head (init)
    _stack[_stack_top]._location = 0;                  // head (init)
    _stack_top++;                                      // head (init)

    while (_stack_top != 0) {                          // head (loop)

        _stack_top--;                                  // after_defination (restore variable)
        newitem = _stack[_stack_top].newitem;          // after_defination (restore variable)
        root = _stack[_stack_top].root;                // after_defination (restore variable)

        int _location = _stack[_stack_top]._location;  // after_defination (restore location)
        if (_location == 0) goto insert_L0;            // after_defination (restore location)
        if (_location == 1) goto insert_L1;            // after_defination (restore location)
        if (_location == 2) goto insert_L2;            // after_defination (restore location)

insert_L0:
    if (tree[newitem].value> tree[root].value)
    {
        if ( tree[root].right == _NULL)
             tree[root].right = newitem;
        else
            //insert (newitem,  tree[root].right);
        {
            _stack[_stack_top].newitem = newitem;      // function call template (store variable)
            _stack[_stack_top].root = root;            // function call template (store variable)
            newitem = _stack[_stack_top].newitem;      // function call template (variable init)
            root = tree[_stack[_stack_top].root].right;// function call template (variable init)
            _stack[_stack_top]._location = 1;          // function call template (store location)
            _stack_top++;                              // function call template (store location)
            goto insert_L0;                            // function call template (jump)
insert_L1:;
        }
    }
    if (tree[newitem].value <  tree[root].value)
    {
        if ( tree[root].left  ==  _NULL)
             tree[root].left = newitem;
        else
            //insert (newitem,  tree[root].left);
        {
            _stack[_stack_top].newitem = newitem;      // function call template (store variable)
            _stack[_stack_top].root = root;            // function call template (store variable)
            newitem = _stack[_stack_top].newitem;      // function call template (variable init)
            root = tree[_stack[_stack_top].root].left; // function call template (variable init)
            _stack[_stack_top]._location = 2;          // function call template (store location)
            _stack_top++;                              // function call template (store location)
            goto insert_L0;                            // function call template (jump)
insert_L2:;
        }
    }
    }
}

struct _dfs_traverse_recursion_record {
    int root;
    int _location;
};

/* displaying elements using BFS traversal */
void dfs_traverse(int root)
{
    _dfs_traverse_recursion_record _stack[MAX_STACK];  // head
    int _stack_top = 0;                                // head

    _stack[_stack_top].root = root;                    // head (init)
    _stack[_stack_top]._location = 0;                  // head (init)
    _stack_top++;                                      // head (init)

    while (_stack_top != 0) {                          // head (loop)

        _stack_top--;                                  // after_defination (restore variable)
        root = _stack[_stack_top].root;                // after_defination (restore variable)

        int _location = _stack[_stack_top]._location;  // after_defination (restore location)
        if (_location == 0) goto dfs_traverse_L0;      // after_defination (restore location)
        if (_location == 1) goto dfs_traverse_L1;      // after_defination (restore location)
        if (_location == 2) goto dfs_traverse_L2;      // after_defination (restore location)

dfs_traverse_L0:
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
        //dfs_traverse(tree[root].left);
        _stack[_stack_top].root = root;            // function call template (store variable)
        root = tree[_stack[_stack_top].root].left; // function call template (variable init)
        _stack[_stack_top]._location = 1;          // function call template (store location)
        _stack_top++;                              // function call template (store location)
        goto dfs_traverse_L0;                      // function call template (jump)
dfs_traverse_L1:;
    }
    if (tree[root].right != _NULL)
    {
        //dfs_traverse(tree[root].right);
        _stack[_stack_top].root = root;            // function call template (store variable)
        root = tree[_stack[_stack_top].root].right;// function call template (variable init)
        _stack[_stack_top]._location = 2;          // function call template (store location)
        _stack_top++;                              // function call template (store location)
        goto dfs_traverse_L0;                      // function call template (jump)
dfs_traverse_L2:;
    }
    }
}
