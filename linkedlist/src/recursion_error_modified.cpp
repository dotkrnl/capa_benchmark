#include <stdlib.h>

#define MAX_LENGTH 20

typedef struct {
    int info;
} DATA;

typedef struct node {
    DATA data;
    int next;
} NODE;

NODE LL[MAX_LENGTH];
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


void init(int* head) {
    *head = _NULL;
}

int *output_list(int head, int *curr) {
    int temp;
    for (temp = head; temp!=_NULL; temp = LL[temp].next) {
		*(curr++) = LL[temp].data.info;
	}
	return curr;
}
void selfFree(int index){
    freeMemory[noOffreeMemory] = index;
    noOffreeMemory++;
}
int selfMalloc(){
    if(noOffreeMemory<1){
        return _NULL;
    } else{
        noOffreeMemory--;
        return freeMemory[noOffreeMemory];
    }
}

int add(int node, DATA data) {

    int temp = selfMalloc();

    if (temp == _NULL) {
        exit(0); // no memory available
    }
    LL[temp].data = data;
    LL[temp].next = node;
    node = temp;
    return node;
}

void add_at(int node, DATA data) {
    int temp = selfMalloc();
    if (temp == _NULL) {
        exit(EXIT_FAILURE); // no memory available
    }
    LL[temp].data = data;
    LL[temp].next = LL[node].next;
    LL[node].next = temp;
}

void remove_node(int head) {
    int temp = selfMalloc();
    if (temp == _NULL) {
        exit(EXIT_FAILURE); // no memory available
    }
    temp = LL[head].next;
    LL[head].next = LL[LL[head].next].next;
    selfFree(temp);
}

int reverse_rec(int ptr, int previous) {
    int temp;
    if (LL[ptr].next == _NULL) {
        LL[ptr].next = previous;
        return ptr;
    } else {
        temp = reverse_rec(LL[ptr].next, ptr);
        LL[ptr].next = previous;
        return temp;
    }
}

int sort_list(int head) {
    int tmpPtr = head, tmpNxt = LL[head].next;
    DATA tmp;
    while (tmpNxt != _NULL) {
        while (tmpNxt != tmpPtr) {
            if (LL[tmpNxt].data.info < LL[tmpPtr].data.info) {
                tmp = LL[tmpPtr].data;
                LL[tmpPtr].data = LL[tmpNxt].data;
                LL[tmpNxt].data = tmp;
            }
            tmpPtr = LL[tmpPtr].next;
        }
        tmpPtr = head;
        tmpNxt = LL[tmpNxt].next;
    }
    return tmpPtr;
}

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
    int i;
    int head = 0;
    int node;
    DATA element;

    init(&head);
    for (i = 0; i < n; i++) {
        element.info = input[i];
        head = add(head, element);
    }

   	int *curr = output;
	curr = output_list(head, curr);
    *(curr++) = -1;

    node = LL[LL[LL[head].next].next].next;
    element.info = 2000;
    add_at(node, element);
    curr = output_list(head, curr);
    *(curr++) = -1;

    node = LL[LL[head].next].next;
    remove_node(node);
    head = sort_list(head); // Sort The List
    curr = output_list(head, curr);
    *(curr++) = -1;

    head = reverse_rec(head,_NULL); // Revers The List
    curr = output_list(head, curr);
    *(curr++) = -1;

  return;
}

}//extern "C"
