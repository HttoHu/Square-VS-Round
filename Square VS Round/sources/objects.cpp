#include "../includes/objects.hpp"
#include "../includes/game.hpp"
#include "../includes/game_map.hpp"
#include "../includes/utility.hpp"
#include "../includes/player.hpp"
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
	if (static_object)
		Screen::blit_static(texture, (int)(pos.x), (int)(pos.y));
	else 
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

bool Entity::bad_pos() const
{
	return app.game_map->out_map(pos.x,pos.y) || app.game_map->out_map(pos.x+w,pos.y+h) || !app.game_map->enable_to_walk(pos.x,pos.y,pos.x+w,pos.y+h);
}

bool tools::objects_collide(Entity* e1, Entity* e2)
{
	double x1 = e1->pos.x, x2 = e2->pos.x, dx1 = e1->get_w(), dx2 = e2->get_w();
	if (x1 + dx1 < x2 || x1 >x2 +dx2)
		return false;
	double y1 = e1->pos.y, y2 = e2->pos.y, dy1 = e1->get_h(), dy2 = e2->get_h();
	if (y1 + dy1 < y2 || y1 >y2+dy2)
		return false;
	return true;
}
