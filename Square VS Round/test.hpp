#pragma once
#include <SDL.h>
#include "square.hpp"
namespace test
{
	void test_init() {
		Square* enemy = new Square(100, 100, "eny");
		vars::stage.players.push_back(enemy);
	}
}