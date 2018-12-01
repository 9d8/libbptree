#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bptree.h"

int test_bptree(int* key_pool);
int* key_pool_create(int size);
void key_pool_destroy(int* key_pool);
void key_pool_shuffle(int* key_pool, int size);

FILE* fp;

void test_run() {
	srand(time(NULL));
	int* kp = key_pool_create(1000);
	fp = fopen("test.bptree", "w+b");

	for(int i = 0; i < 10000 && !test_bptree(kp); i++);

	fclose(fp);
	key_pool_destroy(kp);
}

int test_bptree(int* key_pool) {
	printf("Creating a new bptree to test.\n");
	bptree* bt = bptree_fbpt_create(fp);

	int return_code = 0;
	char* value = "test";
	int total_keys = rand()%91 + 10;
	
	printf("Attempting to insert %d random keys.\n", total_keys);
	key_pool_shuffle(key_pool, 1000);
	for(int i = 0; i < total_keys; i++) {
		printf("bptree_insert(bt, (bptree_key)%d, test);\n", key_pool[i]);
		bptree_insert(bt, (bptree_key)key_pool[i], value);
	}
	printf("\n");

	for(int i = 0; i < total_keys; i++) {
		if(bptree_search(bt, (bptree_key)key_pool[i]) == NULL) {
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
		bptree_delete(bt, (bptree_key)key_pool[i]);
		if(bptree_search(bt, (bptree_key)key_pool[i]) != NULL) {
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

int* key_pool_create(int size) {
	int* key_pool = malloc(sizeof(int)*size);
	for(int i = 0; i < size; i++) {
		key_pool[i] = i;
	}
	return key_pool;
}

void key_pool_destroy(int* key_pool) {
	free(key_pool);
}

void key_pool_shuffle(int* key_pool, int size) {
	for(int i = 0; i < size - 1; i++) {
		int j = rand()%(size - i) + i;	
		int temp = key_pool[i];
		key_pool[i] = key_pool[j];
		key_pool[j] = temp;
	}
}
