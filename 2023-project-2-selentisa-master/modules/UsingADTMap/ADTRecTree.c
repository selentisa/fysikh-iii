
#include <stdlib.h>
#include "ADTMap.h"
#include "ADTRecTree.h"


Map RecLeft;
Map RecRight;
Map RecValues;
int tree_index=0;

    return *(int*)a - *(int*)b;
}



//  Ένα δέντρο είναι pointer σε αυτό το struct
struct rec_tree {
	Pointer value;
	RecTree left;
	RecTree right;

};

// Δημιουργεί και επιστρέφει ένα νέο δέντρο, με τιμή (στη ρίζα) value και υποδέντρα left και right.

RecTree rectree_create(Pointer value, RecTree left, RecTree right){
    // Δημιουργούμε ένα καινούριο map την πρώτη φορά που καλείται η rectree_create
    if(RecValues == NULL){
        RecLeft = map_create(compare_ints, NULL, NULL);
        RecRight = map_create(compare_ints, NULL, NULL);
        RecValues = map_create(compare_ints, NULL, NULL);
        tree_index=1;
    }
    else{
        tree_index++;
        map_insert(RecLeft, &tree_index, left);
        map_insert(RecRight, &tree_index, right);
        map_insert(RecValues, &tree_index, value);

    }

}

// Επιστρέφει τον αριθμό στοιχείων που περιέχει το δέντρο (0 για κενά δέντρα).

int rectree_size(RecTree tree);

// Ελευθερώνει τη μνήμη που δεσμεύει το δέντρο tree (ΔΕΝ καταστρέφει τα υποδέντρα του).

void rectree_destroy(RecTree tree);

// Επιστρέφουν την τιμή (στη ρίζα), το αριστερό και το δεξί υποδέντρο του δέντρου tree.

Pointer rectree_value(RecTree tree);
RecTree rectree_left(RecTree tree);
RecTree rectree_right(RecTree tree);

