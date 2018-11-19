#include "membpt.h"
#include <stdlib.h>
#include "keycmp.h"

static void destroy_nodes(bptree_node* btn);
static bptree_addr create_leaf_node();
static bptree_node* membpt_get_node(bptree* bpt, bptree_addr naddr);
static KEY_COUNT membpt_key_count(bptree* bpt, bptree_addr addr);
static BPT_BOOL membpt_is_leaf(bptree* bpt, bptree_addr addr);
static bptree_key membpt_get_child_key(bptree* bpt, bptree_addr addr, int index);
static bptree_addr membpt_get_child_addr(bptree* bpt, bptree_addr addr, int index);
static void membpt_write_node(bptree* bpt, bptree_addr addr, bptree_node* btn);
static void membpt_close_node(bptree_node* btn);


bptree* bptree_membpt_create() {
	bptree* bt = malloc(sizeof(bptree));	
	
	bt->key_compare = bptree_keycmp_int;
	bt->create_node = create_leaf_node;
	bt->get_node = membpt_get_node;
	bt->key_count = membpt_key_count;
	bt->is_leaf = membpt_is_leaf;
	bt->get_child_key = membpt_get_child_key;
	bt->get_child_addr = membpt_get_child_addr;
	bt->write_node = membpt_write_node;
	bt->close_node = membpt_close_node;

	bt->root = create_leaf_node();
	bt->root.node_p->children[0].addr.node_p = NULL;
	return bt;
}

void bptree_membpt_destroy(bptree* bpt) {
	destroy_nodes(bpt->root.node_p);
	free(bpt);
}

void destroy_nodes(bptree_node* btn) {
	if(!btn->is_leaf) {
		for(int i = 0; i < btn->key_count + 1; i++) {
			destroy_nodes(btn->children[i].addr.node_p);
		}
	}
	free(btn);
}

bptree_addr create_leaf_node() {
	bptree_node* btn = malloc(sizeof(bptree_node));
	btn->key_count = 0;
	btn->is_leaf = 1;
	return (bptree_addr)btn;
}
	
bptree_node* membpt_get_node(bptree* bpt, bptree_addr addr) {
	return addr.node_p;
}
	
KEY_COUNT membpt_key_count(bptree* bpt, bptree_addr addr) {
	return addr.node_p->key_count;
}

BPT_BOOL membpt_is_leaf(bptree* bpt, bptree_addr addr) {
	return addr.node_p->is_leaf;
}

bptree_key membpt_get_child_key(bptree* bpt, bptree_addr addr, int index) {
	return addr.node_p->keys[index];
}

bptree_addr membpt_get_child_addr(bptree* bpt, bptree_addr addr, int index) {
	return addr.node_p->children[index].addr;
}

/* For a memory b+ tree, these functions dont actually do anything. */
void membpt_write_node(bptree* bpt, bptree_addr addr, bptree_node* btn) {

}

void membpt_close_node(bptree_node* btn) {

}
