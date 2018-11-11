#ifndef BPTREE_STRUCT_H_
#define BPTREE_STRUCT_H_

/* These defines are currently experimental. Changing them can have unforseen
 * consequences. */
#define ORDER 5
#define MAX_KEYS (ORDER - 1)
#define MIN_KEYS (int)(ORDER/2.0f - 0.5f)
#define MIN_CHILDREN (int)(ORDER/2.0f + 0.5f)

typedef struct bptree_node bptree_node;
typedef union { void* data; bptree_node* node_p; long node_pos; } bptree_child;
typedef union {int i; char* str;} bptree_key;

typedef struct {
	int (*key_compare)(bptree_key key1, bptree_key key2);
	bptree_child (*create_node)(bptree_node* btn);
	bptree_child (*get_node)(bptree_node* btn, int index);
	bptree_child (*write_node)(bptree_node* btn);
	bptree_node* root;
} bptree;

struct bptree_node {
	int key_count;
	int is_leaf;
	bptree_key keys[MAX_KEYS];
	bptree_child children[ORDER];
};

#endif
