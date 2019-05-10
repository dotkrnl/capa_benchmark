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
    int temp = LL[head].next;
    LL[head].next = LL[LL[head].next].next;
    selfFree(temp);
}

struct _reverse_rec_recursion_record {
    int ptr;
    int previous;
    int _local_temp;
    int _location;
};
#define MAX_STACK 20

int reverse_rec(int ptr, int previous) {
    _reverse_rec_recursion_record _stack[MAX_STACK];   // head
    int _stack_top = 0;                                // head
    int _return_value = 0;                             // head

    _stack[_stack_top].ptr = ptr;                      // head (init)
    _stack[_stack_top].previous = previous;            // head (init)
    _stack[_stack_top]._local_temp = 0;                // head (init)
    _stack[_stack_top]._location = 0;                  // head (init)
    _stack_top++;                                      // head (init)

    while (_stack_top != 0) {                          // head (loop)

    int temp;

        _stack_top--;                                  // after_defination (restore variable)
        ptr = _stack[_stack_top].ptr;                  // after_defination (restore variable)
        previous = _stack[_stack_top].previous;        // after_defination (restore variable)
        temp = _stack[_stack_top]._local_temp;         // after_defination (restore variable)

        int _location = _stack[_stack_top]._location;  // after_defination (restore location)
        if (_location == 0) goto reverse_rec_L0;       // after_defination (restore location)
        if (_location == 1) goto reverse_rec_L1;       // after_defination (restore location)

reverse_rec_L0:                                        // after_defination (start point)
    if (LL[ptr].next == _NULL) {
        LL[ptr].next = previous;

        // return ptr;
        _return_value = ptr; continue;                 // return template
    } else {
        // temp = reverse_rec(LL[ptr].next, ptr);
        _stack[_stack_top].ptr = ptr;                  // function call template (store variable)
        _stack[_stack_top].previous = previous;        // function call template (store variable)
        _stack[_stack_top]._local_temp = temp;         // function call template (store variable)
        ptr = LL[_stack[_stack_top].ptr].next;         // function call template (variable init)
        previous = _stack[_stack_top].ptr;             // function call template (variable init)
        temp = 0;                                      // function call template (variable init)
        _stack[_stack_top]._location = 1;              // function call template (store location)
        _stack_top++;                                  // function call template (store location)
        goto reverse_rec_L0;                           // function call template (jump)
reverse_rec_L1:                                        // function call template (location restore point)
        temp = _return_value;                          // function call template (return value)

        LL[ptr].next = previous;

        // return temp;
        _return_value = temp; continue;                // return template
    }

    }                                                  // footer
    return _return_value;                              // footer
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
