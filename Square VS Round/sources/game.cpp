#include "../includes/game.hpp"
#include "../includes/defs.hpp"
#include "../includes/utility.hpp"
#include "../includes/bullet.hpp"
#include "../includes/player.hpp"
#include "../includes/round.hpp"
#include "../includes/widget.hpp"
#include "../includes/game_map.hpp"
void Stage::draw_players()
{
	for (std::list<Player*>::iterator it = players.begin(); it != players.end();)
	{
		if ((*it)->hp <= 0)
			players.erase(it++);
		else
		{
			(*it)->show();
			it++;
		}
	}
}

void Stage::draw_bullets()
{
	for (std::list<Entity*>::iterator it = bullets.begin(); it != bullets.end(); it++)
	{
		Bullet* bul = static_cast<Bullet*>(*it);
		bul->show();
		if (bul->bad_pos() || !bul->alive)
		{
			bullets.erase(it++);
			delete bul;
			if (it == bullets.end())
				return;

		}
	}
}

void player_update() {
	double dx = 0;
	double dy = 0;

	Player* p = vars::player;
	if (app.keyboard[SDL_SCANCODE_Q])
		p->skill_run(1);
	if (app.keyboard[SDL_SCANCODE_E])
		p->skill_run(2);

	static Pos last_dest_pos = { 0.0,0.0 };
	static double ang = 0.0;
	// Q Skill
	int move_speed = vars::player->move_speed;
	// keyboad move
	if (app.keyboard[SDL_SCANCODE_W] || app.keyboard[SDL_SCANCODE_S] || app.keyboard[SDL_SCANCODE_D] || app.keyboard[SDL_SCANCODE_A])
	{
		app.dest_pos_valid = false;
		dx = (double)(app.keyboard[SDL_SCANCODE_D] - app.keyboard[SDL_SCANCODE_A]);
		dy = (double)(app.keyboard[SDL_SCANCODE_S] - app.keyboard[SDL_SCANCODE_W]);
		if (abs(dx) + abs(dy) == 2)
		{
			dx *= move_speed / sqrt(2.0);
			dy *= move_speed / sqrt(2.0);
		}
		else {
			dx *= move_speed;
			dy *= move_speed;
		}
	}
	// mouse move
	else if (app.dest_pos_valid && !p->pos.collide(app.dest_pos, move_speed))
	{
		if (!last_dest_pos.collide(app.dest_pos, 1.0))
		{
			ang = tools::get_angle(p->pos.x, p->pos.y, app.dest_pos.x, app.dest_pos.y);
			last_dest_pos = app.dest_pos;
		}
		dx = tools::sin(ang) * move_speed;
		dy = -tools::cos(ang) * move_speed;
	}
	else return;


	p->pos.x += dx;
	p->pos.y += dy;
	int del_x[] = { -1,0,-1 };
	int del_y[] = { 0,-1,-1 };
	if (p->bad_pos())
	{
		for (int i = 0; i < 3; i++)
		{
			double a = dx * del_x[i], b =  dy * del_y[i];
			p->pos.x += a;
			p->pos.y += b;
			if (p->bad_pos())
				p->pos.x -= a, p->pos.y -= b;
			else return;
		}
	}
}
void App::game_init()
{
	// init map
	app.game_map = new Map("map1.dat");
	app.game_map->show();
	// init cursor and play...
	vars::player = new Round((double)SCREEN_WIDTH / 2, (double)SCREEN_HEIGHT / 2, "player1");
	vars::player->upgrade();
	vars::player->upgrade();
	auto mouse_pos = tools::get_cursor_pos();
	vars::cursor = new Entity(mouse_pos.first, mouse_pos.second, "../assets/targetter.png");
	vars::cursor->set_static();
	vars::stage.players.push_back(vars::player);


	int bottom_ui_start = 10;
	// split line
	app.split_line = new Widgets::Image("../assets/property_split_line.png");;
	app.split_line->set_pos(0, 620);
	app.split_line->show();
	// property infomation
	app.property = new Widgets::TextBlock(Widgets::NORMAL);
	app.property->reset_content("HP: " + std::to_string(vars::player->hp) + "      Lv:  " + std::to_string(vars::player->level));
	app.property->reset_pos(bottom_ui_start, 670);
	app.property->show();
	bottom_ui_start += 260;


	// init skill states
	// ----- Q skill------
	app.Q_skill_tag = new Widgets::Image("../assets/Q_skill_disable.png");
	if (vars::player->skill_enable(1))
		app.Q_skill_tag->change_pic("../assets/Q_skill_able.png");
	app.Q_skill_tag->set_pos(bottom_ui_start, 650);
	app.Q_skill_tag->show();
	bottom_ui_start += 150;
	// ----- E skill ------
	app.E_skill_tag = new Widgets::Image("../assets/E_skill_disable.png");
	if (vars::player->skill_enable(2))
		app.E_skill_tag->change_pic("../assets/E_skill_able.png");
	app.E_skill_tag->set_pos(bottom_ui_start, 650);
	app.E_skill_tag->show();
	bottom_ui_start += 150;
	// ----- R skill ------
	app.R_skill_tag = new Widgets::Image("../assets/R_skill_disable.png");
	if (vars::player->skill_enable(3))
		app.R_skill_tag->change_pic("../assets/R_skill_able.png");
	app.R_skill_tag->set_pos(bottom_ui_start, 650);
	app.R_skill_tag->show();
	bottom_ui_start += 150;
}

void App::update()
{
	player_update();
	//=================================================================================
	app.camera = { vars::player->pos.x - (SCREEN_WIDTH / 2) ,vars::player->pos.y - (SCREEN_HEIGHT / 2) };
	// ======================process skill state =========================================
}

