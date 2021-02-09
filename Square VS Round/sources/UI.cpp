#include "../includes/UI.hpp"
#include "../includes/utility.hpp"
#include "../includes/draw.hpp"
#include "../includes/game.hpp"
#include "../includes/test.hpp"
namespace UI
{
	namespace MainPage {
		std::vector<Widgets::Button*> buttons;
		bool exit_flag = false;
		// click events
		namespace {
			Widgets::Image* logo;

			void click_start_game(Widgets::Button* button)
			{
				app.game_init();
				test::test_init();
				auto upd = []() {
					do_input();
					app.update();
					test::test_update();
					Screen::draw_objects();
				};
				bool tmp = false;
				run_page(tmp,upd);
			}

			void click_help_button(Widgets::Button* button)
			{

			}

			void click_exit_game(Widgets::Button* button)
			{
				exit(0);
			}

			void process_mouse(SDL_MouseButtonEvent* event)
			{
				if (event->button == SDL_BUTTON_LEFT)
				{
					auto pos = tools::get_cursor_pos();
					for (auto button : buttons)
					{
						if (button->test_pos(pos.first, pos.second))
						{
							button->click_button();
							return;
						}
					}
				}
			}
			void process_mouse_motion(SDL_MouseMotionEvent* event)
			{
				for (auto button : buttons)
				{
					button->move_flag = button->test_pos(event->x, event->y);
				}
			}
		}
		void add_button(int x, int y, const std::string& str, const std::function<void(Widgets::Button*)>& click_event)
		{
			using namespace Widgets;
			Button* button = new Button(x, y, str, ColorTag::BLACK, FontSize::NORMAL);
			button->set_click(click_event);
			buttons.push_back(button);
		}
		void init()
		{
			using namespace Widgets;
			logo = new Image("../assets/logo.png");
			logo->set_pos(500, 110);

			add_button(550, 400, "开始游戏", click_start_game);
			add_button(550, 460, "游戏说明", click_help_button);
			add_button(550, 520, "退出游戏", click_exit_game);

		}
		void update()
		{
			logo->show();
			for (auto a : buttons)
				a->show();
			process_input();
		}
		void process_input()
		{
			SDL_Event event;

			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					exit(0);
					break;
				case SDL_MOUSEMOTION:
					process_mouse_motion(&event.motion);
					break;
				case SDL_MOUSEBUTTONDOWN:
					process_mouse(&event.button);
					break;
				default:
					break;
				}
			}
		}
	}
	void run_page(bool& flag, const std::function<void()>& body)
	{
		long then;
		float remainer;
		then = SDL_GetTicks();
		remainer = 0;


		while (1) {
			if (flag)
			{
				flag = false;
				return;
			}
			Screen::prepare_screen();
			body();
			Screen::update_screen();
			Screen::cap_frame_rate(then, remainer);
		}
	}
}
