#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bptree.h"
#include "output.h"
#include "valid.h"

int test_bptree(bptree_key* key_pool);
void key_pool_shuffle(bptree_key* key_pool, int size);

FILE* fp;

void test_run() {
	srand(time(NULL));
	bptree_key* kp = key_pool_create(1000);
	fp = fopen("test.bptree", "w+b");

	for(int i = 0; i < 10000 && !test_bptree(kp); i++);

	fclose(fp);
	free(kp);
}

int test_bptree(bptree_key* key_pool) {
	printf("Creating a new bptree to test.\n");
	bptree* bt = bptree_membpt_create();

	int total_keys = get_random_bptree(bt, 10, 100, key_pool, 1000);

	int return_code = !is_valid_bptree(bt, key_pool, total_keys);

	for(int i = 0; i < total_keys; i++) {
		if(bptree_search(bt, key_pool[i]) == NULL) {
			printf("Unable to find key for value %d.\n", key_pool[i]);	
			return_code = 1;
		}
	}
	
	dump_keys(bt, bt->root);
	
	int total_deletes = rand()%5 + 1;
	printf("Attempting to delete %d random keys.\n", total_deletes);
	key_pool_shuffle(key_pool, total_keys);

	for(int i = 0; i < total_deletes; i++) {
		printf("del: %d\n", key_pool[i]);
		bptree_delete(bt, key_pool[i]);
		if(bptree_search(bt, key_pool[i]) != NULL) {
			printf("The key %d should have been deleted, but it wasn't.\n", key_pool[i]);
			return_code = 1;
		}
	}
	
	for(int i = total_deletes; i < total_keys; i++) {
		if(bptree_search(bt, (bptree_key)key_pool[i]) == NULL) {
			printf("Unable to find key for value %d.\n", key_pool[i]);	
			return_code = 1;
		}
	}
		
	dump_keys(bt, bt->root);
	
	bptree_membpt_destroy(bt);
	return return_code;
}

int test_tree(bptree* bt, int* keys, int kc) {
	int return_code = 0;

	for(int i = 0; i < kc; i++) {
		if(bptree_search(bt, (bptree_key)keys[i]) == NULL) {
			return_code = 1;
		}
	}

	return return_code;
}

bptree_key* key_pool_create(int size) {
	bptree_key* key_pool = malloc(sizeof(bptree_key)*size);
	for(int i = 0; i < size; i++) {
		key_pool[i].i = i;
	}
	return key_pool;
}

void key_pool_shuffle(bptree_key* key_pool, int size) {
	for(int i = 0; i < size - 1; i++) {
		int j = rand()%(size - i) + i;	
		int temp = key_pool[i].i;
		key_pool[i] = key_pool[j];
		key_pool[j].i = temp;
	}
}

int get_random_bptree(bptree* bpt, int minkeys, int maxkeys, bptree_key* key_pool, int kpsize) {
	char* value = "test";
	int total_keys = rand()%(maxkeys - minkeys) + minkeys;
	
	printf("Attempting to create a bptree with %d random keys...\n", total_keys);
	key_pool_shuffle(key_pool, kpsize);
	for(int i = 0; i < total_keys; i++) {
		printf("%d, ", key_pool[i]);
		bptree_insert(bpt, (bptree_key)key_pool[i], value);
	}
	printf("\n");

	return total_keys;
}
