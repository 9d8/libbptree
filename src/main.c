#include <stdio.h>
#include "btree.h"

int main(int argc, char** argv) {
	btree* bt = btree_create(TYPE_INT);
	char* test = "t";
	btree_insert(bt, 12, test);
	btree_insert(bt, 6, test);
	btree_insert(bt, 7, test);
	btree_insert(bt, 8, test);
	btree_insert(bt, 15, test);
	btree_insert(bt, 27, test);
	btree_insert(bt, 5, test);
	printf("--------------------\n");
	dump_keys(bt->root, 100);
	printf("--------------------\n");
	btree_delete(bt, 15);
	btree_delete(bt, 5);
	btree_delete(bt, 8);
	dump_keys(bt->root, 100);
	printf("--------------------\n");
	btree_destroy(bt);
	return 0;
}

void insert_test(btree* bt) {
	char* test = "test";
	char* test2 = "test2";
	char* test3 = "test3";
	char* test4 = "test4";
	char* jojo = "jojo";
	btree_insert(bt, 1, test);
	btree_insert(bt, 4, test2);
	btree_insert(bt, 5, test3);
	btree_insert(bt, 11, jojo);
	btree_insert(bt, 2, test);
	btree_insert(bt, 7, test4);
	btree_insert(bt, 9, test4);
	btree_insert(bt, 27, test4);
	btree_insert(bt, 3, test4);
	btree_insert(bt, 6, test4);
	btree_insert(bt, 101, test3);
	btree_insert(bt, 600, test4);
	btree_insert(bt, 77, test2);
	btree_insert(bt, 32, test4);
	btree_insert(bt, 85, test4);
	btree_insert(bt, 99, test4);
	printf("--------------------\n");
	dump_keys(bt->root, 100);
	printf("--------------------\n");
	dump_values(bt);
	printf("--------------------\n");
	char* found = btree_search(bt, 11).data;
	printf("%s's bizzare adventure\n", found);
}
