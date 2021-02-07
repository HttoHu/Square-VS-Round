#include "../includes/player.hpp"
#include "../includes/utility.hpp"
#include "../includes/bullet.hpp"
#include "../includes/game.hpp"
#include "../includes/widget.hpp"
void Player::show()
{
	Entity::show();
	// draw hp rect
	int x = (int)pos.x - 10;
	int y = (int)pos.y + get_h()+5;

	int w = hp;
	int h = 5;
	tools::draw_rect(x, y, w, h, Widgets::ColorTag::PINK);
	x += hp;
	w = hp_cap - hp;
	if(w!=0)
		tools::draw_rect(x, y, w, h, Widgets::ColorTag::BLACK);
}
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
