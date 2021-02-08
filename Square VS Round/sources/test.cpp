#include "../includes/test.hpp"
#include "../includes/utility.hpp"
#include "../includes/game_map.hpp"
#include "../includes/square.hpp"
#include "../includes/bullet.hpp"
#include "../includes/game.hpp"
namespace test
{

	std::vector<Square*> enemys;
	std::vector<Walker*> walkers;
	void gen_enemy(int _x,int _y) {
		Square* enemy=new Square(_x, _y, "eny");
		enemy->team_id = 2;
		Walker* enemy_walker= new Walker(enemy, 2);
		vars::stage.players.push_back(enemy);
		enemys.push_back(enemy);
		walkers.push_back(enemy_walker);
	}
	void test::test_init()
	{		
		for (int i = 1; i <= 8; i++)
		{
			auto pos = app.game_map->gen_space(i*10);
			gen_enemy(pos.first, pos.second);
		}
	}
	void test_update()
	{
		for (int i = 0; i < enemys.size(); i++)
		{
			Square* enemy = enemys[i];
			Walker* enemy_walker = walkers[i];


			if (enemy->bullet_cnt >= 100)
			{
				enemy->bullet_cnt -= 100;
				Bullet* bul = new Bullet("../assets/square_bullet.png");
				bul->force = 10;
				double ang = tools::get_angle(enemy->pos.x, enemy->pos.y, vars::player->pos.x, vars::player->pos.y);
				tools::set_dx_dy_by_angle(bul->dx, bul->dy, ang, 2);
				enemy->fire(bul);
			}
			if (enemy_walker->update() == -1)
			{
				int x1 = enemy->get_center_x() / BRICK_SIZE;
				int y1 = enemy->get_center_y() / BRICK_SIZE;

				int x2 = vars::player->get_center_x() / BRICK_SIZE;
				int y2 = vars::player->get_center_y() / BRICK_SIZE;
				tools::count_shortest_path(*app.game_map, enemy_walker->walk_ins, x1, y1, x2, y2);
			}
		}
	}
}