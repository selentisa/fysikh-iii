
#include <stdlib.h>

#include "ADTVector.h"
#include "ADTList.h"
#include "ADTSet.h"
#include "state.h"
#include "common_types.h"


// Οι ολοκληρωμένες πληροφορίες της κατάστασης του παιχνιδιού.
// Ο τύπος State είναι pointer σε αυτό το struct, αλλά το ίδιο το struct
// δεν είναι ορατό στον χρήστη.

struct state {
	Vector objects;			// περιέχει στοιχεία Object (Πλατφόρμες, Αστέρια)
	struct state_info info;	// Γενικές πληροφορίες για την κατάσταση του παιχνιδιού
	float speed_factor;		// Πολλαπλασιαστής ταχύτητς (1 = κανονική ταχύτητα, 2 = διπλάσια, κλπ)
};


// Δημιουργεί και επιστρέφει ένα αντικείμενο

static Object create_object(ObjectType type, float x, float y, float width, float height, VerticalMovement vert_mov, float speed, bool unstable) {
	Object obj = malloc(sizeof(*obj));
	obj->type = type;
	obj->rect.x = x;
	obj->rect.y = y;
	obj->rect.width = width;
	obj->rect.height = height;
	obj->vert_mov = vert_mov;
	obj->vert_speed = speed;
	obj->unstable = unstable;
	return obj;
}

// Προσθέτει αντικείμενα στην πίστα (η οποία μπορεί να περιέχει ήδη αντικείμενα).
// Τα αντικείμενα ξεκινάνε από x = start_x, και επεκτείνονται προς τα δεξιά.
//
// ΠΡΟΣΟΧΗ: όλα τα αντικείμενα έχουν συντεταγμένες x,y σε ένα
// καρτεσιανό επίπεδο.
// - Στο άξονα x το 0 είναι η αρχή της πίστας και οι συντεταγμένες
//   μεγαλώνουν προς τα δεξιά.
//
// - Στον άξονα y το 0 είναι το πάνω μέρος της πίστας, και οι συντεταγμένες μεγαλώνουν
//   προς τα _κάτω_. Η πίστα έχει σταθερό ύψος, οπότε όλες οι
//   συντεταγμένες y είναι ανάμεσα στο 0 και το SCREEN_HEIGHT.
//
// Πέρα από τις συντεταγμένες, αποθηκεύουμε και τις διαστάσεις width,height
// κάθε αντικειμένου. Τα x,y,width,height ορίζουν ένα παραλληλόγραμμο, οπότε
// μπορούν να αποθηκευτούν όλα μαζί στο obj->rect τύπου Rectangle (ορίζεται
// στο include/raylib.h). Τα x,y αναφέρονται στην πάνω-αριστερά γωνία του Rectangle.

static void add_objects(State state, float start_x) {
	// Προσθέτουμε PLATFORM_NUM πλατφόρμες, με τυχαία χαρακτηριστικά.

	for (int i = 0; i < PLATFORM_NUM; i++) {
		Object platform = create_object(
			PLATFORM,
			start_x + 150 + rand() % 80,						// x με τυχαία απόσταση από το προηγούμενο στο διάστημα [150, 230]
			SCREEN_HEIGHT/4 + rand() % SCREEN_HEIGHT/2,			// y τυχαία στο διάστημα [SCREEN_HEIGHT/4, 3*SCREEN_HEIGHT/4]
			i == 0 ? 250 : 50 + rand()%200,						// πλάτος τυχαία στο διάστημα [50, 250] (η πρώτη πάντα 250)
			20,													// ύψος
			i < 3 || rand() % 2 == 0 ? MOVING_UP : MOVING_DOWN,	// τυχαία αρχική κίνηση (οι πρώτες 3 πάντα πάνω)
			0.6 + 3*(rand()%100)/100,							// ταχύτητα τυχαία στο διάστημα [0.6, 3.6]
			i > 0 && (rand() % 10) == 0							// το 10% (τυχαία) των πλατφορμών είναι ασταθείς (εκτός από την πρώτη)
		);
		vector_insert_last(state->objects, platform);

		// Στο 50% των πλατφορμών (τυχαία), εκτός της πρώτης, προσθέτουμε αστέρι
		if(i != 0 && rand() % 2 == 0) {
			Object star = create_object(
				STAR,
				start_x + 200 + rand() % 60,				// x με τυχαία απόσταση από την προηγούμενη πλατφόρμα στο διάστημα [200,260]
				SCREEN_HEIGHT/8 + rand() % SCREEN_HEIGHT/2,	// y τυχαία στο διάστημα [SCREEN_HEIGHT/8, 5*SCREEN_HEIGHT/8]
				30, 30,										// πλάτος, ύψος
				IDLE,										// χωρίς κίνηση
				0,										 	// ταχύτητα 0
				false										// 'unstable' πάντα false για τα αστέρια
			);
			vector_insert_last(state->objects, star);
		}

		start_x = platform->rect.x + platform->rect.width;	// μετακίνηση των επόμενων αντικειμένων προς τα δεξιά
	}
}

