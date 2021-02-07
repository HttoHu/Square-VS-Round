#include "../includes/round.hpp"
#include "../includes/utility.hpp"
#include "../includes/bullet.hpp"
#include "../includes/game.hpp"
#include <algorithm>
void Round::fire(Bullet* bul)
{
	vars::stage.bullets.push_back(bul);
	Pos p = get_aim_pos();
	tools::set_dx_dy_by_angle(bul->dx, bul->dy, tools::get_angle(pos.x, pos.y, p.x, p.y), bul->speed);
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
		hp_cap = 70;
		hp = 70;
		common_bul_force += 5;
		Q_bul_force = 25;
	}
	if (level == 3)
	{
		hp_cap = 90;
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
	Player::show();

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
	Player::show();
}

Camera::Camera(int _x, int _y, Player* master) :Player(_x, _y, "../assets/round_camera.png")
{
	hp = 30;
}

void Camera::hit(Bullet* bul)
{
	if (bul->shooter == master)
		return;
	bul->alive = false;
	hp -= bul->force;
	if (hp < 0) hp = 0;
}

void Camera::fire(Bullet* bul)
{
	vars::stage.bullets.push_back(bul);
	Pos p = get_aim_pos();
	tools::set_dx_dy_by_angle(bul->dx, bul->dy, tools::get_angle(pos.x, pos.y, p.x, p.y), bul->speed);
	bul->shooter = this;
	bul->pos = pos;
	bul->force = 15;
}

void Camera::update()
{
	bullet_cnt ++;
	bullet_cnt = std::max(bullet_cnt, 200);
	if (bullet_cnt >= 100)
	{
		bullet_cnt -= 100;
		aim(master->get_aim_pos());
		fire(new Bullet(".. / assets / round_bullet.png"));
	}
	Pos dest = master->pos;
	double dx = 0;
	double dy = 0;


}
