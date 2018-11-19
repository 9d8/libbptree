#include "bptree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DELETE_CODE int
#define SHIFT_FORWARD(arr, len) memmove(arr + 1, arr, len)
#define SHIFT_BACK(arr, len) memmove(arr, arr + 1, len)

#define FIND_KEY(bpt, btn, key, i) \
	for(i = 0; i < btn->key_count && bpt->key_compare(key, btn->keys[i]) != 0; i++)
#define FIND_KEY_POS(bpt, btn, key, i) \
	for(i = 0; i < btn->key_count && bpt->key_compare(key, btn->keys[i]) >= 0; i++)

typedef struct {
	bptree_key key;
	bptree_child node;
} key_child;

typedef struct {
	int left;
	bptree_node* node;
} node_sibling;

static void destroy_nodes(bptree_node* btn);
static key_child* leaf_insert(bptree* bpt, bptree_node* btn, bptree_key key, bptree_child value);
static key_child* node_insert(bptree* bpt, bptree_node* btn, bptree_key key, bptree_child value);
static DELETE_CODE leaf_delete(bptree* bpt, bptree_node* btn, bptree_key key, node_sibling* sib);
static DELETE_CODE node_delete(bptree* bpt, bptree_node* btn, bptree_key key, node_sibling* sib);
static bptree_child node_search(bptree* bpt, bptree_addr naddr, bptree_key key);
static bptree_key min(bptree* bpt, bptree_addr naddr);
static bptree_key max(bptree* bpt, bptree_addr naddr);
static void dump_keys_aux(bptree* bpt, bptree_addr naddr, int depth);
static bptree_key key_array_insert(bptree* bpt, bptree_key* arr, bptree_key value, int num, size_t size, int* index);

void bptree_insert(bptree* bpt, bptree_key key, void* value) {
	bptree_child bptree_value = { .data = value };
	key_child* child_node_data;
	
	bptree_addr root_addr = bpt->root;
	bptree_node* root_node = BPTN_GET_NODE(bpt, bpt->root);
	
	if((child_node_data = leaf_insert(bpt, root_node, key, bptree_value)) != NULL) {
		bpt->root = BPTN_CREATE_NODE(bpt);
		bptree_node* new_root_node = BPTN_GET_NODE(bpt, bpt->root);
		
		new_root_node->children[0].addr = root_addr; 
		new_root_node->is_leaf = 0;
		node_insert(bpt, new_root_node, child_node_data->key, child_node_data->node);
	
		BPTN_SAVE_AND_CLOSE_NODE(bpt, bpt->root, new_root_node);
		
		free(child_node_data);
	}
	
	BPTN_SAVE_AND_CLOSE_NODE(bpt, root_addr, root_node);
}

key_child* leaf_insert(bptree* bpt, bptree_node* btn, bptree_key key, bptree_child value) {
	key_child* insert = NULL;

	if(!btn->is_leaf) {
		int i;
		//FIND_KEY_POS(bpt, btn, key, i);
		for(i = 0; i < btn->key_count && bpt->key_compare(key, btn->keys[i]) >= 0; i++);
		bptree_addr child_addr = btn->children[i].addr;
		bptree_node* child_node = BPTN_GET_NODE(bpt, child_addr);
		if((insert = leaf_insert(bpt, child_node, key, value)) != NULL) {
			bptree_child right = insert->node;
			key_child* insert_buff = node_insert(bpt, btn, insert->key, right);
			free(insert);
			insert = insert_buff;
		}
		BPTN_SAVE_AND_CLOSE_NODE(bpt, child_addr, child_node);
	} else {
		insert = node_insert(bpt, btn, key, value);
	}

	return insert;
}

