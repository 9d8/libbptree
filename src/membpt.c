#include "membpt.h"
#include <stdlib.h>
#include "keycmp.h"

static void destroy_nodes(bptree_node* btn);
static bptree_node* create_leaf_node();

bptree* bptree_create(int (*key_compare)(bptree_key key1, bptree_key key2)) {
	bptree* bt = malloc(sizeof(bptree));	
	
	if(key_compare == NULL) {
		bt->key_compare = bptree_keycmp_int;
	} else {
		bt->key_compare = key_compare;
	}
	
	bt->root = create_leaf_node();
	bt->root->children[0].node_p = NULL;
	return bt;
}

void bptree_destroy(bptree* bpt) {
	destroy_nodes(bpt->root);
	free(bpt);
}

void destroy_nodes(bptree_node* btn) {
	if(!btn->is_leaf) {
		for(int i = 0; i < btn->key_count + 1; i++) {
			destroy_nodes(btn->children[i].node_p);
		}
	}
	free(btn);
}

bptree_node* create_leaf_node() {
	bptree_node* btn = malloc(sizeof(bptree_node));
	btn->key_count = 0;
	btn->is_leaf = 1;
	return btn;
}