// Δημιουργεί και επιστρέφει την αρχική κατάσταση του παιχνιδιού

State state_create() {
	// Δημιουργία του state
	State state = malloc(sizeof(*state));

	// Γενικές πληροφορίες
	state->info.playing = true;				// Το παιχνίδι ξεκινάει αμέσως
	state->info.paused = false;				// Χωρίς να είναι paused.
	state->speed_factor = 1;				// Κανονική ταχύτητα
	state->info.score = 0;				// Αρχικό σκορ 0

	// Δημιουργούμε το vector των αντικειμένων, και προσθέτουμε αντικείμενα
	// ξεκινώντας από start_x = 0.
	state->objects = vector_create(0, NULL);
	add_objects(state, 0);

	// Δημιουργούμε την μπάλα τοποθετώντας τη πάνω στην πρώτη πλατφόρμα
	Object first_platform = vector_get_at(state->objects, 0);
	state->info.ball = create_object(
		BALL,
		first_platform->rect.x,			// x στην αρχή της πλατφόρμας
		first_platform->rect.y - 40,	// y πάνω στην πλατφόρμα
		45, 45,							// πλάτος, ύψος
		IDLE,							// χωρίς αρχική κατακόρυφη κίνηση
		0,								// αρχική ταχύτητα 0
		false							// "unstable" πάντα false για την μπάλα
	);

	return state;
}

// Επιστρέφει τις βασικές πληροφορίες του παιχνιδιού στην κατάσταση state

StateInfo state_info(State state) {
	// Προς υλοποίηση
	// Προσοχή: η συνάρτηση δεν πρέπει να επιστρέφει την δομή state->info, αλλά
	// ένα αντίγραφο της, γιατί η δομή StateInfo είναι private.
	StateInfo info = malloc(sizeof(*info));
	info->playing = state->info.playing;
	info->paused = state->info.paused;
	info->score = state->info.score;
	info->ball = state->info.ball;
	return info;

}

// Επιστρέφει μια λίστα με όλα τα αντικείμενα του παιχνιδιού στην κατάσταση state,
// των οποίων η συντεταγμένη x είναι ανάμεσα στο x_from και x_to.

List state_objects(State state, float x_from, float x_to) {
	// Προς υλοποίηση
	List list = list_create(NULL);
	for (int i = 0; i < vector_size(state->objects); i++) {
		Object obj = vector_get_at(state->objects, i);
		if (obj->rect.x >= x_from && obj->rect.x <= x_to) {
			list_insert_next(list, list_last(list), obj);
		}
	}
	return list;
}

// Ενημερώνει την κατάσταση state του παιχνιδιού μετά την πάροδο 1 frame.
// Το keys περιέχει τα πλήκτρα τα οποία ήταν πατημένα κατά το frame αυτό.

