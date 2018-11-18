#ifndef BPTREE_STRUCT_H_
#define BPTREE_STRUCT_H_

/* These defines are currently experimental. Changing them can have unforseen
 * consequences. */
#define ORDER 5
#define MAX_KEYS (ORDER - 1)
#define MIN_KEYS (int)(ORDER/2.0f - 0.5f)
#define MIN_CHILDREN (int)(ORDER/2.0f + 0.5f)

typedef struct bptree_node bptree_node;
typedef union bptree_addr { bptree_node* node_p; long node_fpos; } bptree_addr;
typedef union { void* data; bptree_addr addr; } bptree_child;
typedef union {int i; char* str;} bptree_key;

typedef struct {
	int (*key_compare)(bptree_key key1, bptree_key key2);

	bptree_addr (*create_node)(void);

	/* Get an allocated node struct that contains the data for the node stored 
	 * in addr. You should always call close_node() on the returned value after
	 * use. */
	bptree_node* (*get_node)(bptree_addr addr);
	
	/* These functions are for getting a specific attribute of a given node.
	 * For cases where you are doing many reads for the same node or when you 
	 * want to change these values, use get_node() and write_node() instead. */
	int (*key_count)(bptree_addr addr);
	int (*is_leaf)(bptree_addr addr);
	bptree_key (*get_child_key)(bptree_addr addr, int index);
	bptree_addr (*get_child_addr)(bptree_addr addr, int index);
	
	void (*write_node)(bptree_addr addr, bptree_node* btn);
	void (*close_node)(bptree_node* btn);
	bptree_addr root;
} bptree;

struct bptree_node {
	int key_count;
	int is_leaf;
	bptree_key keys[MAX_KEYS];
	bptree_child children[ORDER];
};

#endif
