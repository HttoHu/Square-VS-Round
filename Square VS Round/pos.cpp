#include "pos.hpp"
#include <cmath>
bool Pos::collide(Pos p, double eps)
{
	return abs(x - p.x) + abs(y - p.y) < eps;
}

double Pos::get_dis(Pos p)
{
	return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
}