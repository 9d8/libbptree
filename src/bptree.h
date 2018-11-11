#ifndef BPTREE_H_
#define BPTREE_H_

#include "bptree_struct.h"
#include "membpt.h"
#include "keycmp.h"

bptree* bptree_create(int (*key_compare)(bptree_key key1, bptree_key key2));
void bptree_destroy(bptree* bpt);
void bptree_insert(bptree* bpt, bptree_key key, void* value);
void bptree_delete(bptree* bpt, bptree_key key);
void* bptree_search(bptree* bpt, bptree_key key);
void dump_keys(bptree_node* btn);
void dump_values(bptree* bpt);

#endif
