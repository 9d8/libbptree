#include "filebpt.h"
#include <stdio.h>
#include <stdlib.h>
#include "keycmp.h"
#include "membpt.h"

#define KEY_COUNT_OFFSET 0
#define LEAF_BOOL_OFFSET sizeof(KEY_COUNT)
#define KEYS_OFFSET (LEAF_BOOL_OFFSET + sizeof(BPT_BOOL))
#define CHILDREN_OFFSET (KEYS_OFFSET + sizeof(bptree_key)*MAX_KEYS)

/* This must be equal to the size of */
#define CHUNK_SIZE 1

static bptree_addr create_leaf_node(bptree* bpt);
static bptree_node* fbpt_get_node(bptree* bpt, bptree_addr naddr);
static KEY_COUNT fbpt_key_count(bptree* bpt, bptree_addr addr);
static BPT_BOOL fbpt_is_leaf(bptree* bpt, bptree_addr addr);
static bptree_key fbpt_get_child_key(bptree* bpt, bptree_addr addr, int index);
static bptree_addr fbpt_get_child_addr(bptree* bpt, bptree_addr addr, int index);
static void fbpt_delete_node(bptree* bpt, bptree_addr btn);
static void fbpt_write_node(bptree* bpt, bptree_addr addr, bptree_node* btn);
static void fbpt_close_node(bptree_node* btn);

bptree* bptree_fbpt_create(FILE* datafile) {
	bptree* fbpt = malloc(sizeof(bptree));
	fbpt->tree_head_fpos = ftell(datafile);
	
	bptree_addr free_fpos = { .node_fpos = EOF };
	fwrite(&free_fpos, sizeof(free_fpos), 1, datafile);

	bptree_addr root_address; 
	root_address.node_fpos = fbpt->tree_head_fpos + 2 * sizeof(bptree_addr);
	fwrite(&root_address, sizeof(bptree_addr), 1, datafile);

	fbpt->key_compare = bptree_keycmp_int;
	fbpt->create_node = create_leaf_node;
	fbpt->get_node = fbpt_get_node;
	fbpt->key_count = fbpt_key_count;
	fbpt->is_leaf = fbpt_is_leaf;
	fbpt->get_child_key = fbpt_get_child_key;
	fbpt->get_child_addr = fbpt_get_child_addr;
	fbpt->delete_node = fbpt_delete_node;
	fbpt->write_node = fbpt_write_node;
	fbpt->close_node = fbpt_close_node;
	
	fbpt->fp = datafile;
	fbpt->root = create_leaf_node(fbpt);

	return fbpt;
}

bptree* bptree_fbpt_load(FILE* datafile) {
	bptree* fbpt = malloc(sizeof(bptree));
	fbpt->tree_head_fpos = ftell(datafile);
	
	fseek(datafile, sizeof(bptree_addr), SEEK_CUR);
	fread(&fbpt->root, sizeof(bptree_addr), 1, datafile);

	fbpt->key_compare = bptree_keycmp_int;
	fbpt->create_node = create_leaf_node;
	fbpt->get_node = fbpt_get_node;
	fbpt->key_count = fbpt_key_count;
	fbpt->is_leaf = fbpt_is_leaf;
	fbpt->get_child_key = fbpt_get_child_key;
	fbpt->get_child_addr = fbpt_get_child_addr;
	fbpt->delete_node = fbpt_delete_node;
	fbpt->write_node = fbpt_write_node;
	fbpt->close_node = fbpt_close_node;
	
	fbpt->fp = datafile;

	return fbpt;
}

/* We dont actually need to destroy much since all nodes should be freed from
 * memory automatically. */
void bptree_fbpt_destroy(bptree* fbpt) {
	fseek(fbpt->fp, fbpt->tree_head_fpos + sizeof(bptree_addr), SEEK_SET);
	fwrite(&fbpt->root, sizeof(bptree_addr), 1, fbpt->fp);
	free(fbpt);
}

