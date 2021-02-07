#include <SDL.h>
#include <time.h>
#include "../includes/defs.hpp"
#include "../includes/game.hpp"
#include "../includes/test.hpp"
#include "../includes/widget.hpp"
#include "../includes/draw.hpp"
void init_the_game() {
	init_SDL();
	App::game_init();
	test::test_init();
}

void loop_the_game() {
	long then;
	float remainer;
	then = SDL_GetTicks();

	remainer = 0;
	while (1) {
		Screen::prepare_screen();
		do_input();
		app.update();
		test::test_update();
		Screen::draw_objects();
		Screen::update_screen();
		Screen::cap_frame_rate(then, remainer);
	}
}

int main(int argc, char** argv) {
	srand(clock());
	memset(&app, 0, sizeof(app));

	init_the_game();
	loop_the_game();
	return 0;
}