#ifndef _lcthw_TSTree_h
#define _lcthw_TSTree_h

#include <stdlib.h>
#include "darray.h"

typedef struct TSTree {
    char splitchar;//character at this point in tree
    struct TSTree *low;
    struct TSTree *equal;
    struct TSTree *high;
    void *value;//value for this point in tree with splitchar
} TSTree;

void *TSTree_search(TSTree *root, const char *key, size_t len);

void *TSTree_search_prefix(TSTree *root, const char *key, size_t len);//finds first prefix of a key rather than whole thing

typedef void (*TSTree_traverse_cb)(void *value, void *data);

TSTree *TSTree_insert(TSTree *node, const char *key, size_t len, void *value);//will break key down by each character and insert into tree

void TSTree_traverse(TSTree *node, TSTree_traverse_cb cb, void *data);

void TSTree_destroy(TSTree *root);
/*frees nodes but not same as a TSTree_delete
can use TSTree to search by suffix or approximate most of the characters into groups or other algorithms
difficult to delete from TSTrees and uses lots more memory compared with BSTrees and hashmaps
*/
#endif
