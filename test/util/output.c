#include "output.h"
#include <stdlib.h>
#include "bptree.h"

static void dump_keys_aux(bptree* bpt, bptree_addr naddr, int depth);

void dump_keys_aux(bptree* bpt, bptree_addr naddr, int depth) {
	bptree_node* btn = BPTN_GET_NODE(bpt, naddr);

	printf("%*s", depth*4, "");
	for(int i = 0; i < btn->key_count; i++) {
		printf("%d:%s ", btn->keys[i], btn->is_leaf? btn->children[i + 1].data: "-");
	}
	
	printf("\n");
	
	if(!btn->is_leaf) {
		for(int i = 0; i < btn->key_count + 1; i++) {
			dump_keys_aux(bpt, btn->children[i].addr, depth + 1);
		}
	}

	bpt->close_node(btn);
}

void dump_keys(bptree* bpt, bptree_addr naddr) {
	dump_keys_aux(bpt, naddr, 0);
}

void dump_values(bptree* bpt) {
	char** data;
	int total_data = bptree_get_values(bpt, (void***) &data);
	
	for(int i = 0; i < total_data; i++) {
		printf("%s ", data[i]);
	}

	printf("\n");
	free(data);
}
