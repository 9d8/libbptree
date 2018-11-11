#ifndef BPTREE_H_
#define BPTREE_H_

/* These defines are currently experimental. Changing them can have unforseen
 * consequences. */
#define ORDER 5
#define MAX_KEYS (ORDER - 1)
#define MIN_KEYS (int)(ORDER/2.0f - 0.5f)
#define MIN_CHILDREN (int)(ORDER/2.0f + 0.5f)

typedef struct bptree_node bptree_node;
typedef union { void* data; bptree_node* node; } bptree_child;
typedef union {int i; char* str;} bptree_key;
//typedef int bptree_key;

typedef struct {
	int (*key_compare)(bptree_key key1, bptree_key key2);
	bptree_node* root;
} bptree;

struct bptree_node {
	int key_count;
	int is_leaf;
	bptree_key keys[MAX_KEYS];
	bptree_child children[ORDER];
};

bptree* bptree_create(int (*key_compare)(bptree_key key1, bptree_key key2));
void bptree_destroy(bptree* bpt);
void bptree_insert(bptree* bpt, bptree_key key, void* value);
void bptree_delete(bptree* bpt, bptree_key key);
void* bptree_search(bptree* bpt, bptree_key key);
int bptree_int_key_compare(bptree_key key1, bptree_key key2);
int bptree_str_key_compare(bptree_key key1, bptree_key key2);
void dump_keys(bptree_node* btn);
void dump_values(bptree* bpt);

#endif
