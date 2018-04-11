#include "btree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	btree_key key;
	btree_child	nodes[2];
} key_children;

typedef struct {
	int left;
	btree_node* node;
} node_sibling;

void destroy_nodes(btree_node* btn);
key_children* leaf_insert(btree_node* btn, btree_key key, btree_child value);
key_children* node_insert(btree_node* btn, btree_key key, btree_child value);
int leaf_delete(btree_node* btn, btree_key key, node_sibling* sib);
int node_delete(btree_node* btn, btree_key key, node_sibling* sib);
btree_child node_search(btree_node* btni, btree_key key);
btree_key key_array_insert(btree_key* arr, btree_key value, int num, size_t size, int* index);
btree_node* create_leaf_node();

btree* btree_create(btree_type key_type) {
	btree* bt = malloc(sizeof(btree));	
	bt->key_type = key_type;
	bt->root = create_leaf_node();
	bt->root->children[0].node = NULL;
	return bt;
}

void btree_destroy(btree* bt) {
	destroy_nodes(bt->root);
	free(bt);
}

void destroy_nodes(btree_node* btn) {
	if(!btn->is_leaf) {
		for(int i = 0; i < btn->key_count + 1; i++) {
			destroy_nodes(btn->children[i].node);
		}
	}
	free(btn);
}

void btree_insert(btree* bt, btree_key key, void* value) {
	btree_child btree_value = { .data = value };
	key_children* child_node_data;
	if((child_node_data = leaf_insert(bt->root, key, btree_value)) != NULL) {
		bt->root = create_leaf_node();
		bt->root->children[0] = child_node_data->nodes[0]; 
		bt->root->is_leaf = 0;
		node_insert(bt->root, child_node_data->key, child_node_data->nodes[1]);
		free(child_node_data);
	}
}

key_children* leaf_insert(btree_node* btn, btree_key key, btree_child value) {
	key_children* insert = NULL;

	if(!btn->is_leaf) {
		int i;
		for(i = 0; i < btn->key_count && key >= btn->keys[i]; i++);
		if((insert = leaf_insert(btn->children[i].node, key, value)) != NULL) {
			btree_child right = insert->nodes[1];
			key_children* insert_buff = node_insert(btn, insert->key, right);
			free(insert);
			insert = insert_buff;
		}
	} else {
		insert = node_insert(btn, key, value);
	}

	return insert;
}

key_children* node_insert(btree_node* btn, btree_key key, btree_child value) {
	int insert_index;
	if(btn->key_count < 4) {
		key_array_insert(btn->keys, key, btn->key_count, sizeof(btree_key)*4, &insert_index);
		//insert child in correct spot
		memmove(btn->children + insert_index + 2, btn->children + insert_index + 1, sizeof(btree_child)*(btn->key_count - insert_index));
		btn->children[insert_index + 1] = value;
		//
		btn->key_count++;
	} else {
		btree_key largest_key = key_array_insert(btn->keys, key, 4, sizeof(btree_key)*4, &insert_index);
		btree_child largest_key_value = btn->children[4];

		//insert children and store last value
		if(insert_index < 4) {
			memmove(btn->children + insert_index + 2, btn->children + insert_index + 1, sizeof(btree_child)*(3 - insert_index));
			btn->children[insert_index + 1] = value;
		} else {
			largest_key_value = value;
		}
		
		//turning btn into left node
		btree_node* left_node = btn;
		btree_node* right_node = create_leaf_node();
		btree_key right_key = btn->keys[2];

		//if splitting non-leaf, dont keep middle key and set is_leaf to false
		if(btn->is_leaf) {
			memcpy(right_node->keys, left_node->keys + 2, sizeof(btree_key)*2);
			memcpy(right_node->children + 1, left_node->children + 3, sizeof(btree_child)*2);
			right_node->keys[2] = largest_key;
			right_node->children[3] = largest_key_value;
			right_node->key_count = 3;
			//link node to next node
			right_node->children[0] = left_node->children[0];
			left_node->children[0].node = right_node;
		} else {
			memcpy(right_node->keys, left_node->keys + 3, sizeof(btree_key));
			memcpy(right_node->children, left_node->children + 3, sizeof(btree_child)*2);
			right_node->keys[1] = largest_key;
			right_node->children[2] = largest_key_value;
			right_node->key_count = 2;
			right_node->is_leaf = 0;
		}
		left_node->key_count = 2;

		key_children* left_right_nodes = malloc(sizeof(key_children));
		left_right_nodes->key = right_key;
		left_right_nodes->nodes[0].node = left_node;
		left_right_nodes->nodes[1].node = right_node;
		return left_right_nodes;
	}
	return NULL;
}

void btree_delete(btree* bt, btree_key key) {
	leaf_delete(bt->root, key, NULL);	
}

