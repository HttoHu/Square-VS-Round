#pragma once
#include "player.hpp"
struct Square :public Player
{
public:
	Square(double _x, double _y, const std::string& _name) :Player(_x, _y,"../assets/boss.png") 
	{
		name = _name, hp = 100; hp_cap = 100; shoot_speed = 4;
	}

	void update()override;
	void show()override;
private:
};