

#include "ADTRecTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ADTMap.h"


// Επιστρέφει το υποδέντρο του tree στη θέση pos. Η αρίθμηση των θέσεων ξεκινάει
// από το 0 (ρίζα) και κινείται κατά επίπεδα, τα παιδιά της ρίζας έχουν θέση 1
// και 2, τα δικά τους παιδιά έχουν θέσεις 3,4,5,6, κλπ. Αν το υποδέντρο δεν
// υπάρχει θα επιστρέφεται REC_TREE_EMPTY. 

RecTree rectree_get_subtree(RecTree tree, int pos){
    if(tree == REC_TREE_EMPTY){
        return REC_TREE_EMPTY;
    }
    if(pos == 0){
        return tree;
    }
    if(pos%2 == 1){
        return rectree_get_subtree(rectree_left(tree), (pos-1)/2);
    }
    else{
        return rectree_get_subtree(rectree_right(tree), (pos-2)/2);
    }
}

// Δημιουργεί και επιστρέφει ένα νέο δέντρο, το οποίο προκύπτει αντικαθιστώντας
// το υποδέντρο του tree στη θέση pos με το subtree που δίνεται.  Η θέση pos
// πρέπει να αντιστοιχεί είτε σε υπάρχον κόμβο (που αντικαθίσταται), είτε στο
// κενό παιδί ενός υπάρχοντος κόμβου (οπότε προστίθεται εκεί το subtree).  Αν το
// subtree τοποθετείται στη ρίζα (pos == 0) τότε επιστρέφεται το ίδιο το subtree.
//
// Η συνάρτηση καταστρέφει αυτόματα τόσο το παλιό υποδέντρο που αντικαθίσταται
// (αν υπάρχει), καθώς και όλους τους προγόνους του που μεταβάλλονται (οπότε
// ξαναδημιουργούνται).

RecTree temp_right;
RecTree temp_left;

RecTree rectree_replace_subtree(RecTree tree, int pos, RecTree subtree){
    if(tree == REC_TREE_EMPTY){
        return subtree;
    }
    if(pos == 0){
        if(temp_right != NULL){
            rectree_destroy(temp_right);
        }
        // rectree_destroy(tree);
        // return subtree;
    }
    if(pos%2 == 1){
        if((pos-1)==0){
            temp_right = rectree_right(tree);
        }
         rectree_replace_subtree(rectree_left(tree), (pos-1)/2, subtree);
    }
    else{
        if((pos-2)==0){
            temp_left = rectree_right(tree);
        }
        rectree_replace_subtree(rectree_right(tree), (pos-2)/2, subtree);
    }
    return tree;
}