#include "structs.hpp"
#include "defs.hpp"
#include "utility.hpp"
#include "bullet.hpp"
#include "player.hpp"
#include "round.hpp"
#include "widget.hpp"
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
		if (bul->out_window() || !bul->alive)
		{
			bullets.erase(it++);
			delete bul;
			if (it == bullets.end())
				return;

		}
	}
}


void App::objects_init()
{
	// init cursor and play...
	vars::player = new Round((double)SCREEN_WIDTH/2,(double)SCREEN_HEIGHT/2, "player1");
	vars::player->upgrade();
	auto mouse_pos = tools::get_cursor_pos();
	vars::cursor = new Entity(mouse_pos.first, mouse_pos.second, "../assets/targetter.png");
	vars::stage.players.push_back(vars::player);


	int bottom_ui_start = 10;
	// split line
	app.split_line= new Widgets::Image("../assets/property_split_line.png");;
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
	app.property->reset_content("HP : " + std::to_string(vars::player->hp) + "      Lv :  " + std::to_string(vars::player->level));
	app.property->show();


	static bool Q_enable = vars::player->skill_enable(1);
	static bool E_enable = vars::player->skill_enable(2);
	static bool R_enable = vars::player->skill_enable(3);
	auto skill_state_show = [](int skill_no,bool &last_state, Widgets::Image * image,const std::string &enable_image,const std::string &dis_able_image) {
		if (vars::player->skill_enable(skill_no) != last_state)
		{
			last_state = vars::player->skill_enable(skill_no);
			if (last_state)
				image->change_pic(enable_image);
			else
				image->change_pic(dis_able_image);
		}
		image->show();
	};


	skill_state_show(1, Q_enable, app.Q_skill_tag, "../assets/Q_skill_able.png", "../assets/Q_skill_disable.png");
	skill_state_show(2, E_enable, app.E_skill_tag, "../assets/E_skill_able.png", "../assets/E_skill_disable.png");
	skill_state_show(3, R_enable, app.R_skill_tag, "../assets/R_skill_able.png", "../assets/R_skill_disable.png");

	app.split_line->show();
}

bool Pos::collide(Pos p, double eps)
{
	return abs(x - p.x) + abs(y - p.y) < eps;
}

double Pos::get_dis(Pos p)
{
	return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
}
