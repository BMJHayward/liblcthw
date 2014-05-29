#include "dbg.h"
//maybe see ex16 structs
typedef struct queue {
    struct *next;
    void *value;
} queue;

queue *Queue_create();
Queue_destroy();
Queue_send();
Queue_receive();