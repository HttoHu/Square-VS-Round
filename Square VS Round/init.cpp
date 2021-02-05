#include <SDL.h>
#include <cstdio>
#include <SDL_image.h>
#include "defs.hpp"
#include "structs.hpp"
namespace Widgets
{
	namespace vars {
		void init_ttf(int font_size=20);
	}
}
void init_SDL(){
	int renderer_flags, windows_flags;
	renderer_flags = SDL_RENDERER_ACCELERATED;
	windows_flags = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("The program is broken");
		exit(1);
	}
	app.window = SDL_CreateWindow("Square VS Round", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,windows_flags);
	if (!app.window)
	{
		printf("The program is broken");
		exit(1);
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	app.renderer = SDL_CreateRenderer(app.window, -1, renderer_flags);
	if (!app.renderer)
	{
		printf("The program is broken");
		exit(1);
	}

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDL_ShowCursor(0);


	Widgets::vars::init_ttf();
}

void clean_up(void)
{
	SDL_DestroyRenderer(app.renderer);

	SDL_DestroyWindow(app.window);

	SDL_Quit();
}