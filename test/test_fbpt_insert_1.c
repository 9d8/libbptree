#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bptree.h"
#include "util/output.h"
#include "util/valid.h"

void insert_test(bptree* bt);

int main(int argc, char** argv) {
	FILE* fp = fopen("cache/fbpt_insert_1.bpt", "w+b");

	bptree* bt = bptree_fbpt_create(fp);
	insert_test(bt);
	bptree_fbpt_destroy(bt);

	fclose(fp);
	return 0;
}

void insert_test(bptree* bt) {
	char* test = "test";
	char* test2 = "test2";
	char* test3 = "test3";
	char* test4 = "test4";
	char* jojo = "jojo";

	bptree_key keys[] = { 26, 900, 775, 999, 693, 974, 891, 745, 165, 628, 684, 57, 168, 267, 6, 167, 104, 722, 602, 846, 736, 543, 991, 87, 742, 60, 556 };
	int keyc = 26;

	for(int i = 0; i < keyc; i++) {
		if(i == 9) {
			bptree_insert(bt, keys[i], jojo); 
		} else {
			bptree_insert(bt, keys[i], test); 
		}
	}

	printf("--------------------\n");
	dump_keys(bt, bt->root);
	printf("--------------------\n");
	dump_values(bt);
	printf("--------------------\n");
	char* found = bptree_search(bt, ((bptree_key)628));
	printf("%s's bizzare adventure\n", found);

	if(!is_valid_bptree(bt, keys, keyc) || strcmp(found, "jojo")) {
		exit(1);
	}
}