key_child* node_insert(bptree* bpt, bptree_node* btn, bptree_key key, bptree_child value) {
	int insert_index;
	key_child* right_node_info = NULL;
	//bptree_node* btn = BPTN_GET_NODE(bpt, naddr);

	if(btn->key_count < MAX_KEYS) {
		key_array_insert(bpt, btn->keys, key, btn->key_count, sizeof(bptree_key)*MAX_KEYS, &insert_index);
		//insert child in correct spot
		SHIFT_FORWARD(btn->children + insert_index + 1, sizeof(bptree_child)*(btn->key_count - insert_index));
		btn->children[insert_index + 1] = value;
		//
		btn->key_count++;
	} else {
		bptree_key largest_key = key_array_insert(bpt, btn->keys, key, MAX_KEYS, sizeof(bptree_key)*MAX_KEYS, &insert_index);
		bptree_child largest_key_value = btn->children[MAX_KEYS];

		//insert children and store last value
		if(insert_index < MAX_KEYS) {
			SHIFT_FORWARD(btn->children + insert_index + 1, sizeof(bptree_child)*(MAX_KEYS - 1 - insert_index));
			btn->children[insert_index + 1] = value;
		} else {
			largest_key_value = value;
		}
		
		//turning btn into left node
		bptree_node* left_node = btn;
		
		bptree_addr right_addr = BPTN_CREATE_NODE(bpt);
		bptree_node* right_node = BPTN_GET_NODE(bpt, right_addr);
		bptree_key right_key = btn->keys[MAX_KEYS - MIN_KEYS];

		//if splitting non-leaf, dont keep middle key and set is_leaf to false
		if(btn->is_leaf) {
			memcpy(right_node->keys, left_node->keys + (MAX_KEYS - MIN_KEYS), sizeof(bptree_key)*MIN_KEYS);
			memcpy(right_node->children + 1, left_node->children + (MAX_KEYS - MIN_KEYS) + 1, sizeof(bptree_child)*MIN_KEYS);
			right_node->keys[MIN_KEYS] = largest_key;
			right_node->children[MIN_KEYS + 1] = largest_key_value;
			right_node->key_count = MIN_KEYS + 1;
			//link node to next node
			right_node->children[0] = left_node->children[0];
			left_node->children[0].addr = right_addr;
		} else {
			//EVEN BPTREE ERROR OCCURS SOMEWHERE IN THIS BLOCK
			memcpy(right_node->keys, left_node->keys + MIN_KEYS + 1, sizeof(bptree_key)*(MIN_KEYS - 1));
			memcpy(right_node->children, left_node->children + (MAX_KEYS - MIN_KEYS) + 1, sizeof(bptree_child)*MIN_KEYS);
			right_node->keys[MIN_KEYS - 1] = largest_key;
			right_node->children[MIN_KEYS] = largest_key_value;
			right_node->key_count = MIN_KEYS;
			right_node->is_leaf = 0;
		}
		left_node->key_count = MAX_KEYS - MIN_KEYS;
	
		BPTN_SAVE_AND_CLOSE_NODE(bpt, right_addr, right_node);

		right_node_info = malloc(sizeof(key_child));
		right_node_info->key = right_key;
		right_node_info->node.addr = right_addr;
	}
	
	return right_node_info;
}

#ifndef DISABLE_DELETE

void bptree_delete(bptree* bpt, bptree_key key) {
	leaf_delete(bpt, bpt->root, key, NULL);
	if(bpt->root->key_count == 0 && !bpt->root->is_leaf) {
		bptree_node* new_root = bpt->root->children[0].node_p;
		free(bpt->root);
		bpt->root = new_root;
	}
}

DELETE_CODE leaf_delete(bptree* bpt, bptree_node* btn, bptree_key key, node_sibling* sib) {
	DELETE_CODE di;

	if(!btn->is_leaf) {
		int i;
		for(i = 0; i < btn->key_count && bpt->key_compare(key, btn->keys[i]) >= 0; i++);
		//sibling to be modified when child merges or steals
		node_sibling sibdata = {1,NULL};
		if(i == 0) {
			sibdata.left = 0;
			sibdata.node = btn->children[i+1].node_p;	
		} else if(i == btn->key_count) {
			sibdata.node = btn->children[i-1].node_p;	
		} else {
			bptree_node* left_sib = btn->children[i-1].node_p;
			bptree_node* right_sib = btn->children[i+1].node_p;
			if(left_sib->key_count >= right_sib->key_count || (left_sib->key_count <= 2 && right_sib->key_count <= 2)) {
				sibdata.node = left_sib;
			} else {
				sibdata.left = 0;
				sibdata.node = right_sib;
			}
		}

		bptree_node* child = btn->children[i].node_p;
		di = leaf_delete(bpt, child, key, &sibdata);

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
				di = node_delete(bpt, btn, btn->keys[i-1], sib);
				if(di == 2 || i > btn->key_count) {
					i--;
				}
			} else {
				di = node_delete(bpt, btn, btn->keys[i], sib);
			}
			
			// On merge, child may not exist anymore. Thus do not use past this point
		}

		if(i != 0) {
			btn->keys[i-1] = min(btn->children[i].node_p);
		} else if(i == 0) {
			btn->keys[0] = min(btn->children[1].node_p);
		}	
	} else {
		//perhaps check if key does not exist and throw error
		di = node_delete(bpt, btn, key, sib);
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
DELETE_CODE node_delete(bptree* bpt, bptree_node* btn, bptree_key key, node_sibling* sib) {
	DELETE_CODE di = 0;
	int i;
	for(i = 0; i < btn->key_count && bpt->key_compare(key, btn->keys[i]) != 0; i++);

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
			node_insert(bpt, btn, sibkey, sibchild);
			node_delete(bpt, sib->node, sibkey, NULL);
		} else if(sib->left) {
			//dont need to worry about overflow since delete above garuntees room for shift.
			SHIFT_FORWARD(btn->keys, sizeof(bptree_key)*btn->key_count);
			SHIFT_FORWARD(btn->children, sizeof(bptree_child)*(btn->key_count+1));

			btn->keys[0] = sib->node->keys[sib->node->key_count-1];
			btn->children[0] = sib->node->children[sib->node->key_count];
			btn->key_count++;
			
			node_delete(bpt, sib->node, btn->keys[0], NULL);
		} else {
			node_insert(bpt, btn, sib->node->keys[0], sib->node->children[0]);	
			
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
			node_delete(bpt, btn, key, NULL);
			node_insert(bpt, merged, dead->keys[0],dead->children[1]);
			if(!sib->left) {
				node_insert(bpt, merged, dead->keys[1],dead->children[2]);
			}
		} else if(sib->left) {
			SHIFT_FORWARD(btn->children, sizeof(bptree_child)*(i + 1)); 
			dead->keys[0] = min(dead->children[1].node_p);
			dead->keys[1] = min(dead->children[2].node_p);
			node_insert(bpt, merged, dead->keys[0], dead->children[1]);
			node_insert(bpt, merged, dead->keys[1], dead->children[2]);
		} else {
			SHIFT_BACK(merged->children + i + 1, sizeof(bptree_child)*(merged->key_count - i - 1)); 
			
			merged->children[merged->key_count] = dead->children[0];
			
			merged->keys[merged->key_count - 1] = min(dead->children[0].node_p);
			node_insert(bpt, merged, dead->keys[0], dead->children[1]);
			node_insert(bpt, merged, dead->keys[1], dead->children[2]);
		}	

		free(dead);
		di = 3;
	}

	return di;
}

