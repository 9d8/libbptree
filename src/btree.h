#ifndef BTREE_H_
#define BTREE_H_

typedef struct btree_node btree_node;
typedef enum {TYPE_INT, TYPE_STRING} btree_type;
typedef union { void* data; btree_node* node; } btree_child;
//typedef union {int i; char* str;} btree_key;
typedef int btree_key;

typedef struct {
	btree_type key_type;
	btree_node* root;
} btree;

struct btree_node {
	int key_count;
	int is_leaf;
	btree_key keys[4];
	btree_child children[5];
};

btree* btree_create(btree_type key_type);
void btree_destroy(btree* bt);
void btree_insert(btree* bt, btree_key key, void* value);
btree_child btree_search(btree* bt, btree_key key);
void dump_keys(btree_node* btn, int depth);
void dump_values(btree* bt);

#endif
