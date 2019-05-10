// C code for linked list merged sort
#include<stdlib.h>
#define MAX_LENGTH 200000
#define MAX_STACK 200000
/* Link list node */
struct Node
{
    int data;
    int next;
};
struct Node LL[MAX_LENGTH];
int freeMemory[MAX_LENGTH];
int noOffreeMemory;
int _NULL = -1;
void initFreeMem(){
    noOffreeMemory = MAX_LENGTH;
    for(int i=0;i<noOffreeMemory;i++){
        LL[i].next = _NULL;
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


/* function prototypes */
int SortedMerge(int a, int b);
void FrontBackSplit(int source,
        int* frontRef, int* backRef);

struct _MergeSort_recursion_record {
    int *headRef;
    int _location;
    int _local_head;
    int _local_a;
    int _local_b;
};

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(int* headRef)
{
    _MergeSort_recursion_record _stack[MAX_STACK];     // head
    int _stack_top = 0;                                // head

    _stack[_stack_top].headRef = headRef;              // head (init)
    _stack[_stack_top]._location = 0;                  // head (init)
    _stack_top++;                                      // head (init)

    while (_stack_top != 0) {                          // head (loop)

int head; // = *headRef;
int a;
int b;

        _stack_top--;                                  // after_defination (restore variable)
        headRef = _stack[_stack_top].headRef;          // after_defination (restore variable)
        head = _stack[_stack_top]._local_head;         // after_defination (restore variable)
        a = _stack[_stack_top]._local_a;               // after_defination (restore variable)
        b = _stack[_stack_top]._local_b;               // after_defination (restore variable)

        int _location = _stack[_stack_top]._location;  // after_defination (restore location)
        if (_location == 0) goto MergeSort_L0;         // after_defination (restore location)
        if (_location == 1) goto MergeSort_L1;         // after_defination (restore location)
        if (_location == 2) goto MergeSort_L2;         // after_defination (restore location)

MergeSort_L0:                                          // after_defination (start point)
        head = *headRef;                               // after_defination (variable initialization)

/* Base case -- length 0 or 1 */
if ((head == _NULL) || (LL[head].next == _NULL))
{
    // return;
        continue;                                      // return template
}

/* Split head into 'a' and 'b' sublists */
FrontBackSplit(head, &a, &b);

/* Recursively sort the sublists */
// MergeSort(&a);
        _stack[_stack_top].headRef = headRef;          // function call template (store variable)
        _stack[_stack_top]._local_head = head;         // function call template (store variable)
        _stack[_stack_top]._local_a = a;               // function call template (store variable)
        _stack[_stack_top]._local_b = b;               // function call template (store variable)
        headRef = &_stack[_stack_top]._local_a;        // function call template (variable init)
        _stack[_stack_top]._location = 1;              // function call template (store location)
        _stack_top++;                                  // function call template (store location)
        goto MergeSort_L0;                             // function call template (jump)
MergeSort_L1:;                                         // function call template (location restore point, no return value)
// MergeSort(&b);
        _stack[_stack_top].headRef = headRef;          // function call template (store variable)
        _stack[_stack_top]._local_head = head;         // function call template (store variable)
        _stack[_stack_top]._local_a = a;               // function call template (store variable)
        _stack[_stack_top]._local_b = b;               // function call template (store variable)
        headRef = &_stack[_stack_top]._local_b;        // function call template (variable init)
        _stack[_stack_top]._location = 2;              // function call template (store location)
        _stack_top++;                                  // function call template (store location)
        goto MergeSort_L0;                             // function call template (jump)
MergeSort_L2:;                                         // function call template (location restore point, no return value)

/* answer = merge the two sorted lists together */
*headRef = SortedMerge(a, b);

    }                                                  // footer
}

struct _SortedMerge_recursion_record {
    int a;
    int b;
    int _location;
    int _local_result;
};

/* See https://www.geeksforgeeks.org/?p=3622 for details of this
function */
int SortedMerge(int a, int b)
{
    _SortedMerge_recursion_record _stack[MAX_STACK];   // head
    int _stack_top = 0;                                // head
    int _return_value = 0;                             // head

    _stack[_stack_top].a = a;                          // head (init)
    _stack[_stack_top].b = b;                          // head (init)
    _stack[_stack_top]._location = 0;                  // head (init)
    _stack_top++;                                      // head (init)

    while (_stack_top != 0) {                          // head (loop)

int result; // = _NULL;

        _stack_top--;                                  // after_defination (restore variable)
        a = _stack[_stack_top].a;                      // after_defination (restore variable)
        b = _stack[_stack_top].b;                      // after_defination (restore variable)
        result = _stack[_stack_top]._local_result;     // after_defination (restore variable)

        int _location = _stack[_stack_top]._location;  // after_defination (restore location)
        if (_location == 0) goto SortedMerge_L0;       // after_defination (restore location)
        if (_location == 1) goto SortedMerge_L1;       // after_defination (restore location)
        if (_location == 2) goto SortedMerge_L2;       // after_defination (restore location)

SortedMerge_L0:                                        // after_defination (start point)
        result = _NULL;                                // after_defination (local init)

/* Base cases */
if (a == _NULL)
    // return(b);
        {_return_value = b; continue; }                // return template
else if (b==_NULL)
    // return(a);
        {_return_value = a; continue; }                // return template

/* Pick either a or b, and recur */
if (LL[a].data <= LL[b].data)
{
    result = a;
    // LL[result].next = SortedMerge(LL[a].next, b);
        _stack[_stack_top].a = a;                      // function call template (store variable)
        _stack[_stack_top].b = b;                      // function call template (store variable)
        _stack[_stack_top]._local_result = result;     // function call template (store variable)
        a = LL[_stack[_stack_top].a].next;             // function call template (variable init)
        b = _stack[_stack_top].b;                      // function call template (variable init)
        _stack[_stack_top]._location = 1;              // function call template (store location)
        _stack_top++;                                  // function call template (store location)
        goto SortedMerge_L0;                           // function call template (jump)
SortedMerge_L1:                                        // function call template (location restore point)
        LL[result].next = _return_value;               // function call template (return value)
}
else
{
    result = b;
    // LL[result].next = SortedMerge(a, LL[b].next);
        _stack[_stack_top].a = a;                      // function call template (store variable)
        _stack[_stack_top].b = b;                      // function call template (store variable)
        _stack[_stack_top]._local_result = result;     // function call template (store variable)
        a = _stack[_stack_top].a;                      // function call template (variable init)
        b = LL[_stack[_stack_top].b].next;             // function call template (variable init)
        _stack[_stack_top]._location = 2;              // function call template (store location)
        _stack_top++;                                  // function call template (store location)
        goto SortedMerge_L0;                           // function call template (jump)
SortedMerge_L2:                                        // function call template (location restore point)
        LL[result].next = _return_value;               // function call template (return value)
}

    // return(result);
        _return_value = result; continue;                // return template

    }                                                  // footer
    return _return_value;                              // footer
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(int source,
        int* frontRef, int* backRef)
{
        int fast;
        int slow;
    slow = source;
    fast = LL[source].next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != _NULL)
    {
    fast = LL[fast].next;
    if (fast != _NULL)
    {
        slow = LL[slow].next;
        fast = LL[fast].next;
    }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = LL[slow].next;
    LL[slow].next = _NULL;
}

/* Function to print nodes in a given linked list */
int *printList(int node, int *output)
{
    while(node!=_NULL)
    {
        *(output++) = LL[node].data;
        node = LL[node].next;
    }
    return output;
}

/* Function to insert a node at the beginging of the linked list */
void push(int* head_ref, int new_data)
{
/* allocate node */
int new_node =
            selfMalloc();

/* put in the data */
LL[new_node].data = new_data;

/* link the old list off the new node */
LL[new_node].next = (*head_ref);

/* move the head to point to the new node */
(*head_ref) = new_node;
}

/* Drier program to test above functions*/
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
/* Start with the empty list */
int res = _NULL;
int a = _NULL;

/* Let us create a unsorted linked lists to test the functions */
for (int i = 0; i < n; i++) {
    push(&a, input[i]);
}

/* Sort the above created Linked List */
MergeSort(&a);

output = printList(a, output);
}
}
