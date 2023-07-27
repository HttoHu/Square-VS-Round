#pragma once
#include <string>
#include <SDL.h>
#include "defs.hpp"
#include "pos.hpp"
struct Entity {
public:
	Entity() {}
	Entity(double _x, double _y, const std::string& pic);
	virtual void show();
	virtual void update() {}

	virtual ~Entity();

	Pos pos;
	void rotate(double angle);
	void set_static() { static_object = true; }
	bool bad_pos()const;
	int get_w()const { return w; }
	int get_h()const { return h; }
	int get_center_x()const { return int(pos.x) + w / 2; }
	int get_center_y()const { return int(pos.y) + h / 2; }
private:
	bool static_object=false;
	SDL_Texture* texture;
	int w, h;
};


namespace tools
{
	bool objects_collide(Entity* e1, Entity* e2);
}