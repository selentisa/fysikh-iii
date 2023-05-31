#pragma once // #include το πολύ μία φορά

#include "common_types.h"

// Η παρακάτω σταθερά συμβολίζει ένα κενό δέντρο
#define REC_TREE_EMPTY (RecTree)0

#include "ADTRecTree.h"

typedef struct comp_tree* CompTree;

CompTree comptree_create(Pointer value, CompTree left, CompTree right);
int comptree_size(CompTree tree);
void comptree_destroy(CompTree tree);
Pointer comptree_value(CompTree tree);
CompTree comptree_left(CompTree tree);
CompTree comptree_right(CompTree tree);
CompTree comptree_insert_last(CompTree tree, Pointer value);
CompTree comptree_remove_last(CompTree tree);
RecTree comptree_get_subtree(CompTree tree, int pos);
CompTree comptree_replace_subtree(CompTree tree, int pos, CompTree subtree);


