#include <stdio.h>
#include "bptree.h"
#include "test.h"

void insert_test(bptree* bt);
void delete_test(bptree* bt);
void string_test(bptree* bpt);

int main(int argc, char** argv) {
	bptree* bt = bptree_membpt_create();
	string_test(bt);
	//test_run();
	//delete_test(bt);
	//insert_test(bt);
	bptree_membpt_destroy(bt);
	return 0;
}

void insert_test(bptree* bt) {
	char* test = "test";
	char* test2 = "test2";
	char* test3 = "test3";
	char* test4 = "test4";
	char* jojo = "jojo";
	bptree_insert(bt, ((bptree_key)1), test);
	bptree_insert(bt, ((bptree_key)4), test2);
	bptree_insert(bt, ((bptree_key)5), test3);
	bptree_insert(bt, ((bptree_key)11), jojo);
	bptree_insert(bt, ((bptree_key)2), test);
	bptree_insert(bt, ((bptree_key)7), test4);
	bptree_insert(bt, ((bptree_key)9), test4);
	bptree_insert(bt, ((bptree_key)27), test4);
	bptree_insert(bt, ((bptree_key)3), test4);
	bptree_insert(bt, ((bptree_key)6), test4);
	bptree_insert(bt, ((bptree_key)101), test3);
//	bptree_insert(bt, ((bptree_key)600), test4);
//	bptree_insert(bt, ((bptree_key)77), test2);
//	bptree_insert(bt, ((bptree_key)32), test4);
//	bptree_insert(bt, ((bptree_key)85), test4);
//	bptree_insert(bt, ((bptree_key)99), test4);
	printf("--------------------\n");
	dump_keys(bt, bt->root);
	printf("--------------------\n");
	dump_values(bt);
	printf("--------------------\n");
	char* found = bptree_search(bt, ((bptree_key)11));
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
	dump_keys(bt->root);
	printf("--------------------\n");
	
	bptree_delete(bt, ((bptree_key)965));
	bptree_delete(bt, ((bptree_key)378));

	dump_keys(bt->root);

	bptree_delete(bt, ((bptree_key)952));

	dump_keys(bt->root);
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
