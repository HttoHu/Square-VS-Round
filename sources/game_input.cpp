#include <SDL.h>
#include "../includes/game.hpp"
#include "../includes/defs.hpp"
#include "../includes/objects.hpp"
#include "../includes/utility.hpp"
#include "../includes/round.hpp"
#include "../includes/bullet.hpp"

void process_keydown(SDL_KeyboardEvent *event) {
	if (event->repeat == 0)
	{
		app.keyboard[event->keysym.scancode] = 1;
	}

}

void process_keyup(SDL_KeyboardEvent* event)
{
	if (event->repeat == 0)
	{
		app.keyboard[event->keysym.scancode] = 0;
	}
}

void process_mouse(SDL_MouseButtonEvent* event)
{
	if (event->button == SDL_BUTTON_LEFT)
	{
		if (vars::player->bullet_cnt >= 100)
		{
			vars::player->bullet_cnt -= 100;
			auto pos = tools::get_cursor_pos();
			app.target = { (double)pos.first,(double)pos.second };
			// printf("Target :%llf, %llf\n", app.target.x, app.target.y);
			vars::player->aim({ app.target.x + app.camera.x,app.target.y + app.camera.y });
			vars::player->fire(new Bullet("../assets/round_bullet.png"));
		}
	}
}

void do_input()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			process_keydown(&event.key);
			break;
		case SDL_KEYUP:
			process_keyup(&event.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
			process_mouse(&event.button);
			break;
		default:
			break;
		}
	}
}
