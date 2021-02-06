#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
const std::string bricks_file[] = {
	"../assets/wall_white.png","../assets/wall_black.png"
};
const int BRICK_SIZE = 40;
class Map {
public:
	Map(const std::string& file_name);
	void show();
	bool out_map(int x, int y);
	bool enable_to_walk(int x1,int y1,int x2,int y2);
	std::vector<std::vector<int>> content;
	std::vector<std::vector<SDL_Texture*>> textures;
	int width;
	int hight;
private:


};
namespace tools {
	// 1 -> LEFT 
	// 2 -> RIGHT
	// 3 -> UP
	// 4 -> DOWN
	// By Little Jan
	bool count_shortest_path(const Map & map,std::vector<int>& path, int x1, int y1, int x2, int y2);
}