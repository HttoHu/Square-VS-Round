#include "../includes/game_map.hpp"
#include "../includes/draw.hpp"
#include <fstream>
#include <queue>
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
namespace tools
{

    std::pair<int, int> getPos(int x, int y, int dir) {
        int moveX[4] = { 1, -1, 0, 0 };
        int moveY[4] = { 0, 0, -1, 1 };
        return std::make_pair(x + moveX[dir - 1], y + moveY[dir - 1]);
    }

    // 1 -> LEFT 
    // 2 -> RIGHT
    // 3 -> UP
    // 4 -> DOWN
    bool count_shortest_path(const Map& map, std::vector<int>& path, int x1, int y1, int x2, int y2)
    {
        std::queue<std::pair<int, int> > q;
        bool vis[50][50] = { 0 };
        int tmp[50][50] = { 0 };
        int moveX[4] = { -1, 1, 0, 0 };
        int moveY[4] = { 0, 0, -1, 1 };
        int rvs[4] = { 2, 1, 4, 3 };
        int ok = 0;
        q.push(std::make_pair(x1, y1));
        vis[x1][y1] = 1;
        while (!q.empty())
        {
            int curX = q.front().first;
            int curY = q.front().second;
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                int nxtX = curX + moveX[i];
                int nxtY = curY + moveY[i];
                if (nxtX >= 0 && nxtX < map.width && nxtY >= 0 && nxtY < map.hight && !map.content[nxtY][nxtX] && !vis[nxtX][nxtY])
                {
                    q.push(std::make_pair(nxtX, nxtY));
                    vis[nxtX][nxtY] = 1;
                    tmp[nxtX][nxtY] = rvs[i];
                    if (nxtX == x2 && nxtY == y2)
                    {
                        ok = 1;
                        break;
                    }
                }
            }
            if (ok)
                break;
        }
        if (!ok) return 0;
        std::deque<int> reV;
        int curX = x2, curY = y2;
        while (curX != x1 || curY != y1)
        {
            reV.push_front(tmp[curX][curY]);
            std::pair<int, int> ch = getPos(curX, curY, tmp[curX][curY]);
            curX = ch.first;
            curY = ch.second;
        }
        for (int i = 0; i < reV.size(); i++)
        {
            path.push_back(rvs[reV[i] - 1]);
        }
        return 1;
    }
}