void state_update(State state, KeyState keys) {
	// Προς υλοποίηση
	// Αν το παιχνίδι δεν παίζεται, δεν υπάρχει καμία ανανέωση
	if (!state->info.playing) {
		return;
	}

	// Αν το παιχνίδι είναι paused, δεν υπάρχει καμία ανανέωση
	if (state->info.paused) {
		return;
	}

	//Αν το παιχνίδι έχει τελειώσει και πατηθεί enter, τότε ξαναρχίζει από την αρχή.
	if(keys->enter==true && state->info.playing==false){
		state_destroy(state);
		state = state_create();
	}

	// Αν το παιχνίδι είναι σε pause και πατηθεί n απο τα keys τότε ενημερώνεται για μόνο 1 frame (χρήσιμο για debugging).
	if(keys->n==true && state->info.paused==true){
		state->info.paused=false;
	}

	//Αν πατηθεί P το παιχνίδι μπαίνει σε pause και δεν ενημερώνεται πλέον.
	if(keys->p==true){
		state->info.paused=true;
	}



	// Αν είναι πατημένο το δεξί ή αριστερό βέλος τότε η κίνηση είναι 6 ή 1 pixels αντίστοιχα.
	if(keys->right==true){
		state->info.ball->rect.x += 6; 
	}

	//Αν το πλήκτρο αριστερά είναι πατημένο τότε η κίνηση είναι 1 pixel.
	if(keys->left==true){
		state->info.ball->rect.x -= 1;
	}




	if(keys->up==true){

	//Κατακόρυφη κίνηση μπάλας ανάλογα με τον τύπο κίνησης στον οποία βρίσκεται (vert_mov):
	//Αν βρίσκεται σε ηρεμία (IDLE):
	//Αν είναι πατημένο το πάνω βέλος μπαίνει σε κατάσταση άλματος με αρχική ταχύτητα 17.

	if(state->info.ball->vert_mov == IDLE){
		state->info.ball->vert_mov = JUMPING;
		state->info.ball->vert_speed = 17;
		state->info.ball->rect.y += state->info.ball->vert_speed;  //Μετακινείται προς τα πάνω τόσα pixels όσα η κατακόρυφη ταχύτητά της.
	}

	//Αν βρίσκεται σε κατάσταση άλματος (JUMPING):
	//Μετακινείται προς τα πάνω τόσα pixels όσα η κατακόρυφη ταχύτητά της.
	//Η ταχύτητα μειώνετα στο 85% της προηγούμενης τιμής.
	//Αν η ταχύτητα (που μειώνεται κατά το άλμα) φτάσει το 0.5 τότε μπαίνει σε κατάσταση πτώσης (FALLING)

	if(state->info.ball->vert_mov == JUMPING){
		state->info.ball->rect.y += state->info.ball->vert_speed; // Μετακινείται προς επάνω τόσα pixels όσα και η κατακόρυφη ταχύτητά της.
		state->info.ball->vert_speed *= 0.85; 
		if(state->info.ball->vert_speed < 0.5){
			state->info.ball->vert_mov = FALLING;
		}
	}

	//Αν βρίσκεται σε πτώση (FALLING):
	//Μετακινείτα προς τα κάτω τόσα pixels όσα η κατακόρυφη ταχύτητά της.
	//Η ταχήτητα αυξάνεται κατά 10%, με μέγιστο το 7.

	if(state->info.ball->vert_mov == FALLING){
		state->info.ball->rect.y -= state->info.ball->vert_speed; 
		state->info.ball->vert_speed *= 1.1;
		if(state->info.ball->vert_speed > 7){
			state->info.ball->vert_speed = 7;
		}
	}
	}


	//Αν η μπάλα φτάσει στο κάτω μέρος της οθόνης τερματίζει το παιχνίδι λαμβανοντας υποψη το ScreenHeight
	if(state->info.ball->rect.y > SCREEN_HEIGHT){
		state->info.playing = false;
	}





	/*Κατακόρυφη κίνηση πλατφόρμας ανάλογα με τον τύπο κίνησης στον οποία βρίσκεται (vert_mov):

		Αν κινείται προς τα πάνω (MOVING_UP):
		Μετακινείται προς τα πάνω τόσα pixels όσα η κατακόρυφη ταχύτητά της.
		Αν περάσει το SCREEN_HEIGHT/4 αλλάζει σε MOVING_DOWN
		Αν κινείται προς τα κάτω (MOVING_DOWN):
		Μετακινείται προς τα κάτω τόσα pixels όσα η κατακόρυφη ταχύτητά της.
		Αν περάσει τo 3*SCREEN_HEIGHT/4 αλλάζει σε MOVING_UP
		Αν βρίσκεται σε πτώση (FALLING):
		Μετακινείται προς τα κάτω 4 pixels */
 
	// Αναζήτηση σε όλα τα Objects του state
	for (int i = 0; i < vector_size(state->objects); i++) {

	Object obj = vector_get_at(state->objects, i);
	if(obj->type == PLATFORM){




	if(state->info.ball->vert_mov == IDLE){
		
	}








	if(obj->vert_mov == MOVING_UP){
		obj->rect.y -= obj->vert_speed;
		if(obj->rect.y < SCREEN_HEIGHT/4){
			obj->vert_mov = MOVING_DOWN;
		}
	}

	if(obj->vert_mov == MOVING_DOWN){
		obj->rect.y += obj->vert_speed;
		if(obj->rect.y > 3*SCREEN_HEIGHT/4){
			obj->vert_mov = MOVING_UP;
		}
	}

	if(obj->vert_mov == FALLING){
		obj->rect.y += 4;
	}
	}
	}

}

// Καταστρέφει την κατάσταση state ελευθερώνοντας τη δεσμευμένη μνήμη.

void state_destroy(State state) {
	// Προς υλοποίηση
	free(state->info.ball);
	free(state);
}


Pointer set_find_eq_or_greater(Set set, Pointer value){

    
    if (set_find_node(set, value) != SET_EOF){
		return set_node_value(set, set_find_node(set, value));
	} 
    else {
        set_insert(set, value);
        SetNode node = set_find_node(set,value);
        SetNode last = set_last(set);
        if(set_node_value(set,node) != set_node_value(set,last)){
            SetNode greaterNode = set_next(set, node);
            set_remove(set,value);
            return set_node_value(set,greaterNode);
        }
        else{
            set_remove(set,value);
            return NULL;
        }
        
    }

}


// Επιστρέφει την μοναδική τιμή του set που είναι ισοδύναμη με value,
// ή αν δεν υπάρχει, την μεγαλύτερη τιμή του set που είναι μικρότερη
// από value. Αν δεν υπάρχει καμία τότε επιστρέφει NULL.

Pointer set_find_eq_or_smaller(Set set, Pointer value){

    if (set_find_node(set, value) != SET_EOF) return set_node_value(set, set_find_node(set, value));
    else {
        set_insert(set, value);
        SetNode node = set_find_node(set,value);
        SetNode first = set_first(set);
        if(set_node_value(set,node) != set_node_value(set,first)){
            SetNode lessNode = set_previous(set, node);
            set_remove(set,value);
            return set_node_value(set,lessNode);
        }
        else{
            set_remove(set,value);
            return NULL;
        }
        
    }
}