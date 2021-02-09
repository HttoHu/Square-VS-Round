#pragma once
#include <SDL.h>
#include <vector>
#include <string>


namespace tools {
	const long double PI = 3.14159265358979323846;
	std::pair<int, int> get_cursor_pos();
	void rotate_pic(SDL_Texture* texture, int x, int y, double angle);

	bool test_pos(int x, int y, int w, int h,int x0,int y0);

	double sin(double x);
	double cos(double x);
	double get_angle(double x1, double y1, double x2, double y2);
	void set_dx_dy_by_angle(double& dx, double& dy, double angle,double speed);
	void draw_rect(int x, int y, int w, int h, int color);
	void draw_empty_rect(int x, int y, int w, int h, int color);


	std::wstring string_to_wstring(const std::string& content);
	std::string wstring_to_string(const std::wstring& content);

}