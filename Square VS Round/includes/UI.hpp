#pragma once
#include <SDL.h>
#include <vector>

#include "../includes/widget.hpp"

namespace UI
{

	void run_page(bool& flag, const std::function<void()>& body);
	namespace MainPage
	{
		extern std::vector<Widgets::Button*> buttons;
		extern bool exit_flag;
		void add_button(int x, int y, const std::string& str,const std::function<void(Widgets::Button*)> & click_event);

		void init();
		void update();

		void process_input();

	}

	namespace HelpPage
	{

	}
	namespace GameSelect
	{

	}
}