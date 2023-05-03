#include <stdlib.h>

#include "state.h"
#include "ADTList.h"
#include "raylib.h"
#include "../include/state.h"


// Αρχικοποιεί την κατάσταση το παιχνιδιού

static void state_init(State state) {
	state->score = 0;
	state->playing = true;

	state->character.width = 47;
	state->character.height = 39;
	state->character.x = 80;
	state->character.y = SCREEN_HEIGHT / 2 - state->character.height / 2;

	state->ball1.radius = 15;
	state->ball1.position.x = SCREEN_WIDTH / 3.;
	state->ball1.position.y = state->ball1.radius;

	state->ball2.radius = 30;
	state->ball2.position.x = 2 * SCREEN_WIDTH / 3.;
	state->ball2.position.y = state->ball2.radius;
}

// Δημιουργεί και επιστρέφει την αρχική κατάσταση του παιχνιδιού

State state_create() {
	State state = malloc(sizeof(*state));
	state_init(state);
	return state;
}

// Ενημερώνει την κατάσταση του παιχνιδιού για το επόμενο frame
//
// Για απλότητα, χρησιμοποιούμε απ'ευθείας τη συνάρτηση IsKeyDown(key) για
// έλεγχο των πλήκτρων. Μια καλύτερη υλοποίηση θα έπαιρνε την κατάσταση των
// πλήκτρων σαν όρισμα, ώστε να μπορούμε να δοκιμάσουμε τη συνάρτηση με
// κατάλληλα tests.
//
void state_update(State state) {
	state->game_over = false;		// το true διαρκεί μόνο 1 frame

	if (state->playing) {
		state->character.x += IsKeyDown(KEY_LEFT) ? 1 : 3;

		// wrap
		if (state->character.x > SCREEN_WIDTH) {
			state->character.x = 0;
			state->score++;
		}

		state->ball1.position.y = (int)(state->ball1.position.y + 5) % SCREEN_HEIGHT;
		state->ball2.position.y = (int)(SCREEN_HEIGHT + state->ball2.position.y - 7) % SCREEN_HEIGHT;

		if (IsKeyDown(KEY_UP))
			state->character.y -= 3;
		else
			state->character.y += 1;

		// έλεγχος για collisions
		if (state->character.y < 0 ||
			state->character.y > SCREEN_HEIGHT - state->character.height ||
			CheckCollisionCircleRec(state->ball1.position, state->ball1.radius, state->character) ||
			CheckCollisionCircleRec(state->ball2.position, state->ball2.radius, state->character)) {

			state->playing = false;
			state->game_over = true;
		}

	} else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
		state_init(state);		// επαναφορά στην αρχική κατάσταση
	}
}



StateInfo state_info(State state) {
    StateInfo state_infos;
    state_infos->score = state->score;
    state_infos->playing = state->playing;
    state_infos->game_over = state->game_over;


    return state_infos;
}


List state_objects(State state, float x_from, float x_to) {
    List objects = list_new();
    Object ball1 = malloc(sizeof(*ball1));
    Object ball2 = malloc(sizeof(*ball2));
    Object platform = malloc(sizeof(*platform));
    Object star = malloc(sizeof(*star));

    ball1->type = BALL;
    ball1->rect = (Rectangle) { state->ball1.position.x, state->ball1.position.y, 2 * state->ball1.radius, 2 * state->ball1.radius };
    ball1->vert_mov = IDLE;
    ball1->vert_speed = 0;
    ball1->unstable = false;

    ball2->type = BALL;
    ball2->rect = (Rectangle) { state->ball2.position.x, state->ball2.position.y, 2 * state->ball2.radius, 2 * state->ball2.radius };
    ball2->vert_mov = IDLE;
    ball2->vert_speed = 0;
    ball2->unstable = false;

    platform->type = PLATFORM;
    platform->rect = state->character;
    platform->vert_mov = IDLE;
    platform->vert_speed = 0;
    platform->unstable = false;

    star->type = STAR;
    star->rect = (Rectangle) { 0, 0, 0, 0 };
    star->vert_mov = IDLE;
    star->vert_speed = 0;
    star->unstable = false;

    if (ball1->rect.x >= x_from && ball1->rect.x <= x_to)
        list_append(objects, ball1);
    if (ball2->rect.x >= x_from && ball2->rect.x <= x_to)
        list_append(objects, ball2);
    if (platform->rect.x >= x_from && platform->rect.x <= x_to)
        list_append(objects, platform);
    if (star->rect.x >= x_from && star->rect.x <= x_to)
        list_append(objects, star);

    free(ball1);
    free(ball2);
    free(platform);
    free(star);

    return objects;
}


