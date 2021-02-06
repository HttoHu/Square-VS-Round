#include "../includes/round.hpp"
#include "../includes/utility.hpp"
#include "../includes/bullet.hpp"
#include "../includes/game.hpp"
#include <algorithm>
void Round::fire(Bullet* bul)
{
	vars::stage.bullets.push_back(bul);

	app.target = { (double)tools::get_cursor_pos().first,(double)tools::get_cursor_pos().second };
	tools::set_dx_dy_by_angle(bul->dx, bul->dy, tools::get_angle(pos.x-app.camera.x, pos.y- app.camera.y, app.target.x, app.target.y), bul->speed);
	bul->shooter = this;
	bul->pos = pos;
	bul->force = common_bul_force;
}

void Round::upgrade()
{
	if (level >= 4) return;
	level++;
	if (level == 2)
	{
		hp = 70;
		common_bul_force += 5;
		Q_bul_force = 25;
	}
	if (level == 3)
	{
		hp = 90;
		common_bul_force += 5;
		Q_bul_force = 30;
	}

}

void Round::update()
{
	bullet_cnt += shoot_speed;
	Q_skill_cnt++, E_skill_cnt++;
	// You can shoot two high speed bullet at the same time;
	Q_skill_cnt = std::min(Q_skill_cnt, 550);
	E_skill_cnt = std::min(E_skill_cnt, 600);
	bullet_cnt = std::min(500, bullet_cnt);
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
	else if (skill_id == 2 && E_skill_cnt >= 600)
		return true;
	return false;
}

void Round::skill_run(int skill_id)
{
	if (skill_id == 1)
	{
		if (level >= 2 && Q_skill_cnt >= 300)
		{
			Q_skill_cnt -= 300;
			Bullet* high_speed_bull = create_Q_bullet();
			fire(high_speed_bull);
		}
		return;
	}
	else if (skill_id == 2)
	{
		if (level >= 3 && E_skill_cnt >= 600)
		{
			printf("OK\n");
			E_skill_cnt -= 600;
			RoundShield* shield = new RoundShield(level, pos.x, pos.y, this);
			vars::stage.players.push_front(shield);
		}
	}
}

Bullet* Round::create_Q_bullet()
{
	Bullet* bul = new Bullet("../assets/round_Q_bullet.png");
	bul->force = Q_bul_force;
	bul->speed = 12;
	return bul;
}

RoundShield::RoundShield(int level, int _x, int _y, Player* _master) :Player(_x-25, _y-25, "../assets/round_shield.png"),master(_master)
{
	if (level == 3) hp = 70;
	else if (level == 4) hp = 100;
	else hp = 0;
	move_speed = 0;
}

void RoundShield::hit(Bullet* bul)
{
	if (bul->shooter == master)
		return;
	bul->alive = false;
	hp -= bul->force;
	if (hp < 0) hp = 0;
}

void RoundShield::show()
{
	Entity::show();
}

Camera::Camera(int _x, int _y, Player* master) :Player(_x, _y, "../assets/round_camera.png")
{
	hp = 30;
}

void Camera::hit(Bullet* bul)
{
}

void Camera::update()
{
}
