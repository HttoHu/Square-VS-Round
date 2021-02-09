#include "../includes/widget.hpp"
#include "../includes/game.hpp"
#include "../includes/utility.hpp"
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
		main_font = TTF_OpenFont("../assets/font.ttf", 22);
		big_font = TTF_OpenFont("../assets/font.ttf", 35);
		small_font=TTF_OpenFont("../assets/font.ttf", 18);
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

	TTF_Font* get_font_by_size(FontSize font_size)
	{
		const std::map<FontSize, TTF_Font*> table = {
			{FontSize::BIG,vars::big_font},{FontSize::NORMAL,vars::main_font},
			{FontSize::SMALL,vars::small_font}
		};
		auto res = table.find(font_size);
		if (res == table.end())
		{
			printf("unknown font\n");
			exit(1);
		}
		return res->second;
	}
	SDL_Texture* print_text( const std::wstring& str, TTF_Font*font, ColorTag c) {

		auto color = to_sdl_color(get_color_rgb(c));


		SDL_Surface* surface = TTF_RenderUNICODE_Blended(font, (uint16_t*)str.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(app.renderer, surface);

		SDL_FreeSurface(surface);
		return texture;
	}

	SDL_Texture* print_text(const std::string& str, TTF_Font* font,ColorTag c)
	{
		auto color = to_sdl_color(get_color_rgb(c));


		SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(app.renderer, surface);

		SDL_FreeSurface(surface);
		return texture;
	}



	void Widget::show()
	{
		Screen::blit_static(texture, x, y);
	}
	void Widget::set_width_hight()
	{
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	}

	TextBlock::TextBlock(FontSize font_size,const std::wstring&str):content(str)
	{
		font = get_font_by_size(font_size);
	}
	void TextBlock::reprint()
	{
		SDL_DestroyTexture(texture);
		texture = print_text(content, font, foreground);
		set_width_hight();
	}

	void TextBlock::reset_content(const std::string& str)
	{
		content = tools::string_to_wstring(str);
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





	Button::Button(int x,int y,const std::string & _str, ColorTag co, FontSize sz)
	{
		// set text
		content = new TextBlock(sz, tools::string_to_wstring(_str));
		content->reset_pos(x, y);
		content->reprint();


	}
	void Button::show()
	{
		if (move_flag)
			move_here();
		content->show();
	}
	bool Button::test_pos(int x0, int y0)
	{
		return tools::test_pos(content->x,content->y, content->get_width(), content->get_height(), x0, y0);
	}
	void Button::move_here()
	{
		tools::draw_empty_rect(content->x - 5, content->y - 5, content->w + 10, content->h + 10, BLACK);
	}
}