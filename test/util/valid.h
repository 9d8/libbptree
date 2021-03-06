#ifndef VALID_H_
#define VALID_H_

#include "bptree.h"

int is_valid_bptree(bptree* bpt, bptree_key* keys, int total_keys);
int is_valid_bpt_linked_list(bptree* bpt, bptree_key* keys, int total_keys);

#endif
