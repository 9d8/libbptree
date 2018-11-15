#ifndef KEYCMP_H_
#define KEYCMP_H_

#include "bptree_struct.h"

int bptree_keycmp_int(bptree_key key1, bptree_key key2);
int bptree_keycmp_str(bptree_key key1, bptree_key key2);
void bptree_set_keycmp(bptree* bpt, int (*key_compare)(bptree_key key1, bptree_key key2));

#endif
