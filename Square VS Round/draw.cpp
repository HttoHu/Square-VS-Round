#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "defs.hpp"
#include "game.hpp"
#include "objects.hpp"
#include "utility.hpp"
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
	vars::stage.draw_players();
	vars::stage.draw_bullets();
	

	auto mouse_pos = tools::get_cursor_pos();
	vars::cursor->pos = { (double)mouse_pos.first,(double)mouse_pos.second };
	vars::cursor->show();
}
