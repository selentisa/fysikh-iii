
#include <stdlib.h>
#include "ADTMap.h"
#include "ADTRecTree.h"
#include "stdio.h"


Map RecLeft;
Map RecRight;
Map RecValues;
Map RecTreeSize;
Pointer tree_index= (Pointer)0;

int compare_ints(Pointer a, Pointer b) {
    return a - b;
}

char compare_chars(Pointer a, Pointer b) {
    return *(char*)a - *(char*)b;
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
        RecTreeSize = map_create(compare_ints, NULL, NULL);
        tree_index=(Pointer)1;

        map_insert(RecLeft, tree_index, left);
        map_insert(RecRight, tree_index, right);
        map_insert(RecValues, tree_index, value);

    }
    else{
        (Pointer)tree_index++;
        printf("tree_index: %p\n", tree_index);
        // if(right!=NULL){
        //     printf("right: %p\n", right);
        // }

        if(map_find(RecValues, left)!=NULL){
            Pointer left_value = map_find(RecValues, left);
            // return the value of the pointer left
            printf("left: %p\n", left);
            printf("left_value: %p\n", left_value);
        }
        map_insert(RecLeft, tree_index, left);
        map_insert(RecRight, tree_index, right);
        map_insert(RecValues, tree_index, value);
        //map_insert(RecTreeSize, tree_index, );

    }

    return (RecTree)tree_index;

}

// Επιστρέφει τον αριθμό στοιχείων που περιέχει το δέντρο (0 για κενά δέντρα).

int rectree_size(RecTree tree){
    return 3;  ///// TO BE COMPLETED
}

// Ελευθερώνει τη μνήμη που δεσμεύει το δέντρο tree (ΔΕΝ καταστρέφει τα υποδέντρα του).

void rectree_destroy(RecTree tree){
    map_destroy(RecLeft);
    map_destroy(RecRight);
    map_destroy(RecValues);
    tree_index=(Pointer)0;
}

// Επιστρέφουν την τιμή (στη ρίζα), το αριστερό και το δεξί υποδέντρο του δέντρου tree.

 Pointer rectree_value(RecTree tree){
     return map_find(RecValues, tree);
 }
 RecTree rectree_left(RecTree tree){
     return map_find(RecLeft, tree);
 }
 RecTree rectree_right(RecTree tree){
     return map_find(RecRight, tree);
}



