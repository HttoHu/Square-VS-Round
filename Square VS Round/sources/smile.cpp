#include "../includes/smile.hpp"
#include "../includes/utility.hpp"
#include "../includes/bullet.hpp"

void Smile::update()
{
	bullet_cnt += shoot_speed;
}

void Smile::show()
{
	update();
	Player::show();
}
