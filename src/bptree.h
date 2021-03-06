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
int bptree_get_keys(bptree* bpt, bptree_key** keys);
int bptree_get_values(bptree* bpt, void*** values);

#endif
