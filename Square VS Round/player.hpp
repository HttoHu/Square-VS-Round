#pragma once
#include <SDL.h>
#include "objects.hpp"

struct Bullet;

struct Player :public Entity
{
public:
	Player(double _x,double _y,const std::string pic_str) :Entity(_x,_y,pic_str) {}

	std::string name;

	int hp=0;
	int move_speed=2;
	int bullet_cnt=0;
	int shoot_speed=1;
	int level = 1;
	virtual void upgrade() {}
	virtual void fire(Bullet* bul);
	virtual void hit(Bullet* bul);
	virtual bool skill_enable(int skill_id);
	~Player() {}
};