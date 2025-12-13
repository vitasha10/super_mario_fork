#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* ThirdLevel::get_next() {
	return next;
}

bool ThirdLevel::is_final() const noexcept {
	return true;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void ThirdLevel::init_data() {
	ui_factory->create_mario({10, 10}, 3, 3);

	ui_factory->create_ship({10, 24}, 30, 3);
	ui_factory->create_full_box({20, 14}, 4, 3);
	ui_factory->create_box({35, 18}, 10, 2);
	ui_factory->create_money({28, 10}, 3, 2);

	ui_factory->create_enemy({30, 11}, 3, 2);
	ui_factory->create_enemy({48, 15}, 3, 2);

	ui_factory->create_ship({55, 20}, 25, 2);
	ui_factory->create_full_box({70, 12}, 4, 3);
	ui_factory->create_box({78, 16}, 6, 2);

	ui_factory->create_flying_enemy({70, 6}, 3, 2);
	ui_factory->create_jumping_enemy({95, 18}, 3, 3);

	ui_factory->create_ship({90, 14}, 18, 3);
	ui_factory->create_money({96, 8}, 3, 2);

	ui_factory->create_ship({120, 22}, 18, 2);
	ui_factory->create_full_box({125, 10}, 4, 3);
	ui_factory->create_box({138, 14}, 8, 2);

	ui_factory->create_flying_enemy({140, 6}, 3, 2);
	ui_factory->create_jumping_enemy({150, 18}, 3, 3);
	ui_factory->create_enemy({132, 5}, 3, 2);

	ui_factory->create_ship({160, 20}, 18, 3);
	ui_factory->create_box({170, 12}, 6, 2);
	ui_factory->create_money({174, 8}, 3, 2);

	ui_factory->create_ship({185, 20}, 12, 7);
}
