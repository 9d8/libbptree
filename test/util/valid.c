#include "valid.h"
#include <stdlib.h>

int is_valid_bptree(bptree* bpt, bptree_key* keys, int total_keys) {
	int return_code = 1;

	for(int i = 0; i < total_keys; i++) {
		if(bptree_search(bpt, keys[i]) == NULL) {
			printf("Unable to find key for value %d.\n", keys[i]);	
			return_code = 0;
		}
	}

	return_code = return_code && is_valid_bpt_linked_list(bpt, keys, total_keys);

	return return_code;
}

int is_valid_bpt_linked_list(bptree* bpt, bptree_key* keys, int total_keys) {
	int return_code = 1;
	
	bptree_key* tree_keys;
	int total_tree_keys = bptree_get_keys(bpt, &tree_keys);
	
	void** tree_data;
	int total_tree_data = bptree_get_values(bpt, &tree_data);

	if(total_keys != total_tree_keys) {
		return_code = 0;
	}
	
	/* Sort original key array since bptree_get_keys will return a sorted 
	 * array. */
	for(int i = 0; i < total_keys; i++) {
		for(int j = 0; j < total_keys - 1 - i; j++) {
			if(keys[j].i > keys[j+1].i) {
				bptree_key tmp = keys[j];
				keys[j] = keys[j+1];
				keys[j+1] = tmp;
			}
		}
	}

	for(int i = 0; return_code && i < total_keys; i++) {
		if(keys[i].i != tree_keys[i].i) {
			printf("%d != %d\n", keys[i].i, tree_keys[i].i);
			printf("Keys did not match!\n");
			return_code = 0;
		}
	}
	
	for(int i = 0; return_code && i < total_keys; i++) {
		if(tree_data[i] != bptree_search(bpt, tree_keys[i])) {
			printf("Tree values did not match!\n");
			return_code = 0;
		}
	}

	free(tree_keys);
	free(tree_data);
	return return_code;
}
