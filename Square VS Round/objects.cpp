#include "objects.hpp"
#include "structs.hpp"
#include "utility.hpp"
#include "player.hpp"
namespace vars
{
	Stage stage;
	Player* player;
	Entity* cursor;
}


Entity::Entity(double _x, double _y, const std::string& pic) :pos({ _x,_y })
{
	texture = Screen::load_texture(pic);

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

void Entity::show()
{
	Screen::blit(texture, (int)(pos.x), (int)(pos.y));
}

Entity::~Entity()
{
	SDL_DestroyTexture(texture);
}

void Entity::rotate(double angle)
{
	tools::rotate_pic(texture, (int)pos.x, (int)pos.y, angle);
}

bool Entity::out_window() const
{
	return (pos.x > SCREEN_WIDTH - w) || (pos.x < 0) || (pos.y > SCREEN_HEIGHT - 60) || (pos.y < 0);
}

bool tools::objects_collide(Entity* e1, Entity* e2)
{
	double x1 = e1->pos.x, x2 = e2->pos.x, dx1 = e1->get_w() / 2, dx2 = e2->get_w() / 2;
	if (x1 + dx1 < x2 - dx2 || x1 - dx1>x2 + dx2)
		return false;
	double y1 = e1->pos.y, y2 = e2->pos.y, dy1 = e1->get_h() / 2, dy2 = e2->get_h() / 2;
	if (y1 + dy1 < y2 - dy2 || y1 - dy1>y2 + dy2)
		return false;
	return true;
}
