#ifndef TEST_H_
#define TEST_H_

#include "bptree_struct.h"

void test_run();
bptree_key* key_pool_create(int size);
int get_random_bptree(bptree* bpt, int minkeys, int maxkeys, bptree_key* key_pool, int kpsize);

#endif
