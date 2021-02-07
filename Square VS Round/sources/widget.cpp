#include "../includes/widget.hpp"
#include "../includes/game.hpp"
#include "../includes/draw.hpp"
#include <cstdio>
#include <iostream>
#include <map>
namespace Widgets
{
	namespace vars
	{
		TTF_Font* main_font=nullptr;
		TTF_Font* big_font=nullptr;
		TTF_Font* small_font=nullptr;
	}


	void vars::init_ttf(int font_size)
	{
		if (TTF_Init() == -1)
		{
			printf("SDL TTF INIT FAILED\n");
			exit(1);
		}
		main_font = TTF_OpenFont("../assets/font.otf", 22);
		big_font = TTF_OpenFont("../assets/font.otf", 35);
		small_font=TTF_OpenFont("../assets/font.otf", 18);
		if (!main_font) {
			printf("Open font failed\n");
			exit(1);
		}
	}

	ColorRGB get_color_rgb(ColorTag color_tag)
	{
		const std::map<ColorTag, ColorRGB> table = {
			{ColorTag::WHITE,ColorRGB{255,255,255}},{ColorTag::BLACK,ColorRGB{0,0,0}},
			{ColorTag::GREEN,ColorRGB{56,208,78}},{ColorTag::RED,ColorRGB{236,53,53}},
			{ColorTag::PINK,ColorRGB{255,174,200}}
		};
		auto res = table.find(color_tag);
		if (res == table.end())
		{
			printf("unknown color\n");
			exit(1);
		}
		return res->second;
	}
	
	SDL_Color to_sdl_color(ColorRGB color)
	{
		return { (uint8_t)color.r,(uint8_t)color.g,(uint8_t)color.b };
	}
	void print_text(int x, int y, uint16_t* str) {
		auto color = to_sdl_color(get_color_rgb(BLACK));
		SDL_Surface* surface = TTF_RenderUNICODE_Blended(vars::main_font, str, color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(app.renderer, surface);
		Screen::blit_static(texture, x, y);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
	void print_text(int x, int y, const std::string& str)
	{
		auto color = to_sdl_color(get_color_rgb(GREEN));
		SDL_Surface* surface = TTF_RenderUTF8_Blended(vars::main_font, str.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(app.renderer, surface);
		Screen::blit_static(texture,x,y);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
	TextBlock::TextBlock(FontSize font_size)
	{
		switch (font_size)
		{
		case Widgets::BIG:
			font = vars::big_font;
			break;
		case Widgets::NORMAL:
			font = vars::main_font;
			break;
		case Widgets::SMALL:
			font = vars::small_font;
			break;
		default:
			printf("Error Font\n");
			exit(1);
		}
	}
	void TextBlock::show()
	{
		print_text(x, y, content);
	}
	Image::Image(const std::string & pic_str)
	{
		texture = Screen::load_texture(pic_str);
	}
	void Image::show()
	{
		Screen::blit_static(texture, x, y);
	}
	void Image::change_pic(const std::string& pic_str)
	{
		SDL_DestroyTexture(texture);
		texture = Screen::load_texture(pic_str);
	}
	Image::~Image()
	{
		SDL_DestroyTexture(texture);
	}
}