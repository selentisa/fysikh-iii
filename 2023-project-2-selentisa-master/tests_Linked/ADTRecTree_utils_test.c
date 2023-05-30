//////////////////////////////////////////////////////////////////
//
// Unit tests για τον ADT Priority Queue.
// Οποιαδήποτε υλοποίηση οφείλει να περνάει όλα τα tests.
//
//////////////////////////////////////////////////////////////////

#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing

#include "ADTRecTree.h"
#include <stdio.h>



// θέτει τα στοιχεία του πίνακα array  σε τυχαία σειρά
void shuffle(int* array[], int size) {
	for (int i = 0; i < size; i++) {
		int new_pos = i + rand() / (RAND_MAX / (size - i) + 1);
		int* temp = array[new_pos];
		array[new_pos] = array[i];
		array[i] = temp;
	}
}

// Επιστρέφει έναν ακέραιο σε νέα μνήμη με τιμή value
int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

// int compare_ints(Pointer a, Pointer b) {
// 	return *(int*)a - *(int*)b;
// }

void test_create(void) {

	// Create a sample tree
    RecTree leftChild = rectree_create((int*)5, NULL, NULL);
	
	TEST_ASSERT(leftChild != NULL);
    RecTree rightChild = rectree_create((int*)16, NULL, NULL);
	TEST_ASSERT(rightChild != NULL);
	
    RecTree root = rectree_create((int*)3, leftChild, rightChild);
	TEST_ASSERT(root != NULL);



    // Test rectree_size
    int size = rectree_size(root);
	TEST_ASSERT(size == 3);


    // Test rectree_value, rectree_left, and rectree_right

	TEST_ASSERT(rectree_value(root) == (int*)3);

	TEST_ASSERT(rectree_value(rectree_left(root)) == (int*)5);

	TEST_ASSERT(rectree_value(rectree_right(root)) == (int*)16);

    //printf("rectree_value(rectree_right(root)) %d \n ", (int)rectree_value(rectree_right(root)));


    // Test rectree_get_subtree
    RecTree subtree = rectree_get_subtree(root, 0);
    TEST_ASSERT(subtree != NULL);
    TEST_ASSERT(rectree_value(subtree) == (int*)3);


    // Test rectree_replace_subtree
    RecTree newSubtree = rectree_create((int*)7, NULL, NULL);
    RecTree replacedSubtree = rectree_replace_subtree(root, 1, newSubtree);
    TEST_ASSERT(rectree_value(replacedSubtree) == (int*)3);


    TEST_ASSERT(rectree_value(rectree_left(replacedSubtree)) == (int*)7 );
    TEST_ASSERT(rectree_value(rectree_right(replacedSubtree)) == (int*)16 );
    TEST_ASSERT(rectree_size(replacedSubtree) == 3);
    

    // Test rectree_destroy
    rectree_destroy(replacedSubtree);


}	

void test_insert(void) {

}

void test_remove(void) {
	

}


// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{ "adtRecTree_Linked", test_create },

	{ NULL} // τερματίζουμε τη λίστα με NULL
};