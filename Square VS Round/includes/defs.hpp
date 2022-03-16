#pragma once
#include <string>
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int BRICK_SIZE = 40;
const double eps = 1;
struct SDL_Texture;
struct Player;
struct Entity;

namespace vars {
	extern Player* player;
	extern Entity* cursor;
}
struct App;
extern App app;
extern std::string asset_path;

std::string get_assets_path(const std::string& str);
void init_SDL();

void clean_up();

void do_input();

