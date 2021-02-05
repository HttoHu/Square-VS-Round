#include "round.hpp"
#include "utility.hpp"
#include "bullet.hpp"
#include <algorithm>
void Round::fire(Bullet* bul)
{
	vars::stage.bullets.push_back(bul);

	app.target = { (double)tools::get_cursor_pos().first,(double)tools::get_cursor_pos().second };
	tools::set_dx_dy_by_angle(bul->dx, bul->dy, tools::get_angle(pos.x, pos.y, app.target.x, app.target.y), bul->speed);
	bul->shooter = this;
	bul->pos = pos;
	bul->force = common_bul_force;
}

void Round::upgrade()
{
	if (level >= 4) return;
	level++;
	hp += 20;

	common_bul_force += 5;
	Q_bul_force = 25;

}

void Round::update()
{
	double dx = 0;
	double dy = 0;
	bullet_cnt += shoot_speed;
	Q_skill_cnt++;
	// You can shoot two high speed bullet at the same time;
	Q_skill_cnt = std::min(Q_skill_cnt, 600);

	bullet_cnt = std::min(500,bullet_cnt);
	static Pos last_dest_pos = { 0.0,0.0 };
	static double ang = 0.0;
	// Q Skill
	if (app.keyboard[SDL_SCANCODE_Q] && level >=2 &&Q_skill_cnt>=300)
	{
		Q_skill_cnt -= 300;
		Bullet* high_speed_bull = create_Q_bullet();
		fire(high_speed_bull);
	}

	// keyboad move
	if (app.keyboard[SDL_SCANCODE_W] || app.keyboard[SDL_SCANCODE_S] || app.keyboard[SDL_SCANCODE_D] || app.keyboard[SDL_SCANCODE_A])
	{
		app.dest_pos_valid = false;
		dx = (double)(app.keyboard[SDL_SCANCODE_D] - app.keyboard[SDL_SCANCODE_A]);
		dy = (double)(app.keyboard[SDL_SCANCODE_S] - app.keyboard[SDL_SCANCODE_W]);
		if (abs(dx) + abs(dy) == 2)
		{
			dx *= move_speed / sqrt(2.0);
			dy *= move_speed / sqrt(2.0);
		}
		else {
			dx *= move_speed;
			dy *= move_speed;
		}
	}
	// mouse move
	else if (app.dest_pos_valid && !pos.collide(app.dest_pos, move_speed))
	{
		if (!last_dest_pos.collide(app.dest_pos, 1.0))
		{
			ang = tools::get_angle(pos.x, pos.y, app.dest_pos.x, app.dest_pos.y);
			last_dest_pos = app.dest_pos;
		}
		dx = tools::sin(ang) * move_speed;
		dy = -tools::cos(ang) * move_speed;
	}
	else return;
	
	
	pos.x += dx;
	pos.y += dy;
	if (out_window())
	{
		pos.x -= dx;
		pos.y -= dy;
	}
}

void Round::show()
{
	update();
	Entity::show();

}

bool Round::skill_enable(int skill_id)
{
	if (skill_id == 1 && Q_skill_cnt >= 300)
		return true;
	return false;
}

Bullet* Round::create_Q_bullet()
{
	Bullet* bul = new Bullet("../assets/round_Q_bullet.png");
	bul->force = Q_bul_force;
	bul->speed = 12;
	return bul;
}



