#ifndef MEMBPT_H_
#define MEMBPT_H_

#include "bptree_struct.h"

bptree* bptree_create(int (*key_compare)(bptree_key key1, bptree_key key2));
void bptree_destroy(bptree* bpt);

#endif
