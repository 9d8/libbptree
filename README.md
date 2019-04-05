# libbptree
libbptree is a library for creating general use [B+ Trees](https://en.wikipedia.org/wiki/B%2B_tree).

This program is very experimental and has only been tested a limited amount of times (by me). Thus, I do not reccommend using this library at all for the time being.

# Features
As this program is still in development, many of the planned features are unimplemented or only partially implemented.

Available features:
* Create an order 5 B+ Tree that 
* Create persistent (file stored) B+ Trees
* Use integer values as keys
* Tree insertion/deletion/searching
* Obtain a key sorted linked list of all elements in the tree

Planned features:
* Create b+ tree of any order (currently limited to an order of 5)
* Use any datatype as a key
* Ability to store dynamically allocated memory (as of now children can only be pointers to some allocated memory)

# Simple usage
Here is some sample code that shows the basic functionality of this lib. A more in depth documentation is planned, but it does not exist yet.
```
	bptree* bpt = bptree_membpt_create();

	char* data = "hello";
	char* data2 = "world";
	char* data_misc = "misc";

	bptree_insert(bpt, (bptree_key)0, data);
	bptree_insert(bpt, (bptree_key)2, data2);
	bptree_insert(bpt, (bptree_key)3, data_misc);
	bptree_insert(bpt, (bptree_key)30, data_misc);
	bptree_insert(bpt, (bptree_key)80, data_misc);
	bptree_insert(bpt, (bptree_key)11, data_misc);
	bptree_insert(bpt, (bptree_key)66, data_misc);
	bptree_insert(bpt, (bptree_key)45, data_misc);
	bptree_insert(bpt, (bptree_key)12, data_misc);
	bptree_insert(bpt, (bptree_key)900, data_misc);
	bptree_insert(bpt, (bptree_key)4, data_misc);
	bptree_insert(bpt, (bptree_key)5, data_misc);
	bptree_insert(bpt, (bptree_key)10, data_misc);
	bptree_insert(bpt, (bptree_key)22, data_misc);
	
	bptree_delete(bpt, (bptree_key)4);

	char* result1 = bptree_search(bpt, (bptree_key)0);
	char* result2 = bptree_search(bpt, (bptree_key)2);
	if(result1 != NULL && result2 != NULL) {
		printf("%s %s\n", result1, result2);
	}
	
	bptree_membpt_destroy(bpt);
```
produces a bptree that looks like the following:
'''
5:- 11:- 30:- 66:- 
    0:hello 2:world 3:misc 
    5:misc 10:misc 
    11:misc 12:misc 22:misc 
    30:misc 45:misc 
    66:misc 80:misc 900:misc
'''
