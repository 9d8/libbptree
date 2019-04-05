#ifndef FILEBPT_H_
#define FILEBPT_H_

#include "bptree_struct.h"

bptree* bptree_fbpt_create(FILE* datafile);
bptree* bptree_fbpt_load(FILE* datafile);
void bptree_fbpt_destroy(bptree* fbpt);

#endif
