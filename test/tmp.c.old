#include <stdio.h>
#include "bptree.h"
#include "util/test.h"
#include <unistd.h>

void insert_test(bptree* bt);
void delete_test(bptree* bt);
void string_test(bptree* bpt);

int main(int argc, char** argv) {
	bptree* bt = bptree_membpt_create();

	char* nn = "hello world";
	
	if(access("bptree.file", F_OK)) {
		FILE* fp = fopen("bptree.file", "w+b");
		bptree* fbt = bptree_fbpt_create(fp);

		bptree_insert(fbt, (bptree_key)1, nn);
		bptree_insert(fbt, (bptree_key)9, nn);
		bptree_insert(fbt, (bptree_key)5, nn);
		dump_keys(fbt, fbt->root);
	} else {
		FILE* fp = fopen("bptree.file", "r+b");
		bptree* fbt = bptree_fbpt_load(fp);
		dump_keys(fbt, fbt->root);
	}
	
	
	//string_test(bt);
	//test_run();
	//delete_test(bt);
	//delete_test(fbt);
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
	
	bptree_insert(bt, (bptree_key)100, test);
	bptree_insert(bt, (bptree_key)944, test);
	bptree_insert(bt, (bptree_key)263, test);
	bptree_insert(bt, (bptree_key)500, test);
	bptree_insert(bt, (bptree_key)275, test);
	bptree_insert(bt, (bptree_key)545, test);
	bptree_insert(bt, (bptree_key)728, test);
	bptree_insert(bt, (bptree_key)682, test);
	bptree_insert(bt, (bptree_key)521, test);
	bptree_insert(bt, (bptree_key)671, test);
	bptree_insert(bt, (bptree_key)339, test);
	bptree_insert(bt, (bptree_key)579, test);
	bptree_insert(bt, (bptree_key)629, test);
	bptree_insert(bt, (bptree_key)496, test);
	bptree_insert(bt, (bptree_key)862, test);
	bptree_insert(bt, (bptree_key)624, test);
	bptree_insert(bt, (bptree_key)844, test);
	bptree_insert(bt, (bptree_key)716, test);
	bptree_insert(bt, (bptree_key)78, test);
	bptree_insert(bt, (bptree_key)44, test);
	bptree_insert(bt, (bptree_key)76, test);
	bptree_insert(bt, (bptree_key)145, test);
	bptree_insert(bt, (bptree_key)150, test);
	bptree_insert(bt, (bptree_key)148, test);
	bptree_insert(bt, (bptree_key)663, test);
	bptree_insert(bt, (bptree_key)17, test);
	bptree_insert(bt, (bptree_key)307, test);
	bptree_insert(bt, (bptree_key)707, test);
	bptree_insert(bt, (bptree_key)978, test);
	bptree_insert(bt, (bptree_key)867, test);
	bptree_insert(bt, (bptree_key)126, test);
	bptree_insert(bt, (bptree_key)684, test);
	bptree_insert(bt, (bptree_key)898, test);
	bptree_insert(bt, (bptree_key)202, test);
	bptree_insert(bt, (bptree_key)714, test);
	bptree_insert(bt, (bptree_key)637, test);
	bptree_insert(bt, (bptree_key)470, test);
	bptree_insert(bt, (bptree_key)342, test);
	bptree_insert(bt, (bptree_key)13, test);
	bptree_insert(bt, (bptree_key)538, test);
	bptree_insert(bt, (bptree_key)349, test);
	bptree_insert(bt, (bptree_key)345, test);
	bptree_insert(bt, (bptree_key)812, test);
	bptree_insert(bt, (bptree_key)298, test);
	bptree_insert(bt, (bptree_key)272, test);
	bptree_insert(bt, (bptree_key)471, test);
	bptree_insert(bt, (bptree_key)353, test);
	bptree_insert(bt, (bptree_key)506, test);
	bptree_insert(bt, (bptree_key)826, test);
	bptree_insert(bt, (bptree_key)928, test);
	bptree_insert(bt, (bptree_key)543, test);
	bptree_insert(bt, (bptree_key)57, test);
	bptree_insert(bt, (bptree_key)946, test);
	bptree_insert(bt, (bptree_key)873, test);
	bptree_insert(bt, (bptree_key)491, test);
	bptree_insert(bt, (bptree_key)303, test);
	bptree_insert(bt, (bptree_key)975, test);
	bptree_insert(bt, (bptree_key)959, test);
	bptree_insert(bt, (bptree_key)269, test);
	bptree_insert(bt, (bptree_key)805, test);
	bptree_insert(bt, (bptree_key)757, test);
	bptree_insert(bt, (bptree_key)921, test);
	bptree_insert(bt, (bptree_key)247, test);
	bptree_insert(bt, (bptree_key)178, test);
	bptree_insert(bt, (bptree_key)367, test);
	bptree_insert(bt, (bptree_key)352, test);
	bptree_insert(bt, (bptree_key)518, test);
	bptree_insert(bt, (bptree_key)789, test);
	bptree_insert(bt, (bptree_key)268, test);
	bptree_insert(bt, (bptree_key)973, test);
	bptree_insert(bt, (bptree_key)619, test);
	bptree_insert(bt, (bptree_key)665, test);
	bptree_insert(bt, (bptree_key)494, test);
	bptree_insert(bt, (bptree_key)47, test);
	bptree_insert(bt, (bptree_key)73, test);
	bptree_insert(bt, (bptree_key)198, test);
	bptree_insert(bt, (bptree_key)205, test);
	bptree_insert(bt, (bptree_key)977, test);
	bptree_insert(bt, (bptree_key)207, test);
	bptree_insert(bt, (bptree_key)843, test);
	bptree_insert(bt, (bptree_key)815, test);
	bptree_insert(bt, (bptree_key)387, test);
	bptree_insert(bt, (bptree_key)50, test);

	printf("--------------------\n");
	dump_keys(bt, bt->root);
	printf("--------------------\n");
	
	bptree_delete(bt, ((bptree_key)198));

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
