#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "btree.h"

int test_btree(int* key_pool);
int* key_pool_create(int size);
void key_pool_destroy(int* key_pool);
void key_pool_shuffle(int* key_pool, int size);

void test_run() {
	srand(time(NULL));
	int* kp = key_pool_create(1000);

	for(int i = 0; i < 50 && !test_btree(kp); i++);

	key_pool_destroy(kp);
}

int test_btree(int* key_pool) {
	printf("Creating a new btree to test.\n");
	btree* bt = btree_create(TYPE_INT);

	int return_code = 0;
	char* value = "test";
	int total_keys = rand()%21 + 5;
	
	printf("Attempting to insert %d random keys.\n", total_keys);
	key_pool_shuffle(key_pool, 1000);
	for(int i = 0; i < total_keys; i++) {
		printf("%d ", key_pool[i]);
		btree_insert(bt, key_pool[i], value);
	}
	printf("\n");

	for(int i = 0; i < total_keys; i++) {
		if(btree_search(bt, key_pool[i]).node == NULL) {
			printf("Unable to find key for value %d.\n", key_pool[i]);	
			return_code = 1;
		}
	}
	
	dump_keys(bt->root);
	
	int total_deletes = rand()%1 + 1;
	printf("Attempting to delete %d random keys.\n", total_deletes);
	key_pool_shuffle(key_pool, total_keys);

	for(int i = 0; i < total_deletes; i++) {
		printf("del: %d\n", key_pool[i]);
		btree_delete(bt, key_pool[i]);
	}
	
	for(int i = total_deletes; i < total_keys; i++) {
		if(btree_search(bt, key_pool[i]).node == NULL) {
			printf("Unable to find key for value %d.\n", key_pool[i]);	
			return_code = 1;
		}
	}
	
	dump_keys(bt->root);
	btree_destroy(bt);
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
