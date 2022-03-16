#pragma once
#include "objects.hpp"
struct Bullet :public Entity {
public:
	Bullet(const std::string& filename);
	Bullet(double _x, double _y, const std::string& pic_str, double _dx, double _dy);
	void update()override;
	void show()override;
	bool is_shooter(Player* p);
	double dx, dy;
	bool alive=true;

	bool damage = true;
	bool cure_friend = false;
	int force = 10;
	int speed = 4;
	int team;
	virtual ~Bullet()override {}
private:
	
};
