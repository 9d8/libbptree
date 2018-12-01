#include <stdio.h>
#include "bptree.h"
#include "test.h"

void insert_test(bptree* bt);
void delete_test(bptree* bt);
void string_test(bptree* bpt);

int main(int argc, char** argv) {
	bptree* bt = bptree_membpt_create();
	//FILE* fp = fopen("bptree.file", "w+b");
	//bptree* fbt = bptree_fbpt_create(fp);
	//string_test(bt);
	test_run();
	//delete_test(bt);
	//insert_test(bt);
	//insert_test(fbt);
	
	bptree_membpt_destroy(bt);
	return 0;
}

void insert_test(bptree* bt) {
	char* test = "test";
	char* test2 = "test2";
	char* test3 = "test3";
	char* test4 = "test4";
	char* jojo = "jojo";
	
	bptree_insert(bt, (bptree_key)26, test);
	bptree_insert(bt, (bptree_key)900, test);
	bptree_insert(bt, (bptree_key)775, test);
	bptree_insert(bt, (bptree_key)999, test);
	dump_keys(bt, bt->root);
	bptree_insert(bt, (bptree_key)693, test);
	dump_keys(bt, bt->root);
	bptree_insert(bt, (bptree_key)974, test);
	bptree_insert(bt, (bptree_key)891, test);
	bptree_insert(bt, (bptree_key)745, test);
	bptree_insert(bt, (bptree_key)165, test);
	bptree_insert(bt, (bptree_key)628, jojo);
	bptree_insert(bt, (bptree_key)684, test);
	bptree_insert(bt, (bptree_key)57, test);
	bptree_insert(bt, (bptree_key)168, test);
	bptree_insert(bt, (bptree_key)267, test);
	bptree_insert(bt, (bptree_key)6, test);
	bptree_insert(bt, (bptree_key)167, test);
	bptree_insert(bt, (bptree_key)104, test);
	bptree_insert(bt, (bptree_key)722, test);
	bptree_insert(bt, (bptree_key)602, test);
	bptree_insert(bt, (bptree_key)846, test);
	bptree_insert(bt, (bptree_key)736, test);
	bptree_insert(bt, (bptree_key)543, test);
	bptree_insert(bt, (bptree_key)991, test);
	bptree_insert(bt, (bptree_key)87, test);
	bptree_insert(bt, (bptree_key)742, test);
	bptree_insert(bt, (bptree_key)60, test);
	bptree_insert(bt, (bptree_key)556, test);
	
	printf("--------------------\n");
	dump_keys(bt, bt->root);
	printf("--------------------\n");
	dump_values(bt);
	printf("--------------------\n");
	char* found = bptree_search(bt, ((bptree_key)628));
	printf("%s's bizzare adventure\n", found);
}

#ifndef DISABLE_DELETE

void delete_test(bptree* bt) {
	char* test = "test";

	bptree_insert(bt, ((bptree_key)0), test);
	bptree_insert(bt, ((bptree_key)912), test);
	bptree_insert(bt, ((bptree_key)138), test);
	bptree_insert(bt, ((bptree_key)718), test);
	bptree_insert(bt, ((bptree_key)213), test);
	bptree_insert(bt, ((bptree_key)916), test);
	bptree_insert(bt, ((bptree_key)905), test);
	bptree_insert(bt, ((bptree_key)358), test);
	bptree_insert(bt, ((bptree_key)241), test);
	bptree_insert(bt, ((bptree_key)54), test);
	bptree_insert(bt, ((bptree_key)942), test);
	bptree_insert(bt, ((bptree_key)716), test);
	bptree_insert(bt, ((bptree_key)736), test);
	bptree_insert(bt, ((bptree_key)704), test);
	bptree_insert(bt, ((bptree_key)869), test);
	bptree_insert(bt, ((bptree_key)681), test);
	bptree_insert(bt, ((bptree_key)798), test);
	bptree_insert(bt, ((bptree_key)885), test);
	bptree_insert(bt, ((bptree_key)770), test);
	bptree_insert(bt, ((bptree_key)791), test);
	bptree_insert(bt, ((bptree_key)461), test);
	bptree_insert(bt, ((bptree_key)383), test);
	bptree_insert(bt, ((bptree_key)354), test);
	bptree_insert(bt, ((bptree_key)373), test);
	bptree_insert(bt, ((bptree_key)867), test);
	bptree_insert(bt, ((bptree_key)804), test);
	bptree_insert(bt, ((bptree_key)546), test);
	bptree_insert(bt, ((bptree_key)454), test);
	bptree_insert(bt, ((bptree_key)570), test);
	bptree_insert(bt, ((bptree_key)826), test);
	bptree_insert(bt, ((bptree_key)809), test);
	bptree_insert(bt, ((bptree_key)549), test);
	bptree_insert(bt, ((bptree_key)931), test);
	bptree_insert(bt, ((bptree_key)443), test);
	bptree_insert(bt, ((bptree_key)378), test);
	bptree_insert(bt, ((bptree_key)663), test);
	bptree_insert(bt, ((bptree_key)730), test);
	bptree_insert(bt, ((bptree_key)970), test);
	bptree_insert(bt, ((bptree_key)860), test);
	bptree_insert(bt, ((bptree_key)543), test);
	bptree_insert(bt, ((bptree_key)43), test);
	bptree_insert(bt, ((bptree_key)160), test);
	bptree_insert(bt, ((bptree_key)839), test);
	bptree_insert(bt, ((bptree_key)141), test);
	bptree_insert(bt, ((bptree_key)548), test);
	bptree_insert(bt, ((bptree_key)929), test);
	bptree_insert(bt, ((bptree_key)952), test);
	bptree_insert(bt, ((bptree_key)91), test);
	bptree_insert(bt, ((bptree_key)190), test);
	bptree_insert(bt, ((bptree_key)965), test);
	bptree_insert(bt, ((bptree_key)375), test);

	printf("--------------------\n");
	dump_keys(bt, bt->root);
	printf("--------------------\n");
	
	bptree_delete(bt, ((bptree_key)965));
	bptree_delete(bt, ((bptree_key)378));

	dump_keys(bt, bt->root);

	bptree_delete(bt, ((bptree_key)952));

	dump_keys(bt, bt->root);
}

#endif


void string_test(bptree* bpt) {
	bptree_insert(bpt, ((bptree_key)"key1"), "data");
	bptree_insert(bpt, ((bptree_key)"key2"), "data");
	bptree_insert(bpt, ((bptree_key)"key3"), "data");
	bptree_insert(bpt, ((bptree_key)"key4"), "data");
	bptree_insert(bpt, ((bptree_key)"bazinga"), "cr");
	bptree_insert(bpt, ((bptree_key)"key"), "data");
	bptree_insert(bpt, ((bptree_key)"key5"), "data");
	bptree_insert(bpt, ((bptree_key)"this is a password"), "data a");
	bptree_insert(bpt, ((bptree_key)"key entry"), "data");
	bptree_insert(bpt, ((bptree_key)"i'm hungry"), "food");

	char* food = bptree_search(bpt, ((bptree_key)"i'm hungry"));
	char* password = bptree_search(bpt, ((bptree_key)"this is a password"));
	char* bazinga = bptree_search(bpt, ((bptree_key)"bazinga"));

	printf("%s %s %s\n", food, password, bazinga);
}
