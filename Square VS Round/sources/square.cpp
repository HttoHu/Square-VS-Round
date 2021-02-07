#include "../includes/square.hpp"
#include "../includes/utility.hpp"
#include "../includes/bullet.hpp"

void Square::update()
{
	bullet_cnt += shoot_speed;
}

void Square::show()
{
	update();
	Player::show();
}
