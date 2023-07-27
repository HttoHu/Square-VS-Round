#include "../includes/test.hpp"
#include "../includes/utility.hpp"
#include "../includes/game_map.hpp"
#include "../includes/widget.hpp"
#include "../includes/smile.hpp"
#include "../includes/bullet.hpp"
#include "../includes/draw.hpp"
#include "../includes/game.hpp"
namespace test
{
	int player_score = 0;
	int start_time = 0;

	std::vector<Smile*> enemys;
	std::vector<Walker*> walkers;
	void gen_enemy(int _x,int _y) {
		Smile* enemy=new Smile(_x, _y, "eny");
		enemy->team_id = 2;
		Walker* enemy_walker= new Walker(enemy, 2);
		vars::stage.players.push_back(enemy);
		enemys.push_back(enemy);
		walkers.push_back(enemy_walker);
	}

	void test::test_init()
	{		
		start_time = SDL_GetTicks();
		for (int i = 1; i <= 3; i++)
		{
			auto pos = app.game_map->gen_space(i*10);
			gen_enemy(pos.first, pos.second);
		}
	}
	void test_update()
	{
		while (SDL_GetTicks() - start_time >= 20000 || enemys.size()<3)
		{
			auto pos = app.game_map->gen_space(rand()%200);
			gen_enemy(pos.first, pos.second);

			start_time = SDL_GetTicks();
		}
		if (vars::player->level<4 && player_score > vars::player->level * 15)
		{
			player_score -= vars::player->level * 15;
			vars::player->upgrade();
		}
		if (vars::player->level==4 && player_score >= 40)
		{
			Screen::prepare_screen();
			auto texture = Widgets::print_text("Win, the game will exit after 9 secs", Widgets::get_font_by_size(Widgets::BIG));
			Screen::blit_static(texture, 500, 300);
			Screen::update_screen();
			for (int i = 1; i < 300; i++)
			{
				do_input();
				SDL_Delay(30);
			}
			exit(0);
		}
		else if (vars::player->hp <= 0)
		{
			Screen::prepare_screen();
			auto texture = Widgets::print_text("Lost, the game will exit after 9 secs", Widgets::get_font_by_size(Widgets::BIG));
			Screen::blit_static(texture, 500, 300);
			do_input();
			Screen::update_screen();
			for (int i = 1; i < 100; i++)
			{
				do_input();
				SDL_Delay(30);
			}
			exit(0);
		}
		for (int i = 0; i < enemys.size(); i++)
		{
			Smile* enemy = enemys[i];
			Walker* enemy_walker = walkers[i];

			if (enemy->hp <= 0)
			{
				std::swap(enemys[i], enemys.back());
				std::swap(walkers[i], walkers.back());
				delete walkers.back();
				delete enemys.back();
				walkers.pop_back();
				enemys.pop_back();
				player_score += 10;
				continue;
			}
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