bptree_addr create_leaf_node(bptree* bpt) {
	/* Maybe a freopen is better here for portability...but probably slower. */
	fseek(bpt->fp, 0, SEEK_END);
	bptree_addr addr = { .node_fpos = ftell(bpt->fp) };
	
	/* Write key_count = 0 to file. */
	KEY_COUNT kc = 0;
	fwrite(&kc, sizeof(KEY_COUNT), 1, bpt->fp);
	/* Write is_leaf = 1 to file. */
	BPT_BOOL is_leaf = 1;
	fwrite(&is_leaf, sizeof(BPT_BOOL), 1, bpt->fp);
	/* Write garbage data to file. Im not sure that this is a good idea. */
	bptree_child garbage[ORDER];	
	/* The pointer child for leaf nodes needs to be EOF by default in order for 
	 * the linked list of leaf nodes to end. It cannot be NULL or 0 since that 
	 * is an actual position in the file. */
	garbage[0].addr.node_fpos = EOF;
	fwrite(garbage, sizeof(bptree_key), MAX_KEYS, bpt->fp);
	fwrite(garbage, sizeof(bptree_child), ORDER, bpt->fp);

	return addr;
}

bptree_node* fbpt_get_node(bptree* bpt, bptree_addr addr) {
	bptree_node* btn = NULL;
	
	if(addr.node_fpos != EOF) {
		btn = malloc(sizeof(bptree_node));
		fseek(bpt->fp, addr.node_fpos, SEEK_SET);
		
		fread(&btn->key_count, sizeof(KEY_COUNT), 1, bpt->fp);
		fread(&btn->is_leaf, sizeof(BPT_BOOL), 1, bpt->fp);
		fread(btn->keys, sizeof(bptree_key), MAX_KEYS, bpt->fp);
		fread(btn->children, sizeof(bptree_child), btn->key_count + 1, bpt->fp);
	}

	return btn;
}

KEY_COUNT fbpt_key_count(bptree* bpt, bptree_addr addr) {
	KEY_COUNT kc;
	fseek(bpt->fp, addr.node_fpos + KEY_COUNT_OFFSET, SEEK_SET);
	fread(&kc, sizeof(KEY_COUNT), 1, bpt->fp);
	return kc;
}

BPT_BOOL fbpt_is_leaf(bptree* bpt, bptree_addr addr) {
	BPT_BOOL is_leaf;
	fseek(bpt->fp, addr.node_fpos + LEAF_BOOL_OFFSET, SEEK_SET);
	fread(&is_leaf, sizeof(BPT_BOOL), 1, bpt->fp);
	return is_leaf;
}

bptree_key fbpt_get_child_key(bptree* bpt, bptree_addr addr, int index) {
	bptree_key key;
	fseek(bpt->fp, addr.node_fpos + KEYS_OFFSET + index*sizeof(bptree_key), SEEK_SET);
	fread(&key, sizeof(bptree_key), 1, bpt->fp);
	return key;
}

bptree_addr fbpt_get_child_addr(bptree* bpt, bptree_addr addr, int index) {
	bptree_addr child_addr;
	fseek(bpt->fp, addr.node_fpos + CHILDREN_OFFSET + index*sizeof(bptree_addr), SEEK_SET);
	fread(&child_addr, sizeof(bptree_addr), 1, bpt->fp);
	return child_addr;
}

void fbpt_delete_node(bptree* bpt, bptree_addr btn) {

}

void fbpt_write_node(bptree* bpt, bptree_addr addr, bptree_node* btn) {
	fseek(bpt->fp, addr.node_fpos, SEEK_SET);

	fwrite(&btn->key_count, sizeof(btn->key_count), 1, bpt->fp);
	fwrite(&btn->is_leaf, sizeof(btn->is_leaf), 1, bpt->fp);
	fwrite(btn->keys, sizeof(bptree_key), MAX_KEYS, bpt->fp);
	fwrite(btn->children, sizeof(bptree_child), btn->key_count + 1, bpt->fp);
}

void fbpt_close_node(bptree_node* btn) {
	free(btn);
}

bptree_addr get_chunk(bptree* bpt) {
	

	fseek(bpt->fp, 0, SEEK_END);
	bptree_addr chunk_addr = { .node_fpos = ftell(bpt->fp) };

	char garbage[CHUNK_SIZE];
	fwrite(garbage, CHUNK_SIZE, 1, bpt->fp);

	return chunk_addr;
}
