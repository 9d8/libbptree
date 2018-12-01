#ifndef BPTREE_H_
#define BPTREE_H_

#include "bptree_struct.h"
#include "membpt.h"
#include "filebpt.h"
#include "keycmp.h"

#undef DISABLE_DELETE

void bptree_insert(bptree* bpt, bptree_key key, void* value);
void bptree_delete(bptree* bpt, bptree_key key);
void* bptree_search(bptree* bpt, bptree_key key);
void dump_keys(bptree* bpt, bptree_addr naddr);
void dump_values(bptree* bpt);

#endif
