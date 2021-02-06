#include "bullet.hpp"
#include "player.hpp"
#include "game.hpp"
Bullet::Bullet(const std::string& filename) :Entity(0, 0, filename)
{
}

Bullet::Bullet(double _x, double _y, const std::string& pic_str, double _dx, double _dy) : Entity(_x, _y, pic_str), dx(_dx), dy(_dy) {}

void Bullet::update()
{
	if (alive)
	{
		pos.x += dx * 4;
		pos.y += dy * 4;
		using iterate = std::list<Player*>::iterator;
		for (iterate it = vars::stage.players.begin(); it != vars::stage.players.end(); it++)
		{
			if (tools::objects_collide(this, *it) && !is_shooter(*it))
			{
				(*it)->hit(this);
			}
		}
	}
}

void Bullet::show()
{
	update();
	Entity::show();
}

bool Bullet::is_shooter(Player* p)
{
	return shooter == p;
}
