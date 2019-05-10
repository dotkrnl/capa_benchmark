// C code for linked list merged sort
#include<stdlib.h>
#define MAX_LENGTH 40
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

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(int* headRef)
{
int head = *headRef;
int a;
int b;

/* Base case -- length 0 or 1 */
if ((head == _NULL) || (LL[head].next == _NULL))
{
	return;
}

/* Split head into 'a' and 'b' sublists */
FrontBackSplit(head, &a, &b);

/* Recursively sort the sublists */
MergeSort(&a);
MergeSort(&b);

/* answer = merge the two sorted lists together */
*headRef = SortedMerge(a, b);
}

/* See https://www.geeksforgeeks.org/?p=3622 for details of this
function */
int SortedMerge(int a, int b)
{
int result = _NULL;

/* Base cases */
if (a == _NULL)
	return(b);
else if (b==_NULL)
	return(a);

/* Pick either a or b, and recur */
if (LL[a].data <= LL[b].data)
{
	result = a;
	LL[result].next = SortedMerge(LL[a].next, b);
}
else
{
	result = b;
	LL[result].next = SortedMerge(a, LL[b].next);
}
return(result);
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
