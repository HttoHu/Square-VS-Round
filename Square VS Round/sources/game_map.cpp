#include "../includes/game_map.hpp"
#include "../includes/draw.hpp"
#include <fstream>
#include <queue>
#include <time.h>
#include <tuple>

Map::Map(const std::string& file_name)
{
	std::ifstream ifs(file_name);
	if (!ifs.good())
	{
		printf("open map file failed\n");
		exit(1);
	}
	ifs >> hight >> width;
	// init content and textures array
	content.resize(hight);
	textures.resize(hight);
	for (auto& a : content)
		a.resize(width);
	for (auto& a : textures)
		a.resize(width);


	for (int i = 0; i < hight; i++)
	{
		std::string str;
		ifs >> str;
		for (int j = 0; j < str.size(); j++)
		{
			content[i][j] = str[j] - '0';
			textures[i][j] = Screen::load_texture(bricks_file[str[j] - '0']);
		}
	}

	ifs.close();
}

void Map::show()
{
	int cnt = 0;
	for (int i = 0; i < hight; i++)
		for (int j = 0; j < width; j++)
			Screen::blit(textures[i][j], j * BRICK_SIZE, i * BRICK_SIZE);
}

bool Map::out_map(int x, int y)
{
	return x<BRICK_SIZE || y<BRICK_SIZE || x>(width - 1) * BRICK_SIZE || y>(hight - 1) * BRICK_SIZE;
}

bool Map::enable_to_walk(int x1, int y1, int x2, int y2)
{
	x1 /= BRICK_SIZE;
	y1 /= BRICK_SIZE;
	x2 /= BRICK_SIZE;
	y2 /= BRICK_SIZE;
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++)
			if (content[j][i])
				return false;
	return true;
}
std::pair<int, int> Map::gen_space(int no)
{
	int cnt = 0;
	for (int i = 0; i < content.size(); i++)
		for (int j = 0; j < content.size(); j++)
			if (content[i][j] == 0)
			{
				cnt++;
				if (cnt == no)
					return { j * BRICK_SIZE + BRICK_SIZE / 2,i * BRICK_SIZE + BRICK_SIZE / 2 };
			}
	return { -1,-1 };
}
namespace tools
{
	namespace {
		struct Pair {
			int first;
			int second;
		};
		int vis[50][50];
		int track[50][50];
	}
	// 1 -> LEFT 
	// 2 -> RIGHT
	// 3 -> UP
	// 4 -> DOWN

	bool count_shortest_path(const Map& map, std::vector<int>& path, int x1, int y1, int x2, int y2)
	{
		int dx[] = { 0, -1,1,0,0 };
		int dy[] = { 0, 0,0,-1,1 };
		int rev[] = { 0,2,1,4,3 };
		memset(vis, 0, sizeof(vis));
		using Tri = std::tuple<int, int, int>;
		std::priority_queue<Tri, std::vector< Tri>, std::greater<Tri>> q;
		q.push({ abs(x1 - x2) + abs(y1 - y2),x1,y1 });
		vis[x1][y1] = 1;
		bool ok = false;
		while (!q.empty())
		{
			auto [d, x, y] = q.top();
			q.pop();

			for (int i = 1; i <= 4; i++)
			{
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (vis[nx][ny] || nx < 0 || ny < 0 || nx >= map.width || ny >= map.hight || map.content[ny][nx])continue;

				q.push({ abs(nx - x2) + abs(ny - y2),nx,ny });
				track[nx][ny] = rev[i];
				vis[nx][ny] = 1;
				if (nx == x2 && ny == y2) {
					ok = true; break;
				}
			}
			if (ok) break;
		}
		if (!ok)return ok;

		while (x2 != x1 || y2 != y1)
		{
			int dir = track[x2][y2];
			path.push_back(rev[dir]);
			x2 += dx[dir];
			y2 += dy[dir];
		}
		return true;
	}
}
