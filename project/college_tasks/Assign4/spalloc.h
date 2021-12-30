#ifndef __SPALLOC_H__
#define __SPALLOC_H__ 1

#include <stdint.h>


void sp_seed(uint32_t seed);
uint32_t sp_rand();
void *sp_realloc(void *chunk, uint64_t size);
void sp_free(void *chunk);
void *sp_calloc(size_t nmemb, size_t size);
void *sp_malloc(uint64_t size);


#endif //__SPALLOC_H__