//WARNING: this does not account for children yet
int leaf_delete(btree_node* btn, btree_key key, node_sibling* sib) {
	int delete_code = 0;

	if(!btn->is_leaf) {
		int i;
		for(i = 0; i < btn->key_count && key >= btn->keys[i]; i++);
		//sibling to be modified when child merges or steals
		node_sibling sibdata = {1,NULL};
		if(i == 0) {
			sibdata.left = 0;
			sibdata.node = btn->children[i+1].node;	
		} else if(i == btn->key_count) {
			sibdata.node = btn->children[i-1].node;	
		} else {
			btree_node* left_sib = btn->children[i-1].node;
			btree_node* right_sib = btn->children[i+1].node;
			if(left_sib->key_count >= right_sib->key_count || (left_sib->key_count <= 2 && right_sib->key_count <= 2)) {
				sibdata.node = left_sib;
			} else {
				sibdata.left = 0;
				sibdata.node = right_sib;
			}
		}

		//i != 1 for overwrite since rightmost child has no left parent
		btree_node* child = btn->children[i].node;
		if((delete_code = leaf_delete(child, key, &sibdata)) == 1 && i != 0) {
			//overwrite left parent
			//i-1 since i equals child index, not key index
			btn->keys[i-1] = child->keys[0];
		} else if(delete_code == 2) {
			if(i == 0) {
				//be wary of this
				i++;
			}
			if(sibdata.left) {
				btn->keys[i-1] = child->keys[0];
			} else {
				btn->keys[i-1] = sibdata.node->keys[0];
			}
		}
	} else {
		delete_code = node_delete(btn, key, sib);
	}	

	return delete_code;
}

//return codes:
//	0 - Do nothing
//	1 - Normal delete + need to overwrite left parent key
//	2 - Steal occured
//	3 - Merge occured
int node_delete(btree_node* btn, btree_key key, node_sibling* sib) {
	int code = 0;
	if(btn->key_count >= 3) {
		int i;
		for(i = 0; i < btn->key_count && key != btn->keys[i]; i++);
		memmove(btn->keys + i, btn->keys + i + 1, sizeof(btree_child)*(btn->key_count - i - 1));
		btn->key_count--;
		if(i == 0) {
			code = 1;
		}
	//steal
	} else if(sib != NULL && sib->node->key_count >= 3) {
		//delete key
		int i;
		for(i = 0; i < btn->key_count && key != btn->keys[i]; i++);
		memmove(btn->keys + i, btn->keys + i + 1, sizeof(btree_child)*(btn->key_count - i - 1));
		btree_key sibkey;
		btree_child sibchild;
		if(sib->left) {
			sibkey = sib->node->keys[sib->node->key_count-1];
			sibchild = sib->node->children[sib->node->key_count];
		} else {
			sibkey = sib->node->keys[0];
			sibchild = sib->node->children[1];
		}
		//this is necessary for node_insert to work properly
		btn->key_count--;
		//careful: make sure child doesnt get deallocated by node_delete when deleteing sib->node
		node_insert(btn, sibkey, sibchild);
		node_delete(sib->node, sibkey, NULL);
		code = 2;
	//merge
	} else {

	}

	return code;
}

btree_child btree_search(btree* bt, btree_key key) {
	return node_search(bt->root, key);
}

btree_child node_search(btree_node* btn, btree_key key) {
	btree_child value = { NULL };

	if(!btn->is_leaf) {
		int i;
		for(i =	0; i < btn->key_count && key >= btn->keys[i]; i++);
		value = node_search(btn->children[i].node, key);
	} else {
		int i;
		for(i =	0; i < btn->key_count && key != btn->keys[i]; i++);
		if(i != btn->key_count) {
			return btn->children[i + 1];
		}
	}

	return value;
}

void dump_keys(btree_node* btn, int depth) {
	for(int i = 0; i < btn->key_count; i++) {
		printf("%d:%s ", btn->keys[i], btn->children[i + 1].data);
	}
	
	printf("\n");
	
	if(!btn->is_leaf && depth > 0) {
		for(int i = 0; i < btn->key_count + 1; i++) {
			dump_keys(btn->children[i].node, depth - 1);
		}
	}
}

void dump_values(btree* bt) {
	btree_node* node = bt->root;
	while(!node->is_leaf) {
		node = node->children[0].node;
	}
	
	while(node != NULL) {
		for(int i = 0; i < node->key_count; i++) {
			printf("%s ", node->children[i + 1].data);
		}
		node = node->children[0].node;
	}

	printf("\n");
}

btree_key key_array_insert(btree_key* arr, btree_key value, int num, size_t size, int* index) {
	int length = size/sizeof(btree_key);
	btree_key last = arr[num - 1];
	int i;
	for(i = 0; i < num; i++) {
		if(value < arr[i]) {
			//prevent buffer overflows.
			//since loop breaks, we can modify num.
			if(num == length) num--;
			memmove(arr + i + 1, arr + i, sizeof(btree_key)*(num - i));
			break;
		}
	}
	if(i < length) {
		arr[i] = value;
	} else {
		last = value;
	}

	if(index != NULL) {
		*index = i;
	}
	return last;
}

int key_compare(btree_key* key1, btree_key* key2) {
	return (key1 > key2);
}

btree_node* create_leaf_node() {
	btree_node* btn = malloc(sizeof(btree_node));
	btn->key_count = 0;
	btn->is_leaf = 1;
	return btn;
}