#endif

void* bptree_search(bptree* bpt, bptree_key key) {
	return node_search(bpt, bpt->root, key).data;
}

bptree_child node_search(bptree* bpt, bptree_addr naddr, bptree_key key) {
	bptree_node* btn = BPTN_GET_NODE(bpt, naddr);
	bptree_child value = { NULL };

	if(!btn->is_leaf) {
		int i;
		for(i =	0; i < btn->key_count && bpt->key_compare(key, btn->keys[i]) >= 0; i++);
		value = node_search(bpt, btn->children[i].addr, key);
	} else {
		int i;
		for(i =	0; i < btn->key_count && bpt->key_compare(key, btn->keys[i]) != 0; i++);
		if(i != btn->key_count) {
			return btn->children[i + 1];
		}
	}

	bpt->close_node(btn);
	return value;
}

bptree_key min(bptree* bpt, bptree_addr naddr) {
	bptree_addr addr = naddr;
	while(!BPTN_IS_LEAF(bpt, addr)) {
		addr = BPTN_GET_CHILD_ADDR(bpt, addr, 0);
	}
	return BPTN_GET_CHILD_KEY(bpt, addr, 0);
}

bptree_key max(bptree* bpt, bptree_addr naddr) {
	bptree_addr addr = naddr;
	int key_count = BPTN_KEY_COUNT(bpt, addr);

	while(!BPTN_IS_LEAF(bpt, addr)) {
		addr = BPTN_GET_CHILD_ADDR(bpt, addr, key_count);
	}
	return BPTN_GET_CHILD_KEY(bpt, addr, key_count - 1);
}

void dump_keys_aux(bptree* bpt, bptree_addr naddr, int depth) {
	bptree_node* btn = BPTN_GET_NODE(bpt, naddr);

	printf("%*s", depth*4, "");
	for(int i = 0; i < btn->key_count; i++) {
		printf("%d:%s ", btn->keys[i], btn->is_leaf? btn->children[i + 1].data: "-");
	}
	
	printf("\n");
	
	if(!btn->is_leaf) {
		for(int i = 0; i < btn->key_count + 1; i++) {
			dump_keys_aux(bpt, btn->children[i].addr, depth + 1);
		}
	}

	bpt->close_node(btn);
}

void dump_keys(bptree* bpt, bptree_addr naddr) {
	dump_keys_aux(bpt, naddr, 0);
}

void dump_values(bptree* bpt) {
	bptree_addr addr = bpt->root;
	while(!BPTN_IS_LEAF(bpt, addr)) {
		addr = BPTN_GET_CHILD_ADDR(bpt, addr, 0);
	}
	
	bptree_node* node = BPTN_GET_NODE(bpt, addr);
	
	while(node != NULL) {
		for(int i = 0; i < node->key_count; i++) {
			printf("%s ", node->children[i + 1].data);
		}
		bptree_addr next_addr = node->children[0].addr;
		BPTN_CLOSE_NODE(bpt, node);
		node = BPTN_GET_NODE(bpt, next_addr);
	}

	printf("\n");
}

bptree_key key_array_insert(bptree* bpt, bptree_key* arr, bptree_key value, int num, size_t size, int* index) {
	int length = size/sizeof(bptree_key);
	bptree_key last = arr[num - 1];
	int i;
	for(i = 0; i < num; i++) {
		if(bpt->key_compare(value, arr[i]) < 0) {
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
