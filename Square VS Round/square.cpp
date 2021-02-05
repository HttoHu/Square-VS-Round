#include "square.hpp"
#include "utility.hpp"
#include "bullet.hpp"

void Square::update()
{
	bullet_cnt += shoot_speed;
	static int ang = 0;
	ang++;
	ang %= 360;
	double dx = tools::cos(ang) * move_speed;
	double dy = tools::sin(ang) * move_speed;
	pos.x += dx;
	pos.y += dy;
	if (out_window())
	{
		pos.x -= dx;
		pos.y -= dy;
	}
	if (bullet_cnt >= 100)
	{
		bullet_cnt -= 100;
		Bullet* bul = new Bullet("../assets/square_bullet.png");
		bul->force = 10;
		double ang = tools::get_angle(pos.x, pos.y, vars::player->pos.x, vars::player->pos.y);
		tools::set_dx_dy_by_angle(bul->dx, bul->dy, ang, 4);
		fire(bul);
	}
}

void Square::show()
{
	update();
	Entity::show();
}