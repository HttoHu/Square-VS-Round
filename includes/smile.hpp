#pragma once
#include "player.hpp"
struct Smile :public Player
{
public:
	Smile(double _x, double _y, const std::string& _name) :Player(_x, _y,"../assets/smile.png") 
	{
		name = _name, hp = 100; hp_cap = 100; shoot_speed = 4;
	}

	void update()override;
	void show()override;
private:
	int d = 1;
};