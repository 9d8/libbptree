#ifndef BPTREE_H_
#define BPTREE_H_

/* These defines are currently experimental. Changing them can have unforseen
 * consequences. */
#define ORDER 5
#define MAX_KEYS (ORDER - 1)
#define MIN_KEYS (int)(ORDER/2.0f - 0.5f)
#define MIN_CHILDREN (int)(ORDER/2.0f + 0.5f)

typedef struct bptree_node bptree_node;
typedef enum {TYPE_INT, TYPE_STRING} bptree_type;
typedef union { void* data; bptree_node* node; } bptree_child;
//typedef union {int i; char* str;} bptree_key;
typedef int bptree_key;

typedef struct {
	bptree_type key_type;
	bptree_node* root;
} bptree;

struct bptree_node {
	int key_count;
	int is_leaf;
	bptree_key keys[MAX_KEYS];
	bptree_child children[ORDER];
};

bptree* bptree_create(bptree_type key_type);
void bptree_destroy(bptree* bt);
void bptree_insert(bptree* bt, bptree_key key, void* value);
void bptree_delete(bptree* bt, bptree_key key);
bptree_child bptree_search(bptree* bt, bptree_key key);
void dump_keys(bptree_node* btn);
void dump_values(bptree* bt);

#endif
