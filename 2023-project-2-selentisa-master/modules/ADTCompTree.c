#include "ADTCompTree.h"
#include "ADTRecTree.h"
#include <stdlib.h>



struct comp_tree {
    RecTree h_tree;
};


CompTree comp_tree_create(Pointer value, RecTree left, RecTree right, CompareFunc compare) {
    CompTree tree = malloc(sizeof(*tree));
    tree->h_tree = rectree_create(value, left, right);
    return tree;
}


int comp_tree_size(CompTree tree) {
    return rectree_size(tree->h_tree);
}


void comp_tree_destroy(CompTree tree) {
    rectree_destroy(tree->h_tree);
    free(tree);
}


Pointer comptree_value(CompTree tree){
    return rectree_value(tree->h_tree);
}

CompTree comptree_left(CompTree tree){
    if (tree->h_tree == REC_TREE_EMPTY) {
        return NULL;
    }
    CompTree left = malloc(sizeof(*left));
    left->h_tree = rectree_left(tree->h_tree);
    return left;
}

CompTree comptree_right(CompTree tree){
    if (tree->h_tree == REC_TREE_EMPTY) {
        return NULL;
    }
    CompTree right = malloc(sizeof(*right));
    right->h_tree = rectree_right(tree->h_tree);
    return right;
}

Pointer comptree_value(CompTree tree){
    return rectree_value(tree->h_tree);
}


CompTree comptree_insert_last(CompTree tree, Pointer value) {
    if (tree->h_tree == REC_TREE_EMPTY) {
        return comp_tree_create(value, REC_TREE_EMPTY, REC_TREE_EMPTY, NULL);
    }
    int size = comp_tree_size(tree);
    int pos = size + 1;
    RecTree subtree = rectree_create(value, REC_TREE_EMPTY, REC_TREE_EMPTY);
    tree->h_tree = rectree_replace_subtree(tree->h_tree, pos, subtree);
    return tree;
}


CompTree comptree_remove_last(CompTree tree) {
    if (tree->h_tree == REC_TREE_EMPTY) {
        return NULL;
    }
    int size = comp_tree_size(tree);
    int pos = size;
    tree->h_tree = rectree_replace_subtree(tree->h_tree, pos, REC_TREE_EMPTY);
    return tree;
}