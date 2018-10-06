#include "bptree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DELETE_CODE int
#define SHIFT_FORWARD(arr, len) memmove(arr + 1, arr, len)
#define SHIFT_BACK(arr, len) memmove(arr, arr + 1, len)

typedef struct {
	bptree_key key;
	bptree_child nodes[2];
} key_children;

typedef struct {
	int left;
	bptree_node* node;
} node_sibling;

void destroy_nodes(bptree_node* btn);
key_children* leaf_insert(bptree_node* btn, bptree_key key, bptree_child value);
key_children* node_insert(bptree_node* btn, bptree_key key, bptree_child value);
DELETE_CODE leaf_delete(bptree_node* btn, bptree_key key, node_sibling* sib);
DELETE_CODE node_delete(bptree_node* btn, bptree_key key, node_sibling* sib);
bptree_child node_search(bptree_node* btni, bptree_key key);
bptree_key min(bptree_node* btn);
bptree_key max(bptree_node* btn);
void dump_keys_aux(bptree_node* btn, int depth);
bptree_key key_array_insert(bptree_key* arr, bptree_key value, int num, size_t size, int* index);
bptree_node* create_leaf_node();

bptree* bptree_create(bptree_type key_type) {
	bptree* bt = malloc(sizeof(bptree));	
	bt->key_type = key_type;
	bt->root = create_leaf_node();
	bt->root->children[0].node = NULL;
	return bt;
}

void bptree_destroy(bptree* bt) {
	destroy_nodes(bt->root);
	free(bt);
}

void destroy_nodes(bptree_node* btn) {
	if(!btn->is_leaf) {
		for(int i = 0; i < btn->key_count + 1; i++) {
			destroy_nodes(btn->children[i].node);
		}
	}
	free(btn);
}

void bptree_insert(bptree* bt, bptree_key key, void* value) {
	bptree_child bptree_value = { .data = value };
	key_children* child_node_data;
	if((child_node_data = leaf_insert(bt->root, key, bptree_value)) != NULL) {
		bt->root = create_leaf_node();
		bt->root->children[0] = child_node_data->nodes[0]; 
		bt->root->is_leaf = 0;
		node_insert(bt->root, child_node_data->key, child_node_data->nodes[1]);
		free(child_node_data);
	}
}

key_children* leaf_insert(bptree_node* btn, bptree_key key, bptree_child value) {
	key_children* insert = NULL;

	if(!btn->is_leaf) {
		int i;
		for(i = 0; i < btn->key_count && key >= btn->keys[i]; i++);
		if((insert = leaf_insert(btn->children[i].node, key, value)) != NULL) {
			bptree_child right = insert->nodes[1];
			key_children* insert_buff = node_insert(btn, insert->key, right);
			free(insert);
			insert = insert_buff;
		}
	} else {
		insert = node_insert(btn, key, value);
	}

	return insert;
}

