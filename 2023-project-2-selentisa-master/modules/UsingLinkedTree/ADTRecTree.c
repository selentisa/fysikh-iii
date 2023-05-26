///////////////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT RecTree μέσω links
//
///////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "ADTRecTree.h"



// Προς υλοποίηση...


//  Ένα δέντρο είναι pointer σε αυτό το struct
struct rec_tree {
	Pointer value;
	RecTree left;
	RecTree right;

};


// Δημιουργεί και επιστρέφει ένα νέο δέντρο, με τιμή (στη ρίζα) value και υποδέντρα left και right.

RecTree rectree_create(Pointer value, RecTree left, RecTree right) {

	RecTree tree = malloc(sizeof(struct rec_tree));
	tree->value = value;
	tree->left = left;
	tree->right = right;
	return tree;

}

// Επιστρέφει τον αριθμό στοιχείων που περιέχει το δέντρο.

int rectree_size(RecTree tree) {
	if (tree == REC_TREE_EMPTY) {
		return 0;
	}
	return 1 + rectree_size(tree->left) + rectree_size(tree->right);
	
}

// Ελευθερώνει όλη τη μνήμη που δεσμεύει το δέντρο tree.

void rectree_destroy(RecTree tree) {

	if (tree == REC_TREE_EMPTY) {
		return;
	}
	rectree_destroy(tree->left);
	rectree_destroy(tree->right);
	free(tree);


}

// Επιστρέφουν την τιμή (στη ρίζα), το αριστερό και το δεξί υποδέντρο του δέντρου tree.

Pointer rectree_value(RecTree tree) {
	if(tree == REC_TREE_EMPTY)
		return NULL;
	return tree->value;

}

RecTree rectree_left(RecTree tree) {
	if (tree == REC_TREE_EMPTY) {
		return NULL;
	}
	return tree->left;
}

RecTree rectree_right(RecTree tree) {
	if (tree == REC_TREE_EMPTY) {
		return NULL;
	}
	return tree->right;

}

