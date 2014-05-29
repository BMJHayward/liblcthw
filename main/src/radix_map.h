#ifndef _radixmap_h
#include <stdint.h>

typedef union RMElement {//unions are a type of struct where members occupy same space in memory, so an int, uint64, and a struct within a union are all in the same place, allowing other functions to use a call to or argument from elements in a union in the same way as other types and data structures. If you change one member, you change the others. The union is the size of it's biggest member.
    uint64_t raw;
    struct {
        uint32_t key;
        uint32_t value;
    } data;
} RMElement;

typedef struct RadixMap {
    size_t max;
    size_t end;
    uint32_t counter;
    RMElement *contents;
    RMElement *temp;
} RadixMap;

RadixMap *RadixMap_create(size_t max);

void RadixMap_destroy(RadixMap *map);

void RadixMap_sort(RadixMap *map);

RMElement *RadixMap_find(RadixMap *map, uint32_t key);

int RadixMap_add(RadixMap *map, uint32_t key, uint32_t value);

int RadixMap_delete(RadixMap *map, RMElement *el);

#endif