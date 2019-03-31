#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bptree.h"
#include "util/random.h"
#include "util/output.h"

int main(int argc, char** argv) {
	srand(time(NULL));
	bptree* bt = bptree_membpt_create();
	bptree_key* kp = key_pool_create(1000);
	get_random_bptree(bt, 10, 100, kp, 1000);
	dump_keys(bt, bt->root);
	bptree_membpt_destroy(bt);
	return 0;
}
