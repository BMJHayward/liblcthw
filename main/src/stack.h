#include "dbg.h"
//maybe see ex16 structs
typedef struct stack {//keeps track of length and current position with cur
    struct *next;
    void *value;
} stack;

stack *Stack_create();
Stack_push();
Stack_pop();
Stack_peek();
Stack_destroy();