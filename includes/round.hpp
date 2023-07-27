#pragma once
#include "objects.hpp"
#include "player.hpp"
#include <vector>
struct Round :public Player {
public:
	// _x, _y : the position of the player 
	// pic_str : the sharp of the player
	// _ms: the move speed of the player
	Round(double _x, double _y, const std::string& _name) :Player(_x, _y, "../assets/round.png") { name = _name, hp = 50; shoot_speed = 1; move_speed = 3; hp_cap = 50; common_bul_force = 15; upgrade(), upgrade(),upgrade(); }
	void fire(Bullet* bul)override;
	void upgrade()override;
	void update()override;
	void show()override;

	bool skill_enable(int skill_id)override;
	void skill_run(int skill_id)override;

	~Round()override {}
	Pos last_shoot_pos;
private:
	int Q_bul_force = 15;
	int Q_skill_cnt = 0;
	int E_skill_cnt = 0;
	int R_skill_cnt = 10;
	Bullet* create_Q_bullet();
};

class RoundShield : public Player
{
public:
	RoundShield(int level,int _x,int _y,Player *_master);
	void hit(Bullet* bul)override;
	void show()override;
private:
	Player* master;
};
class Camera : public Player {
public:
	Camera(int _x, int _y, Player* _master);
	void hit(Bullet* bul)override;
	void fire(Bullet* bul)override;
	void update();
	void show()override;
private:
	Player* master;
	std::vector<int> ins;
};