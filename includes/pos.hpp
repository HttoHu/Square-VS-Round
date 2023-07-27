#pragma once
struct Pos {
	double x;
	double y;
	bool collide(Pos p, double eps);
	double get_dis(Pos p);
};