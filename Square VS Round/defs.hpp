#pragma once
#include <string>
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const double eps = 1;
struct SDL_Texture;
struct Player;
struct Entity;


struct Screen {
	static void prepare_screen();
	static void update_screen();
	static SDL_Texture* load_texture(const std::string& filename);
	static void blit(SDL_Texture* texture, int x, int y);
	static void cap_frame_rate(long &then, float &remainder);

	static void draw_objects();
};

namespace vars {
	extern Player* player;
	extern Entity* cursor;
}
struct App;
extern App app;
void init_SDL();

void clean_up();

void do_input();

