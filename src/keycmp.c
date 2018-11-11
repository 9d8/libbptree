#include "keycmp.h"
#include <string.h>

int bptree_keycmp_int(bptree_key key1, bptree_key key2) {
	return key1.i - key2.i;
}

int bptree_keycmp_str(bptree_key key1, bptree_key key2) {
	return strcmp(key1.str, key2.str);
}