key_children* node_insert(bptree_node* btn, bptree_key key, bptree_child value) {
	int insert_index;
	if(btn->key_count < 4) {
		key_array_insert(btn->keys, key, btn->key_count, sizeof(bptree_key)*4, &insert_index);
		//insert child in correct spot
		SHIFT_FORWARD(btn->children + insert_index + 1, sizeof(bptree_child)*(btn->key_count - insert_index));
		btn->children[insert_index + 1] = value;
		//
		btn->key_count++;
	} else {
		bptree_key largest_key = key_array_insert(btn->keys, key, 4, sizeof(bptree_key)*4, &insert_index);
		bptree_child largest_key_value = btn->children[4];

		//insert children and store last value
		if(insert_index < 4) {
			SHIFT_FORWARD(btn->children + insert_index + 1, sizeof(bptree_child)*(3 - insert_index));
			btn->children[insert_index + 1] = value;
		} else {
			largest_key_value = value;
		}
		
		//turning btn into left node
		bptree_node* left_node = btn;
		bptree_node* right_node = create_leaf_node();
		bptree_key right_key = btn->keys[2];

		//if splitting non-leaf, dont keep middle key and set is_leaf to false
		if(btn->is_leaf) {
			memcpy(right_node->keys, left_node->keys + 2, sizeof(bptree_key)*2);
			memcpy(right_node->children + 1, left_node->children + 3, sizeof(bptree_child)*2);
			right_node->keys[2] = largest_key;
			right_node->children[3] = largest_key_value;
			right_node->key_count = 3;
			//link node to next node
			right_node->children[0] = left_node->children[0];
			left_node->children[0].node = right_node;
		} else {
			memcpy(right_node->keys, left_node->keys + 3, sizeof(bptree_key));
			memcpy(right_node->children, left_node->children + 3, sizeof(bptree_child)*2);
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

void bptree_delete(bptree* bt, bptree_key key) {
	leaf_delete(bt->root, key, NULL);
	if(bt->root->key_count == 0 && !bt->root->is_leaf) {
		bptree_node* new_root = bt->root->children[0].node;
		free(bt->root);
		bt->root = new_root;
	}
}

DELETE_CODE leaf_delete(bptree_node* btn, bptree_key key, node_sibling* sib) {
	DELETE_CODE di;

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
			bptree_node* left_sib = btn->children[i-1].node;
			bptree_node* right_sib = btn->children[i+1].node;
			if(left_sib->key_count >= right_sib->key_count || (left_sib->key_count <= 2 && right_sib->key_count <= 2)) {
				sibdata.node = left_sib;
			} else {
				sibdata.left = 0;
				sibdata.node = right_sib;
			}
		}

		bptree_node* child = btn->children[i].node;
		di = leaf_delete(child, key, &sibdata);

		if(di == -1) {
			return di;
		} else if(di == 1 && i != 0) {
			di = 0;
		} else if(di == 2) {
			// (!sibdata.left) == (i == 0)
			if(!sibdata.left) {
				child->keys[child->key_count-1] = btn->keys[i];
				btn->keys[i] = min(sibdata.node);
			}
			di = 0;
		} else if(di == 3) {
			if(sibdata.left) {
				di = node_delete(btn, btn->keys[i-1], sib);
				if(di == 2 || i > btn->key_count) {
					i--;
				}
			} else {
				di = node_delete(btn, btn->keys[i], sib);
			}
			
			// On merge, child may not exist anymore. Thus do not use past this point
		}

		if(i != 0) {
			btn->keys[i-1] = min(btn->children[i].node);
		} else if(i == 0) {
			btn->keys[0] = min(btn->children[1].node);
		}	
	} else {
		//perhaps check if key does not exist and throw error
		di = node_delete(btn, key, sib);
	}

	return di;
}

//return codes:
// -1 - Key not found
//	0 - Do nothing
//	1 - Normal delete + need to overwrite left parent key
//	2 - Steal occured
//	3 - Merge occured
//function assumes key exists. If it does not, bad things will happen.
DELETE_CODE node_delete(bptree_node* btn, bptree_key key, node_sibling* sib) {
	DELETE_CODE di = 0;
	int i;
	for(i = 0; i < btn->key_count && key != btn->keys[i]; i++);

	if(i == btn->key_count) {
		di = -1;	
	} else if(btn->key_count >= 3 || sib == NULL) {
		SHIFT_BACK(btn->keys + i, sizeof(bptree_key)*(btn->key_count - i - 1));
		SHIFT_BACK(btn->children + i + 1, sizeof(bptree_child)*(btn->key_count - i - 1));
		btn->key_count--;

		if(i == 0 && btn->is_leaf) {
			di = 1;
		}
	//steal
	} else if(sib->node->key_count >= 3) {
		//delete key
		SHIFT_BACK(btn->keys + i, sizeof(bptree_key)*(btn->key_count - i - 1));
		SHIFT_BACK(btn->children + i + 1, sizeof(bptree_child)*(btn->key_count - i - 1));
		
		//this is necessary for node_insert to work properly
		btn->key_count--;

		if(btn->is_leaf) {
			bptree_key sibkey;
			bptree_child sibchild;
			if(sib->left) {
				sibkey = sib->node->keys[sib->node->key_count-1];
				sibchild = sib->node->children[sib->node->key_count];
			} else {
				sibkey = sib->node->keys[0];
				sibchild = sib->node->children[1];
			}
			//careful: make sure child doesnt get deallocated by node_delete when deleteing sib->node
			node_insert(btn, sibkey, sibchild);
			node_delete(sib->node, sibkey, NULL);
		} else if(sib->left) {
			//dont need to worry about overflow since delete above garuntees room for shift.
			SHIFT_FORWARD(btn->keys, sizeof(bptree_key)*btn->key_count);
			SHIFT_FORWARD(btn->children, sizeof(bptree_child)*(btn->key_count+1));

			btn->keys[0] = sib->node->keys[sib->node->key_count-1];
			btn->children[0] = sib->node->children[sib->node->key_count];
			btn->key_count++;
			
			node_delete(sib->node, btn->keys[0], NULL);
		} else {
			node_insert(btn, sib->node->keys[0], sib->node->children[0]);	
			
			SHIFT_BACK(sib->node->keys, sizeof(bptree_key)*(sib->node->key_count - 1));
			SHIFT_BACK(sib->node->children, sizeof(bptree_child)*(sib->node->key_count));
			
			sib->node->key_count--;
		}
		
		di = 2;
	//merge
	} else {
		bptree_node* merged = sib->node;
		bptree_node* dead = btn;
		//always merge towards the left node.
		if(!sib->left) {
			merged = btn;
			dead = sib->node;
		}

		//could be 2 or 1...
		if(btn->is_leaf) {
			merged->children[0] = dead->children[0];
			node_delete(btn, key, NULL);
			node_insert(merged, dead->keys[0],dead->children[1]);
			if(!sib->left) {
				node_insert(merged, dead->keys[1],dead->children[2]);
			}
		} else if(sib->left) {
			SHIFT_FORWARD(btn->children, sizeof(bptree_child)*(i + 1)); 
			dead->keys[0] = min(dead->children[1].node);
			dead->keys[1] = min(dead->children[2].node);
			node_insert(merged, dead->keys[0], dead->children[1]);
			node_insert(merged, dead->keys[1], dead->children[2]);
		} else {
			SHIFT_BACK(merged->children + i + 1, sizeof(bptree_child)*(merged->key_count - i - 1)); 
			
			merged->children[merged->key_count] = dead->children[0];
			
			merged->keys[merged->key_count - 1] = min(dead->children[0].node);
			node_insert(merged, dead->keys[0], dead->children[1]);
			node_insert(merged, dead->keys[1], dead->children[2]);
		}	

		free(dead);
		di = 3;
	}

	return di;
}

bptree_child bptree_search(bptree* bt, bptree_key key) {
	return node_search(bt->root, key);
}

bptree_child node_search(bptree_node* btn, bptree_key key) {
	bptree_child value = { NULL };

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

bptree_key min(bptree_node* btn) {
	bptree_node* node = btn;
	while(!node->is_leaf) {
		node = node->children[0].node;
	}
	return node->keys[0];
}

bptree_key max(bptree_node* btn) {
	bptree_node* node = btn;
	while(!node->is_leaf) {
		node = node->children[node->key_count].node;
	}
	return node->keys[node->key_count - 1];
}

void dump_keys_aux(bptree_node* btn, int depth) {
	printf("%*s", depth*4, "");
	for(int i = 0; i < btn->key_count; i++) {
		printf("%d:%s ", btn->keys[i], btn->is_leaf? btn->children[i + 1].data: "-");
	}
	
	printf("\n");
	
	if(!btn->is_leaf) {
		for(int i = 0; i < btn->key_count + 1; i++) {
			dump_keys_aux(btn->children[i].node, depth + 1);
		}
	}
}

void dump_keys(bptree_node* btn) {
	dump_keys_aux(btn, 0);
}

void dump_values(bptree* bt) {
	bptree_node* node = bt->root;
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

bptree_key key_array_insert(bptree_key* arr, bptree_key value, int num, size_t size, int* index) {
	int length = size/sizeof(bptree_key);
	bptree_key last = arr[num - 1];
	int i;
	for(i = 0; i < num; i++) {
		if(value < arr[i]) {
			//prevent buffer overflows.
			//since loop breaks, we can modify num.
			if(num == length) num--;
			SHIFT_FORWARD(arr + i, sizeof(bptree_key)*(num - i));
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

int key_compare(bptree_key* key1, bptree_key* key2) {
	return (key1 > key2);
}

bptree_node* create_leaf_node() {
	bptree_node* btn = malloc(sizeof(bptree_node));
	btn->key_count = 0;
	btn->is_leaf = 1;
	return btn;
}