#include "..\includes\square.hpp"
#include "../includes/bullet.hpp"
#include "../includes/game.hpp"
#include "../includes/utility.hpp"

void Square::fire(Bullet* bul)
{
	vars::stage.bullets.push_back(bul);
	Pos p = get_aim_pos();
	tools::set_dx_dy_by_angle(bul->dx, bul->dy, tools::get_angle(pos.x, pos.y, p.x, p.y), bul->speed);
	bul->team = team_id;
	bul->pos = pos;
	bul->force = common_bul_force;
}

void Square::upgrade()
{
	if (level >= 4) return;
	level++;
	if (level == 2)
	{
		hp_cap = 80;
		hp = 80;
		common_bul_force += 5;
	}
	else if (level == 3)
	{
		hp_cap = 100;
		hp = 100;
		common_bul_force += 5;
	}
	else if (level == 4)
	{
		hp_cap = 135;
		hp = 135;
		common_bul_force += 10;
	}
}

void Square::update()
{
	bullet_cnt += shoot_speed * 2;
	Q_skill_cnt++, E_skill_cnt++, R_skill_cnt++;
	// You can shoot two high speed bullet at the same time;
	Q_skill_cnt = std::min(Q_skill_cnt, 550);
	E_skill_cnt = std::min(E_skill_cnt, 600);
	R_skill_cnt = std::min(R_skill_cnt, 1200);
	bullet_cnt = std::min(bullet_cnt, 500);
}

void Square::show()
{
	update();
	Player::show();
}

bool Square::skill_enable(int skill_id)
{
	if (level >= 2 && skill_id == 1 && Q_skill_cnt >= 300)
		return true;
	else if (level >= 3 && skill_id == 2 && E_skill_cnt >= 600)
		return true;
	else if (level >= 4 && skill_id == 3 && R_skill_cnt >= 1200)
		return true;
	return false;
}

void Square::skill_run(int skill_id)
{
	if (!skill_enable(skill_id))
		return;
	if (skill_id == 1)
	{
		Q_skill_cnt -= 300;
		Bullet* high_speed_bull = create_Q_bullet();
		fire(high_speed_bull);
		return;
	}
}

Bullet* Square::create_Q_bullet()
{
	Bullet* bul = new Bullet(get_assets_path("square/square_Q_bullet"));
	bul->force = Q_bul_force;
	bul->speed = 12;
	return bul;
}
