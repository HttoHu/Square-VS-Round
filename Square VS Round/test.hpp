#pragma once
#include <SDL.h>
#include "square.hpp"
namespace test
{
	void test_init() {
		Square* enemy = new Square(50, 50, "eny");
		vars::stage.players.push_back(enemy);
	}
}