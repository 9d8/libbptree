#include "output.h"

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
	bptree_addr addr = bpt->root;
	while(!BPTN_IS_LEAF(bpt, addr)) {
		addr = BPTN_GET_CHILD_ADDR(bpt, addr, 0);
	}
	
	bptree_node* node = BPTN_GET_NODE(bpt, addr);
	
	while(node != NULL) {
		for(int i = 0; i < node->key_count; i++) {
			printf("%s ", node->children[i + 1].data);
		}
		bptree_addr next_addr = node->children[0].addr;
		BPTN_CLOSE_NODE(bpt, node);
		node = BPTN_GET_NODE(bpt, next_addr);
	}

	printf("\n");
}
