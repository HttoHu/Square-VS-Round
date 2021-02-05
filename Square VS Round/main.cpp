#include <SDL.h>
#include "defs.hpp"
#include "structs.hpp"
#include "test.hpp"
#include "widget.hpp"
void init_the_game() {
	init_SDL();
	App::objects_init();
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
		Screen::draw_objects();
		Screen::update_screen();
		Screen::cap_frame_rate(then, remainer);
	}
}
int main(int argc, char** argv) {
	memset(&app, 0, sizeof(app));

	init_the_game();
	loop_the_game();
	return 0;
}