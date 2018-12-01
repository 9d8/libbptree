#ifndef BPTREE_STRUCT_H_
#define BPTREE_STRUCT_H_

#include <stdio.h>

/* These defines are currently experimental. Changing them can have unforseen
 * consequences. */
#define ORDER 5
#define MAX_KEYS (ORDER - 1)
#define MIN_KEYS (int)(ORDER/2.0f - 0.5f)
#define MIN_CHILDREN (int)(ORDER/2.0f + 0.5f)

#define BPTN_CREATE_NODE(bpt) bpt->create_node(bpt)
#define BPTN_GET_NODE(bpt, addr) bpt->get_node(bpt, addr)
#define BPTN_KEY_COUNT(bpt, addr) bpt->key_count(bpt, addr)
#define BPTN_IS_LEAF(bpt, addr) bpt->is_leaf(bpt, addr)
#define BPTN_GET_CHILD_KEY(bpt, addr, index) bpt->get_child_key(bpt, addr, index)
#define BPTN_GET_CHILD_ADDR(bpt, addr, index) bpt->get_child_addr(bpt, addr, index)
#define BPTN_DELETE_NODE(bpt, addr) bpt->delete_node(bpt, addr)
#define BPTN_WRITE_NODE(bpt, addr, btn) bpt->write_node(bpt, addr, btn)
#define BPTN_CLOSE_NODE(bpt, btn) bpt->close_node(btn)
#define BPTN_SAVE_AND_CLOSE_NODE(bpt, addr, btn) BPTN_WRITE_NODE(bpt, addr, btn); \
	BPTN_CLOSE_NODE(bpt, btn)

#define KEY_COUNT int
#define BPT_BOOL int

typedef struct bptree bptree;
typedef struct bptree_node bptree_node;
typedef union bptree_addr { bptree_node* node_p; long node_fpos; } bptree_addr;
typedef union { void* data; bptree_addr addr; } bptree_child;
typedef union {int i; char* str;} bptree_key;

struct bptree {
	int (*key_compare)(bptree_key key1, bptree_key key2);

	bptree_addr (*create_node)(bptree* bpt);

	/* Get an allocated node struct that contains the data for the node stored 
	 * in addr. You should always call close_node() on the returned value after
	 * use. */
	bptree_node* (*get_node)(bptree* bpt, bptree_addr addr);
	
	/* These functions are for getting a specific attribute of a given node.
	 * For cases where you are doing many reads for the same node or when you 
	 * want to change these values, use get_node() and write_node() instead. */
	KEY_COUNT (*key_count)(bptree* bpt, bptree_addr addr);
	BPT_BOOL (*is_leaf)(bptree* bpt, bptree_addr addr);
	bptree_key (*get_child_key)(bptree* bpt, bptree_addr addr, int index);
	bptree_addr (*get_child_addr)(bptree* bpt, bptree_addr addr, int index);

	void (*delete_node)(bptree* bpt, bptree_addr addr);
	
	void (*write_node)(bptree* bpt, bptree_addr addr, bptree_node* btn);
	void (*close_node)(bptree_node* btn);
	
	bptree_addr root;

	FILE* fp;
	long offset;
};

struct bptree_node {
	KEY_COUNT key_count;
	BPT_BOOL is_leaf;
	bptree_key keys[MAX_KEYS];
	bptree_child children[ORDER];
};

#endif
