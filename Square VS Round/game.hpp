#pragma once
#include <string>
#include <SDL.h>
#include <list>
#include <vector>
#include "defs.hpp"
#include "pos.hpp"
namespace Widgets
{
	class TextBlock;
	class Image;
}
class Map;
struct App
{
	SDL_Renderer* renderer;
	SDL_Window* window;
	Map* game_map;

	static void game_init();
	static void update();
	int keyboard[350];

	bool dest_pos_valid = false;
	Pos dest_pos = { (double)SCREEN_WIDTH / 2,(double)SCREEN_HEIGHT / 2 };
	Pos target;
	Pos camera;


	Widgets::TextBlock* property;
	Widgets::Image* split_line;
	Widgets::Image* Q_skill_tag;
	Widgets::Image* E_skill_tag;
	Widgets::Image* R_skill_tag;
};


struct Entity;
struct Player;
struct Stage {
public:
	std::list<Player*> players;
	std::list<Entity*> bullets;
	void draw_players();
	void draw_bullets();
private:
};
namespace vars {
	extern Stage stage;
}