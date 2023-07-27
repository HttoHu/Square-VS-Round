#pragma once
#include <SDL.h>
#include <string>
struct Screen {
	static void prepare_screen();
	static void update_screen();
	static SDL_Texture* load_texture(const std::string& filename);
	static void blit(SDL_Texture* texture, int x, int y);
	static void blit_static(SDL_Texture* texture, int x, int y);
	static void cap_frame_rate(long& then, float& remainder);

	static void draw_objects();
};
namespace tools {

}