#include "../includes/round.hpp"
#include "../includes/utility.hpp"
#include "../includes/bullet.hpp"
#include "../includes/game.hpp"
#include <iostream>
#include <algorithm>
void Round::fire(Bullet *bul)
{
    vars::stage.bullets.push_back(bul);
    Pos p = get_aim_pos();
    tools::set_dx_dy_by_angle(bul->dx, bul->dy, tools::get_angle(pos.x, pos.y, p.x, p.y), bul->speed);
    bul->team = team_id;
    bul->pos = pos;
    bul->force = common_bul_force;
}

void Round::upgrade()
{
    if (level >= 4)
        return;
    level++;
    if (level == 2)
    {
        hp_cap = 70;
        hp = 70;
        common_bul_force += 5;
    }
    if (level == 3)
    {
        hp_cap = 90;
        hp = 90;
        common_bul_force += 5;
    }
    if (level == 4)
    {
        hp_cap = 120;
        hp = 120;
        common_bul_force += 10;
    }
}

void Round::update()
{
    bullet_cnt += shoot_speed * 2;
    Q_skill_cnt++, E_skill_cnt++, R_skill_cnt++;
    // You can shoot two high speed bullet at the same time;
    Q_skill_cnt = std::min(Q_skill_cnt, 550);
    E_skill_cnt = std::min(E_skill_cnt, 650);
    R_skill_cnt = std::min(R_skill_cnt, 1200);
    bullet_cnt = std::min(bullet_cnt, 500);
    // hp = hp_cap;
    if (shield)
        shield->update();
    if (robot)
        robot->update();
}

void Round::show()
{
    update();
    Player::show();
}

bool Round::skill_enable(int skill_id)
{
    if (level >= 2 && skill_id == 1 && Q_skill_cnt >= 300)
        return true;
    else if (level >= 3 && skill_id == 2 && E_skill_cnt >= 600)
        return true;
    else if (level >= 4 && skill_id == 3 && R_skill_cnt >= 1200)
        return true;
    return false;
}

void Round::skill_run(int skill_id)
{
    if (!skill_enable(skill_id))
        return;
    if (skill_id == 1)
    {
        Q_skill_cnt -= 300;
        Bullet *high_speed_bull = create_Q_bullet();
        fire(high_speed_bull);
        return;
    }
    else if (skill_id == 2)
    {
        E_skill_cnt -= 600;
        if (shield)
        {
            shield->hp = shield->hp_cap;
            return;
        }
        shield = new RoundShield(level, pos.x, pos.y, this);
        vars::stage.players.push_back(shield);
    }
    else if (skill_id == 3)
    {
        if (robot)
            return;
        R_skill_cnt -= 1200;
        robot = new RoundRobot(pos.x + 50, pos.y + 50, this);
        vars::stage.players.push_back(robot);
    }
}

Bullet *Round::create_Q_bullet()
{
    Bullet *bul = new Bullet("../assets/round_Q_bullet.png");
    bul->force = Q_bul_force;
    bul->speed = 12;
    return bul;
}

RoundShield::RoundShield(int level, int _x, int _y, Round *_master) : Player(_x - 25, _y - 25, "../assets/round_shield.png"), master(_master)
{
    if (level == 3)
        hp = 70;
    else if (level == 4)
        hp = 100;
    else
        hp = 0;
    hp_cap = hp;
    move_speed = 0;
}

void RoundShield::hit(Bullet *bul)
{
    if (bul->team == master->team_id)
        return;
    bul->alive = false;
    hp -= bul->force;
    if (hp < 0)
        hp = 0;
}
void RoundShield::remove_from_list()
{
    master->shield = nullptr;
    delete this;
}

void RoundShield::update()
{
    pos.x = master->pos.x - 40;
    pos.y = master->pos.y - 40;
}
void RoundShield::show()
{
    Player::show();
}

RoundRobot::RoundRobot(int _x, int _y, Round *_master) : Player(_x, _y, "../assets/round_camera.png"), master(_master)
{
    hp = 100;
    hp_cap = 100;
}

void RoundRobot::hit(Bullet *bul)
{
    if (bul->team == master->team_id)
        return;
    bul->alive = false;
    hp -= bul->force;
    if (hp < 0)
        hp = 0;
}

void RoundRobot::fire(Bullet *bul)
{
    vars::stage.bullets.push_back(bul);
    Pos p = get_aim_pos();
    tools::set_dx_dy_by_angle(bul->dx, bul->dy, tools::get_angle(pos.x, pos.y, p.x, p.y), bul->speed);
    bul->team = team_id;
    bul->pos = pos;
    bul->force = 3;
}

void RoundRobot::remove_from_list()
{
    master->robot = nullptr;
    delete this;
}
void RoundRobot::update()
{
    bullet_cnt += 10;
    bullet_cnt = std::min(bullet_cnt, 200);
    // fire
    if (bullet_cnt >= 100)
    {
        bullet_cnt -= 100;
        aim(master->get_aim_pos());
        fire(new Bullet("../assets/round_bullet.png"));
    }
    // follow master
    Pos dest = master->pos;
    double dx = 0;
    double dy = 0;
    tools::set_dx_dy_by_angle(dx, dy, tools::get_angle(pos.x, pos.y, dest.x, dest.y), 2);
    dest.x += master->get_w() / 2;
    dest.y += master->get_h() / 2;
    double eps = std::max(master->get_h(), master->get_w());
    if (!dest.collide(pos, eps))
        pos.x += dx, pos.y += dy;
}

void RoundRobot::show()
{
    update();
    Player::show();
}
