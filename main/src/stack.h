#include "dbg.h"
typedef struct stack {
    struct *next;
    void *value;
} stack;

stack *Stack_create();
Stack_push();
Stack_pop();
Stack_peek();
Stack_destroy();
