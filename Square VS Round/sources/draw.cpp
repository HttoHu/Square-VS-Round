#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "../includes/defs.hpp"
#include "../includes/game.hpp"
#include "../includes/objects.hpp"
#include "../includes/player.hpp"
#include "../includes/widget.hpp"
#include "../includes/utility.hpp"
#include "../includes/game_map.hpp"
void Screen::prepare_screen()
{
	static int a = 255, b = 255, c = 255, d = 255;
	SDL_SetRenderDrawColor(app.renderer, a, b, c, d);
	SDL_RenderClear(app.renderer);
}
void Screen::update_screen() {
	SDL_RenderPresent(app.renderer);
}
SDL_Texture* Screen::load_texture(const std::string& filename)
{
	SDL_Texture* texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename.c_str());

	texture = IMG_LoadTexture(app.renderer, filename.c_str());

	return texture;
}

void Screen::blit(SDL_Texture* texture, int x, int y)
{
	SDL_Rect dest;
	dest.x = x-app.camera.x;
	dest.y = y-app.camera.y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void Screen::blit_static(SDL_Texture* texture, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void Screen::cap_frame_rate(long& then, float& remainder)
{
	long wait, frameTime;
	wait = 16 + remainder;
	remainder -= (int)remainder;
	frameTime = SDL_GetTicks() - then;
	wait -= frameTime;
	if (wait < 1)
	{
		wait = 1;
	}
	SDL_Delay(wait);
	remainder += 0.667;
	then = SDL_GetTicks();
}

void Screen::draw_objects()
{
	// Show map and objects
	app.game_map->show();
	vars::stage.draw_players();
	vars::stage.draw_bullets();
	// show mouse
	auto mouse_pos = tools::get_cursor_pos();
	vars::cursor->pos = { (double)mouse_pos.first,(double)mouse_pos.second };
	vars::cursor->show();
	// show tool bar
	static bool Q_enable = vars::player->skill_enable(1);
	static bool E_enable = vars::player->skill_enable(2);
	static bool R_enable = vars::player->skill_enable(3);
	auto skill_state_show = [](int skill_no, bool& last_state, Widgets::Image* image, const std::string& enable_image, const std::string& dis_able_image) {
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
	// ----------------------Property------------------------
	app.property->reset_content("HP : " + std::to_string(vars::player->hp) + "      Lv :  " + std::to_string(vars::player->level));
	app.property->show();
	app.split_line->show();
}
