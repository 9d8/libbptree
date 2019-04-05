#ifndef FHEAP_H_
#define FHEAP_H_

#include <stdio.h>
#include <stdint.h>

/* In Bytes */
#define BLOCK_SIZE 52

#define FHEAP_ADDR long

typedef struct {
	FILE* fp;
	long free_block[16];
	int end_free_blocks;
	long heap_end;
} fheap;

fheap* fheap_init(FILE* fp);

FHEAP_ADDR fheap_alloc(fheap* heap, size_t size);
void fheap_free(fheap* heap, FHEAP_ADDR pos);

#endif
