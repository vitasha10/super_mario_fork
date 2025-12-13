#include "second_level.hpp"

#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool SecondLevel::is_final() const noexcept {
	return false;
}

biv::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);
	
	ui_factory->create_ship({20, 25}, 40, 2);
	ui_factory->create_box({25, 18}, 10, 2);
	ui_factory->create_money({28, 12}, 3, 2);
	ui_factory->create_ship({60, 20}, 10, 7);
	ui_factory->create_full_box({70, 14}, 4, 3);
	ui_factory->create_enemy({55, 12}, 3, 2);
	ui_factory->create_ship({80, 25}, 20, 2);
	ui_factory->create_box({90, 18}, 8, 2);
	ui_factory->create_jumping_enemy({95, 16}, 3, 3);
	ui_factory->create_ship({120, 20}, 10, 7);
	ui_factory->create_flying_enemy({110, 8}, 3, 2);
	ui_factory->create_money({125, 10}, 3, 2);
	ui_factory->create_ship({150, 25}, 40, 2);
	ui_factory->create_full_box({160, 15}, 4, 3);
	ui_factory->create_enemy({170, 12}, 3, 2);
	ui_factory->create_ship({210, 20}, 10, 7);
}
