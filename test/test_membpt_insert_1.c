#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bptree.h"
#include "util/valid.h"

void insert_test(bptree* bt);

int main(int argc, char** argv) {
	bptree* bt = bptree_membpt_create();
	insert_test(bt);
	bptree_membpt_destroy(bt);
	return 0;
}

void insert_test(bptree* bt) {
	char* test = "test";
	char* test2 = "test2";
	char* test3 = "test3";
	char* test4 = "test4";
	char* jojo = "jojo";
	
	bptree_insert(bt, (bptree_key)26, test);
	bptree_insert(bt, (bptree_key)900, test);
	bptree_insert(bt, (bptree_key)775, test);
	bptree_insert(bt, (bptree_key)999, test);
	bptree_insert(bt, (bptree_key)693, test);
	bptree_insert(bt, (bptree_key)974, test);
	bptree_insert(bt, (bptree_key)891, test);
	bptree_insert(bt, (bptree_key)745, test);
	bptree_insert(bt, (bptree_key)165, test);
	bptree_insert(bt, (bptree_key)628, jojo);
	bptree_insert(bt, (bptree_key)684, test);
	bptree_insert(bt, (bptree_key)57, test);
	bptree_insert(bt, (bptree_key)168, test);
	bptree_insert(bt, (bptree_key)267, test);
	bptree_insert(bt, (bptree_key)6, test);
	bptree_insert(bt, (bptree_key)167, test);
	bptree_insert(bt, (bptree_key)104, test);
	bptree_insert(bt, (bptree_key)722, test);
	bptree_insert(bt, (bptree_key)602, test);
	bptree_insert(bt, (bptree_key)846, test);
	bptree_insert(bt, (bptree_key)736, test);
	bptree_insert(bt, (bptree_key)543, test);
	bptree_insert(bt, (bptree_key)991, test);
	bptree_insert(bt, (bptree_key)87, test);
	bptree_insert(bt, (bptree_key)742, test);
	bptree_insert(bt, (bptree_key)60, test);
	bptree_insert(bt, (bptree_key)556, test);
	
	printf("--------------------\n");
	dump_keys(bt, bt->root);
	printf("--------------------\n");
	dump_values(bt);
	printf("--------------------\n");
	char* found = bptree_search(bt, ((bptree_key)628));
	printf("%s's bizzare adventure\n", found);

	if(strcmp(found, "jojo")) {
		exit(1);
	}
}
