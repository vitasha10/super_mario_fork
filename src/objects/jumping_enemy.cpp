#include "jumping_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(
	const Coord& top_left, const int width, const int height
) : Enemy(top_left, width, height) {
	hspeed = 0.1f;
}

void JumpingEnemy::move_vertically() noexcept {
	if (on_ground) {
		jump();
		on_ground = false;
	}
	Movable::move_vertically();
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	Enemy::process_vertical_static_collision(obj);
	on_ground = true;
}
