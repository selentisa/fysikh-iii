#include "ADTCompTree.h"
#include "ADTRecTree.h"
#include <stdlib.h>



struct comp_tree {
    Pointer value;
    RecTree rec_tree;
};

CompTree comptree_create(Pointer value, CompTree left, CompTree right) {
    CompTree tree = malloc(sizeof(struct comp_tree));
    tree->value = value;
    tree->rec_tree = rectree_create(value, left ? left->rec_tree : REC_TREE_EMPTY, right ? right->rec_tree : REC_TREE_EMPTY);
    return tree;
}

int comptree_size(CompTree tree) {
    return rectree_size(tree->rec_tree);
}

void comptree_destroy(CompTree tree) {
    rectree_destroy(tree->rec_tree);
    free(tree);
}

Pointer comptree_value(CompTree tree) {
    return rectree_value(tree->rec_tree);
}

CompTree comptree_left(CompTree tree) {
    CompTree left = malloc(sizeof(struct comp_tree));
    left->value = rectree_value(rectree_left(tree->rec_tree));
    left->rec_tree = rectree_left(tree->rec_tree);
    return left;
}

CompTree comptree_right(CompTree tree) {
    CompTree right = malloc(sizeof(struct comp_tree));
    right->value = rectree_value(rectree_right(tree->rec_tree));
    right->rec_tree = rectree_right(tree->rec_tree);
    return right;
}

CompTree comptree_insert_last(CompTree tree, Pointer value) {
    int size = comptree_size(tree);
    int pos = size;
    RecTree subtree = comptree_get_subtree(tree, pos);
    RecTree newSubtree = rectree_create(value, REC_TREE_EMPTY, REC_TREE_EMPTY);
    RecTree updatedTree = rectree_replace_subtree(tree->rec_tree, pos, newSubtree);
    comptree_destroy(tree);
    CompTree newTree = malloc(sizeof(struct comp_tree));
    newTree->value = rectree_value(updatedTree);
    newTree->rec_tree = updatedTree;
    return newTree;
}

CompTree comptree_remove_last(CompTree tree) {
    int size = comptree_size(tree);
    int pos = size - 1;
    RecTree updatedTree = rectree_replace_subtree(tree->rec_tree, pos, REC_TREE_EMPTY);
    comptree_destroy(tree);
    CompTree newTree = malloc(sizeof(struct comp_tree));
    newTree->value = rectree_value(updatedTree);
    newTree->rec_tree = updatedTree;
    return newTree;
}

RecTree comptree_get_subtree(CompTree tree, int pos) {
    return rectree_get_subtree(tree->rec_tree, pos);
}

CompTree comptree_replace_subtree(CompTree tree, int pos, CompTree subtree) {
    RecTree newSubtree = subtree ? subtree->rec_tree : REC_TREE_EMPTY;
    RecTree updatedTree = rectree_replace_subtree(tree->rec_tree, pos, newSubtree);
    CompTree newTree = malloc(sizeof(struct comp_tree));
    newTree->value = rectree_value(updatedTree);
    newTree->rec_tree = updatedTree;
    return newTree;
}
