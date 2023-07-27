#pragma once
#include <SDL.h>
#include <functional>
#include <SDL_ttf.h>
#include <string>
namespace Widgets
{
    enum ColorTag
    {
        BLACK,
        WHITE,
        GREEN,
        RED,
        PINK
    };
    enum FontSize
    {
        BIG,
        NORMAL,
        SMALL
    };
    struct ColorRGB
    {
        int r;
        int g;
        int b;
    };
    ColorRGB get_color_rgb(ColorTag color_tag);
    SDL_Color to_sdl_color(ColorRGB color);

    SDL_Texture *print_text(const std::wstring &str, TTF_Font *, ColorTag color = BLACK);
    SDL_Texture *print_text(const std::string &str, TTF_Font *, ColorTag color = BLACK);
    TTF_Font *get_font_by_size(FontSize);
    namespace vars
    {
        void init_ttf(int font_size = 12);
        extern TTF_Font *main_font;
        extern TTF_Font *big_font;
        extern TTF_Font *small_font;
    }
    class Widget
    {
    public:
        virtual ~Widget() {}
        virtual void show();
        void set_width_hight();
        void reset_pos(int nx, int ny) { x = nx, y = ny; }
        int get_height()
        {
            return h;
        }
        int get_width()
        {
            return w;
        }
        int w = 0, h = 0, x = 0, y = 0;
        SDL_Texture *texture = nullptr;
    };
    class TextBlock : public Widget
    {
    public:
        TextBlock(FontSize font_size, const std::wstring &str);

        void reprint();
        void reset_content(const std::wstring &str) { content = str; }
        void reset_content(const std::string &str);
        void reset_color(ColorTag c) { foreground = c; }

        ~TextBlock() { SDL_DestroyTexture(texture); }

    private:
        ColorTag foreground = BLACK;
        TTF_Font *font;
        std::wstring content;
    };

    class Image
    {
    public:
        Image(const std::string &pic_str);
        void show();
        void set_pos(int _x, int _y) { x = _x, y = _y; }
        void change_pic(const std::string &pic_str);
        int get_width();
        int get_hight();
        ~Image();

    private:
        SDL_Texture *texture;
        int x = 0, y = 0;
    };

    class Button
    {
    public:
        Button(int x, int y, const std::string &_str, ColorTag co, FontSize sz = NORMAL);
        void click_button() { click(this); }
        void set_click(const std::function<void(Button *)> &func) { click = func; }
        void show();
        bool test_pos(int x, int y);

        void move_here();
        bool move_flag = false;
        TextBlock *content;

    private:
        std::function<void(Button *)> click;
    };
}
