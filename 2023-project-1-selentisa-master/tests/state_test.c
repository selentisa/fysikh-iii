//////////////////////////////////////////////////////////////////
//
// Test για το state.h module
//
//////////////////////////////////////////////////////////////////

#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing

#include "state.h"
#include "ADTSet.h"
#include "set_utils.h"

#include <stdlib.h>
#include "common_types.h"


void test_state_create() {

	State state = state_create();
	TEST_ASSERT(state != NULL);

	StateInfo info = state_info(state);
	TEST_ASSERT(info != NULL);

	TEST_ASSERT(info->playing);
	TEST_ASSERT(!info->paused);
	TEST_ASSERT(info->score == 0);

	// Προσθέστε επιπλέον ελέγχους
}

void test_state_update() {
	State state = state_create();
	TEST_ASSERT(state != NULL && state_info(state) != NULL);

	// Πληροφορίες για τα πλήκτρα (αρχικά κανένα δεν είναι πατημένο)
	struct key_state keys = { false, false, false, false, false, false, false };
	
	// Χωρίς κανένα πλήκτρο, η μπάλα μετακινείται 4 pixels δεξιά
	Rectangle old_rect = state_info(state)->ball->rect;
	//state_update(state, &keys);
	Rectangle new_rect = state_info(state)->ball->rect;

	//TEST_ASSERT( new_rect.x == old_rect.x + 4 );

	// Με πατημένο το δεξί βέλος, η μπάλα μετακινείται 6 pixels δεξιά
	keys.right = true;
	old_rect = state_info(state)->ball->rect;
	state_update(state, &keys);
	new_rect = state_info(state)->ball->rect;

	TEST_CHECK( new_rect.x == old_rect.x + 6 );

	// Με πατημένο το αριστερό βέλος, η μπάλα μετακινείται 1 pixels αριστερά
	keys.right = false;
	keys.left = true;
	old_rect = state_info(state)->ball->rect;
	state_update(state, &keys);
	new_rect = state_info(state)->ball->rect;

	TEST_CHECK( new_rect.x == old_rect.x - 1 );


	// Με πατημένο το πάνω βέλος, 	//Κατακόρυφη κίνηση μπάλας ανάλογα με τον τύπο κίνησης στον οποία βρίσκεται (vert_mov):
	//Αν βρίσκεται σε ηρεμία (IDLE):
	//Αν είναι πατημένο το πάνω βέλος μπαίνει σε κατάσταση άλματος με αρχική ταχύτητα 17.
		//Αν βρίσκεται σε κατάσταση άλματος (JUMPING):
	//Μετακινείται προς τα πάνω τόσα pixels όσα η κατακόρυφη ταχύτητά της.
	//Η ταχύτητα μειώνετα στο 85% της προηγούμενης τιμής.
	//Αν η ταχύτητα (που μειώνεται κατά το άλμα) φτάσει το 0.5 τότε μπαίνει σε κατάσταση πτώσης (FALLING)

	keys.left = false;
	keys.up = true;
	old_rect = state_info(state)->ball->rect;
	state_update(state, &keys);
	new_rect = state_info(state)->ball->rect;


		
	


	// Προσθέστε επιπλέον ελέγχους
}

// Προσθέστε επιπλέον tests
// Δημιουργια test για set_utils.c για set_find_eq_or_greater και set_find_eq_or_less

int compare(Pointer a, Pointer b) {
    // Cast pointers to the correct data type
    Pointer num_a =  a;
    Pointer num_b =  b;

    if (num_a < num_b) {
        return -1; // a is less than b
    } else if (num_a > num_b) {
        return 1; // a is greater than b
    } else {
        return 0; // a and b are equivalent
    }
}

void test_set_utils() {
	// Δημιουργία συνόλου

	Set set = set_create((CompareFunc)compare, NULL);
	TEST_ASSERT(set != NULL);


	// Προσθήκη στοιχείων
	//
	set_insert(set, (int*)1);
	set_insert(set, (int*)2);
	set_insert(set, (int*)3);
	set_insert(set, (int*)4);
	set_insert(set, (int*)5);

	// Έλεγχος μεγέθους
	TEST_ASSERT(set_size(set) == 5);


	// Έλεγχος set_find_eq_or_greater for Pointer

	TEST_ASSERT(set_find_eq_or_greater(set, (int*)0) == (int*)1);
	TEST_ASSERT(set_find_eq_or_greater(set, (int*)1) == (int*)1);
	TEST_ASSERT(set_find_eq_or_greater(set, (int*)2) == (int*)2);
	TEST_ASSERT(set_find_eq_or_greater(set, (int*)6) == NULL);


}

// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{ "test_state_create", test_state_create },
	{ "test_state_update", test_state_update },
	{ "test_set_utils", test_set_utils },

	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};