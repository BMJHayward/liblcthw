#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dbg.h"
#include "tstree.h"

static inline TSTree *TSTree_insert_base(TSTree *root, TSTree *node,
        const char *key, size_t len, void *value)
{
    if(node == NULL) {//if given NULL for this arg fn will create one for you
        node = (TSTree *) calloc(1, sizeof(TSTree));

        if(root == NULL) {
            root = node;
        }

        node->splitchar = *key;
    }

    if(*key < node->splitchar) {//goes to low branch if key is less
        node->low = TSTree_insert_base(root, node->low, key, len, value);
    } else if(*key == node->splitchar) {
        if(len > 1) {
            node->equal = TSTree_insert_base(root, node->equal, key+1, len - 1, value);//insert along equal branch if key == splitchar
        } else {
            assert(node->value == NULL && "Duplicate insert into tst.");
            node->value = value;
        }
    } else {
        node->high = TSTree_insert_base(root, node->high, key, len, value);
    }//if key is higher simply insert recursively along high branch

    return node;
/*//you only increment through characters in the key if the first character is equal, not 
when low or high. makes fn much quicker, though you can get a bad key
*/
}

TSTree *TSTree_insert(TSTree *node, const char *key, size_t len, void *value)
{//parent fn handling initial conditions so TSTree_insert_base can recurse cleanly
    return TSTree_insert_base(node, node, key, len, value);
}

void *TSTree_search(TSTree *root, const char *key, size_t len)
{//same as insert_base except no assignment, only returns node->value
    TSTree *node = root;
    size_t i = 0;

    while(i < len && node) {
        if(key[i] < node->splitchar) {
            node = node->low;
        } else if(key[i] == node->splitchar) {
            i++;
            if(i < len) node = node->equal;
        } else {//goes down equal branch as long as you haven't reached the last character
            node = node->high;
        }
    }

    if(node) {
        return node->value;
    } else {
        return NULL;
    }
}

void *TSTree_search_prefix(TSTree *root, const char *key, size_t len)
{
    if(len == 0) return NULL;

    TSTree *node = root;
    TSTree *last = NULL;
    size_t i = 0;

    while(i < len && node) {
        if(key[i] < node->splitchar) {
            node = node->low;
        } else if(key[i] == node->splitchar) {
            i++;
            if(i < len) {
                if(node->value) last = node;
                node = node->equal;
            }
        } else {
            node = node->high;
        }
    }

    node = node ? node : last;

    //traverse until find the first value in the equal chain
    //this is then the first node with this prefix
    while(node && !node->value) {
        node = node->equal;
    }

    return node ? node->value : NULL;
}

void TSTree_traverse(TSTree *node, TSTree_traverse_cb cb, void *data)
{//takes key and value (cb, *data) and traverse tree to that point
    if(!node) return;

    if(node->low) TSTree_traverse(node->low, cb, data);

    if(node->equal) {
        TSTree_traverse(node->equal, cb, data);
    }

    if(node->high) TSTree_traverse(node->high , cb, data);

    if(node->value) cb(node->value, data);
}

void TSTree_destroy(TSTree *node)//frees node but not whole tree apparently deleting a tree is very difficult and complex i.e. this fn != TSTree_delete()
{
    if(node == NULL) return;

    if(node->low) TSTree_destroy(node->low);

    if(node->equal) {
        TSTree_destroy(node->equal);
    }

    if(node->high) TSTree_destroy(node->high);

    free(node);
}
