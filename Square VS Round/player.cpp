#include "player.hpp"
#include "utility.hpp"
#include "bullet.hpp"
#include "game.hpp"
void Player::fire(Bullet* bul)
{
	vars::stage.bullets.push_back(bul);
	bul->shooter = this;
	bul->pos = pos;
}

void Player::hit(Bullet* bul)
{
	if (!bul->alive) return;
	hp -= bul->force;
	bul->alive = false;
}

bool Player::skill_enable(int skill_id)
{
	return false;
}
