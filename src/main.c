#include <stdio.h>
#include "btree.h"
#include "test.h"

void delete_test(btree* bt);

int main(int argc, char** argv) {
	btree* bt = btree_create(TYPE_INT);
	test_run();
//	delete_test(bt);
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
	dump_keys(bt->root);
	printf("--------------------\n");
	dump_values(bt);
	printf("--------------------\n");
	char* found = btree_search(bt, 11).data;
	printf("%s's bizzare adventure\n", found);
}

void delete_test(btree* bt) {
	char* test = "test";
	btree_insert(bt, 136, test);
	btree_insert(bt, 638, test);
	btree_insert(bt, 593, test);
	btree_insert(bt, 350, test);
	btree_insert(bt, 847, test);
	btree_insert(bt, 267, test);
	btree_insert(bt, 282, test);
	btree_insert(bt, 254, test);
	btree_insert(bt, 406, test);
	btree_insert(bt, 877, test);
	btree_insert(bt, 833, test);
	btree_insert(bt, 292, test);
	btree_insert(bt, 972, test);
//	btree_insert(bt, 680, test);
//	btree_insert(bt, 611, test);
//	btree_insert(bt, 829, test);
//	btree_insert(bt, 26, test);
//	btree_insert(bt, 27, test);
//	btree_insert(bt, 590, test);
//	btree_insert(bt, 123, test);
//	btree_insert(bt, 85, test);
//	btree_insert(bt, 42, test);
//	btree_insert(bt, 882, test);
//	btree_insert(bt, 115, test);
//	btree_insert(bt, 496, test);
//	btree_insert(bt, 84, test);
	
	printf("--------------------\n");
	dump_keys(bt->root);
	printf("--------------------\n");
	btree_delete(bt, 254);
	dump_keys(bt->root);
}
