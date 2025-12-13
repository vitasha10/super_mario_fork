/**
	Игровой цикл - это обощённое представление потока событий, происходящих в игре.

	Игровой цикл:
		1. Установка параметров игры
		2. Получение пользовательского ввода
		3. Обновление внутреннего состояния игры
		4. Обновление изображения на экране
		5. Проверка того, не окончена ли игра

		*** Если игра не окончена, то возвращаемся в пункт № 2.

		6. Завершение
*/
#include <thread>

#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "game_map.hpp"
#include "mario.hpp"
#include "os_control_settings.hpp"
#include "ui_factory.hpp"
#include "user_input.hpp"

#ifdef BIV_USE_QT_UI
#include <QApplication>
#include <QTimer>

#include "qt_game_map.hpp"
#include "qt_ui_factory.hpp"
#else
#include "console_ui_factory.hpp"
#endif

#ifdef BIV_USE_QT_UI
int main(int argc, char* argv[]) {
	// 1. Установка параметров игры
	using namespace std::chrono_literals;
	biv::os::init_settings();

	QApplication app(argc, argv);

	biv::Game game;
	biv::UIFactory* ui_factory = new biv::QtUIFactory(&game);
	biv::GameMap* game_map = ui_factory->get_game_map();
	biv::GameLevel* game_level = new biv::FirstLevel(ui_factory);
	biv::Mario* mario = ui_factory->get_mario();
	constexpr int GAME_TICK_MS = 10;

	auto* qt_map = dynamic_cast<biv::QtGameMap*>(game_map);
	if (qt_map != nullptr && qt_map->widget() != nullptr) {
		qt_map->widget()->show();
		qt_map->widget()->setFocus();
	}

	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, [&]() {
		// 2. Получение пользовательского ввода
		biv::os::UserInput user_input = biv::os::get_user_input();
		switch (user_input) {
			case biv::os::UserInput::MAP_LEFT:
				mario->move_map_left();
				if (!game.check_static_collisions(mario)) {
					game.move_map_left();
				}
				mario->move_map_right();
				break;
			case biv::os::UserInput::MAP_RIGHT:
				mario->move_map_right();
				if (!game.check_static_collisions(mario)) {
					game.move_map_right();
				}
				mario->move_map_left();
				break;
			case biv::os::UserInput::MARIO_JUMP:
				mario->jump();
				break;
			case biv::os::UserInput::EXIT:
				game.finish();
				break;
			case biv::os::UserInput::NO_INPUT:
				break;
		}

		// 3. Обновление внутреннего состояния игры
		game.move_objs_horizontally();
		game.check_horizontally_static_collisions();

		game.move_objs_vertically();
		game.check_mario_collision();
		game.check_vertically_static_collisions();

		if (
			game_map->is_below_map(mario->get_top())
			|| !mario->is_active()
		) {
			game_level->restart();
			mario = ui_factory->get_mario();
			std::this_thread::sleep_for(1000ms);
		}

		if (game.is_level_end()) {
			if (!game_level->is_final()) {
				game_level = game_level->get_next();
				mario = ui_factory->get_mario();
				std::this_thread::sleep_for(1000ms);
				game.start_level();
			} else {
				game.finish();
			}
		}

		// 4. Обновление изображения на экране
		game_map->refresh();
		game_map->show();

		if (game.is_finished()) {
			timer.stop();
			if (qt_map != nullptr) {
				qt_map->close_widget();
			}
			app.quit();
		}
	});
	timer.start(GAME_TICK_MS);

	int result = app.exec();

	delete game_level;
	delete ui_factory;

	return result;
}
#else
int main() {
	// 1. Установка параметров игры
	using namespace std::chrono_literals;
	biv::os::init_settings();
	
	biv::Game game;
	biv::UIFactory* ui_factory = new biv::ConsoleUIFactory(&game);
	biv::GameMap* game_map = ui_factory->get_game_map();
	biv::GameLevel* game_level = new biv::FirstLevel(ui_factory);
	biv::Mario* mario = ui_factory->get_mario();
	
	biv::os::UserInput user_input;
	do {
		// 2. Получение пользовательского ввода	
		user_input = biv::os::get_user_input();
		switch (user_input) {
			case biv::os::UserInput::MAP_LEFT:
				mario->move_map_left();
				if (!game.check_static_collisions(mario)) {
					game.move_map_left();
				}
				mario->move_map_right();
				break;
			case biv::os::UserInput::MAP_RIGHT:
				mario->move_map_right();
				if (!game.check_static_collisions(mario)) {
					game.move_map_right();
				}
				mario->move_map_left();
				break;
			case biv::os::UserInput::MARIO_JUMP:
				mario->jump();
				break;
			case biv::os::UserInput::EXIT:
				game.finish();
				break;
			case biv::os::UserInput::NO_INPUT:
				break;
		}
		
		// 3. Обновление внутреннего состояния игры
		game.move_objs_horizontally();
		game.check_horizontally_static_collisions();
		
		game.move_objs_vertically();
		game.check_mario_collision();
		game.check_vertically_static_collisions();
		
		if (
			game_map->is_below_map(mario->get_top())
			|| !mario->is_active()
		) {
			game_level->restart();
			mario = ui_factory->get_mario();
			std::this_thread::sleep_for(1000ms);
		}
		
		if (game.is_level_end()) {
			if (!game_level->is_final()) {
				game_level = game_level->get_next();
				mario = ui_factory->get_mario();
				std::this_thread::sleep_for(1000ms);
				game.start_level();
			} else {
				game.finish();
			}
		}
		
		// 4. Обновление изображения на экране
		game_map->refresh();
		biv::os::set_cursor_start_position();
		game_map->show();
		std::this_thread::sleep_for(10ms);
	} while (
		/* 5. Проверка того, не окончена ли игра */ 
		!game.is_finished()
	);
	
	// 6. Завершение

	delete game_level;
	delete ui_factory;

	return 0;
}
#endif
