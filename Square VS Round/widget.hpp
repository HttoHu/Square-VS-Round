#pragma once
#include <SDL.h>
#include <functional>
#include <SDL_ttf.h>
#include <string>
namespace Widgets
{
	enum ColorTag {
		BLACK,WHITE
	};
	enum FontSize {
		BIG,NORMAL,SMALL
	};
	struct ColorRGB {
		int r;
		int g;
		int b;
	};
	ColorRGB get_color_rgb(ColorTag color_tag);
	SDL_Color to_sdl_color(ColorRGB color);

	// test functions
	void print_text(int x, int y, uint16_t* str);
	void print_text(int x, int y, const std::string& str);
	namespace vars
	{
		void init_ttf(int font_size=12);
		extern TTF_Font* main_font;
		extern TTF_Font* big_font;
		extern TTF_Font* small_font;
	}

	class TextBlock
	{
	public:
		TextBlock(FontSize font_size);
		void reset_content(const std::string& str) { content = str; }
		void reset_pos(int nx, int ny) { x = nx, y = ny;  }
		void show();
	private:
		TTF_Font* font;
		std::string content;
		int x = 0;
		int y = 0;
	};

	class Image {
	public:
		Image(const std::string&pic_str);
		void show();
		void set_pos(int _x, int _y) { x = _x, y = _y; }
		void change_pic(const std::string& pic_str);

		~Image();
	private:
		SDL_Texture* texture;
		int x=0, y=0;
	};
}
