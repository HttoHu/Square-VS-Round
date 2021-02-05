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
	int force = 10;
	int speed = 4;
	Player* shooter;
	virtual ~Bullet()override {}
private:
	
};
