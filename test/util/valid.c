#include "valid.h"

int is_valid_bptree(bptree* bpt, bptree_key* keys, int total_keys) {
	int return_code = 0;

	for(int i = 0; i < total_keys; i++) {
		if(bptree_search(bpt, keys[i]) == NULL) {
			printf("Unable to find key for value %d.\n", keys[i]);	
			return_code = 1;
		}
	}

	return 1;
}
