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
	bul->team = team_id;
	bul->pos = pos;
}

void Player::hit(Bullet* bul)
{
	if (!bul->alive||bul->team==team_id) return;
	hp -= bul->force;
	bul->alive = false;
}

bool Player::skill_enable(int skill_id)
{
	return false;
}

Walker::Walker(Player* _walker, int _speed):walker(_walker),speed(_speed)
{
	nc=c = walker->get_center_x()/ BRICK_SIZE;
	nr=r = walker->get_center_y() / BRICK_SIZE;
}

int Walker::update()
{
	double dx;
	double dy;
	if (!prepared)
	{
		int dest_x = c * BRICK_SIZE + BRICK_SIZE / 2;
		int dest_y = r * BRICK_SIZE + BRICK_SIZE / 2;
		if (walker->pos.collide({ (double)dest_x,(double)dest_y }, 1))
		{
			prepared = true;
		}
		for (int i = 1; i <= speed && !prepared; i++)
		{
			tools::set_dx_dy_by_angle(dx, dy, tools::get_angle(walker->get_center_x(), walker->get_center_y(), dest_x, dest_y), 1);
			walker->pos.x += dx;
			walker->pos.y += dy;
			if (walker->pos.collide({ (double)dest_x,(double)dest_y }, 1))
			{
				prepared = true;
				break;
			}
		}
		return 1;
	}
	int dest_x = nc * BRICK_SIZE + BRICK_SIZE / 2;
	int dest_y = nr * BRICK_SIZE + BRICK_SIZE / 2;
	auto test_collide = [&]() {
		return abs(walker->get_center_x() - dest_x) + abs(walker->get_center_y() - dest_y) <= 2;
	};
	for (int i = 1; i <= speed; i++)
	{
		tools::set_dx_dy_by_angle(dx, dy, tools::get_angle(walker->get_center_x(), walker->get_center_y(), dest_x, dest_y), 1);
		walker->pos.x += dx;
		walker->pos.y += dy;
		if (test_collide())
		{
			if (walk_ins.empty()) return -1;
			int dr[] = { 0,0,0,-1,1 };
			int dc[] = { 0,-1,1,0,0 };
			int ins = walk_ins.back();
			walk_ins.pop_back();
			c = nc;
			r = nr;
			nc = c + dc[ins];
			nr = r + dr[ins];
			dest_x = nc * BRICK_SIZE + BRICK_SIZE / 2, dest_y = nr * BRICK_SIZE + BRICK_SIZE / 2;
		}
	}
	return 1;
}

