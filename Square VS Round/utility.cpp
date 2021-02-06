#include "utility.hpp"
#include "game.hpp"
std::pair<int, int> tools::get_cursor_pos()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return { x,y };
}

void tools::rotate_pic(SDL_Texture* texture, int x, int y, double angle)
{
	SDL_Rect dstRect;

	dstRect.x = x;
	dstRect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);
	dstRect.x -= (dstRect.w / 2);
	dstRect.y -= (dstRect.h / 2);

	SDL_RenderCopyEx(app.renderer, texture, NULL, &dstRect, angle, NULL, SDL_FLIP_NONE);
}

double tools::sin(double x)
{
	return ::sin(x * PI / 180.0);
}

double tools::cos(double x)
{
	return ::cos(x * PI / 180.0);
}

double tools::get_angle(double x1, double y1, double x2, double y2)
{
	double angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
	return angle >= 0 ? angle : 360 + angle;
}

void tools::set_dx_dy_by_angle(double& dx, double& dy, double angle, double speed)
{
	dx = sin(angle) * speed;
	dy = -cos(angle) * speed;
}

