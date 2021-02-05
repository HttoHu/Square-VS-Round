#pragma once
#include "objects.hpp"
#include "player.hpp"

struct Round :public Player {
public:
	// _x, _y : the position of the player 
	// pic_str : the sharp of the player
	// _ms: the move speed of the player
	Round(double _x, double _y, const std::string& _name) :Player(_x, _y, "../assets/round.png") { name = _name, hp = 50; shoot_speed = 1; move_speed = 3; }
	void fire(Bullet* bul)override;
	void upgrade()override;
	void update()override;
	void show()override;

	bool skill_enable(int skill_id)override;
	~Round()override {}
private:
	int common_bul_force = 10;
	int Q_bul_force = 15;
	int Q_skill_cnt = 0;
	Bullet* create_Q_bullet();
};