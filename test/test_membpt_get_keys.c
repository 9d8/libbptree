#include <stdio.h>
#include <stdlib.h>
#include "bptree.h"
#include "util/output.h"
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

	bptree_key keys[] = { 615, 621, 246, 610, 929, 356, 77, 885, 563, 771, 521, 260, 275, 520, 594, 39, 116, 379, 349, 706, 573, 43, 954, 130, 843, 846, 190, 490, 579 };
	int keyc = 29;

	for(int i = 0; i < keyc; i++) {
		bptree_insert(bt, keys[i], test); 
	}

	dump_keys(bt, bt->root);
	
	if(!is_valid_bpt_linked_list(bt, keys, keyc)) {
		exit(1);
	}
}
