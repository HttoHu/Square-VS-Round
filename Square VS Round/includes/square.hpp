#pragma once
#include "objects.hpp"
#include "player.hpp"

struct Square :public Player {
public:
	// _x, _y : the position of the player 
	// pic_str : the sharp of the player
	// _ms: the move speed of the player
	Square(double _x, double _y, const std::string& _name) :Player(_x, _y, asset_path+"/square/square.png")
	{
		name = _name, hp = 60; shoot_speed = 1; move_speed = 3; hp_cap = 60; common_bul_force = 15;
	}
	void fire(Bullet* bul)override;
	void upgrade()override;
	void update()override;
	void show()override;

	bool skill_enable(int skill_id)override;
	void skill_run(int skill_id)override;

	~Square()override {}
	Pos last_shoot_pos;
private:
	int Q_bul_force = 15;
	int Q_skill_cnt = 0;
	int E_skill_cnt = 0;
	int R_skill_cnt = 10;
	Bullet* create_Q_bullet();
};