#include <stdio.h>
#include <bptree.h>
#include "test.h"

void delete_test(bptree* bt);

int main(int argc, char** argv) {
	bptree* bt = bptree_create(TYPE_INT);
	//test_run();
	delete_test(bt);
	bptree_destroy(bt);
	return 0;
}

void insert_test(bptree* bt) {
	char* test = "test";
	char* test2 = "test2";
	char* test3 = "test3";
	char* test4 = "test4";
	char* jojo = "jojo";
	bptree_insert(bt, 1, test);
	bptree_insert(bt, 4, test2);
	bptree_insert(bt, 5, test3);
	bptree_insert(bt, 11, jojo);
	bptree_insert(bt, 2, test);
	bptree_insert(bt, 7, test4);
	bptree_insert(bt, 9, test4);
	bptree_insert(bt, 27, test4);
	bptree_insert(bt, 3, test4);
	bptree_insert(bt, 6, test4);
	bptree_insert(bt, 101, test3);
	bptree_insert(bt, 600, test4);
	bptree_insert(bt, 77, test2);
	bptree_insert(bt, 32, test4);
	bptree_insert(bt, 85, test4);
	bptree_insert(bt, 99, test4);
	printf("--------------------\n");
	dump_keys(bt->root);
	printf("--------------------\n");
	dump_values(bt);
	printf("--------------------\n");
	char* found = bptree_search(bt, 11).data;
	printf("%s's bizzare adventure\n", found);
}

void delete_test(bptree* bt) {
	char* test = "test";

	bptree_insert(bt, 0, test);
	bptree_insert(bt, 912, test);
	bptree_insert(bt, 138, test);
	bptree_insert(bt, 718, test);
	bptree_insert(bt, 213, test);
	bptree_insert(bt, 916, test);
	bptree_insert(bt, 905, test);
	bptree_insert(bt, 358, test);
	bptree_insert(bt, 241, test);
	bptree_insert(bt, 54, test);
	bptree_insert(bt, 942, test);
	bptree_insert(bt, 716, test);
	bptree_insert(bt, 736, test);
	bptree_insert(bt, 704, test);
	bptree_insert(bt, 869, test);
	bptree_insert(bt, 681, test);
	bptree_insert(bt, 798, test);
	bptree_insert(bt, 885, test);
	bptree_insert(bt, 770, test);
	bptree_insert(bt, 791, test);
	bptree_insert(bt, 461, test);
	bptree_insert(bt, 383, test);
	bptree_insert(bt, 354, test);
	bptree_insert(bt, 373, test);
	bptree_insert(bt, 867, test);
	bptree_insert(bt, 804, test);
	bptree_insert(bt, 546, test);
	bptree_insert(bt, 454, test);
	bptree_insert(bt, 570, test);
	bptree_insert(bt, 826, test);
	bptree_insert(bt, 809, test);
	bptree_insert(bt, 549, test);
	bptree_insert(bt, 931, test);
	bptree_insert(bt, 443, test);
	bptree_insert(bt, 378, test);
	bptree_insert(bt, 663, test);
	bptree_insert(bt, 730, test);
	bptree_insert(bt, 970, test);
	bptree_insert(bt, 860, test);
	bptree_insert(bt, 543, test);
	bptree_insert(bt, 43, test);
	bptree_insert(bt, 160, test);
	bptree_insert(bt, 839, test);
	bptree_insert(bt, 141, test);
	bptree_insert(bt, 548, test);
	bptree_insert(bt, 929, test);
	bptree_insert(bt, 952, test);
	bptree_insert(bt, 91, test);
	bptree_insert(bt, 190, test);
	bptree_insert(bt, 965, test);
	bptree_insert(bt, 375, test);

	printf("--------------------\n");
	dump_keys(bt->root);
	printf("--------------------\n");
	
	bptree_delete(bt, 965);
	bptree_delete(bt, 378);

	dump_keys(bt->root);

	bptree_delete(bt, 952);

	dump_keys(bt->root);
}
