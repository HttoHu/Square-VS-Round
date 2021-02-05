#pragma once
#include <string>
#include <SDL.h>
#include "defs.hpp"
#include "structs.hpp"

struct Entity {
public:
	Entity() {}
	Entity(double _x, double _y, const std::string& pic);
	virtual void show();
	virtual void update() {}

	virtual ~Entity();

	Pos pos;
	void rotate(double angle);

	bool out_window()const;
	int get_w()const { return w; }
	int get_h()const { return h; }
private:
	SDL_Texture* texture;
	int w, h;
};


namespace tools
{
	bool objects_collide(Entity* e1, Entity* e2);
}