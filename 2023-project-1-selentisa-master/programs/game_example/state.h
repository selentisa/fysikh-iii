#pragma once

#include "raylib.h"
#include "ADTList.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

// Λόγω της απλότητας του παιχνιδιού, όλες οι πληροφορίες
// είναι άμεσα ορατές στον χρήστη, χωρίς information hiding.

typedef struct ball {
	Vector2 position;
	int radius;
}* Ball;

typedef struct state {
	Rectangle character;				// θέση και μέγεθος του χαρακτήρα
	struct ball ball1, ball2;			// θέση και μέγεθος των αντικειμένων
	int score;							// τρέχων σκορ
	bool playing;						// true αν το παιχνίδι είναι σε εξέλιξη
	bool game_over;						// true αν είμαστε στο frame που μόλις έγινε game_over (στο επόμενο frame ξαναγίνεται false)
}* State;

// Define the StateInfo struct
typedef struct {
    int score;
    bool playing;
    bool game_over;
} StateInfo;



// Δημιουργεί και επιστρέφει την αρχική κατάσταση του παιχνιδιού

State state_create();

// Ενημερώνει την κατάσταση state του παιχνιδιού μετά την πάροδο 1 frame.

void state_update(State state);

// Επιστρέφει τις βασικές πληροφορίες του παιχνιδιού στην κατάσταση state
StateInfo state_info(State state);

// Επιστρέφει μία λίστα με όλα τα αντικείμενα του παιχνιδιού στην κατάσταση state,
// των οποίων η συντεταγμένη x είναι ανάμεσα στο x_from και x_to.
List state_objects(State state, float x_from, float x_to);
