#include "fheap.h"
#include <stdlib.h>

fheap* fheap_init(FILE* fp) {
	/* Init fheap struct */
	fheap* heap = malloc(sizeof(fheap));
	heap->fp = fp;

	/* Expand file for writing */

	/* Write Mem List */
	const int block_sizes = 16;
	for(int i = 0; i < block_sizes; i++) {
		heap->free_block[i] = EOF;
	}
	fwrite(&block_sizes , sizeof(block_sizes), 1, fp);
	fwrite(heap->free_block, sizeof(heap->free_block[0]), 16, fp);

	heap->end_free_blocks = 0;
	heap->heap_end = ftell(fp);
}

long fheap_write(fheap* heap, void* data, size_t size, size_t num) {
	int blocks = (size * num - 1)/8 + 1;
	int block_size_index = blocks - 1;

	/* Search for freed blocks to overwrite. Starting with the size of the data 
	 * we want to write. */
	while(heap->free_block[block_size_index] == EOF && block_size_index < 16) {
		block_size_index++;
	}

	if(block_size_index == 16) {
		/* Write to end of heap, or add more memory. */
		fseek(heap->fp, heap->heap_end, SEEK_SET);

		if(blocks > heap->end_free_blocks) {
			/* Add more blocks to heap. */
			int new_blocks;
			heap->end_free_blocks += new_blocks - blocks;
		}

		fwrite(data, size, num, heap->fp);
	} else {
		/* Write bytes and split empty bytes. */
	}
}

void fheap_free(fheap* heap, long pos);
