#ifndef hashmap_algos_h
#define hashmap_algos_h
#include <stdint.h>

uint32_t Hashmap_fnv1a_hash(void *data);//produces good numbers is reasonably fast
uint32_t Hashmap_adler32_hash(void *data);//old, horrible but good to study
uint32_t Hashmap_djb_hash(void *data);//fast possible not great numbers

#endif