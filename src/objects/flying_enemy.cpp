#include "flying_enemy.hpp"

#include <algorithm>

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(
	const Coord& top_left, const int width, const int height,
	const float amplitude
) : Enemy(top_left, width, height), initial_y(top_left.y), amplitude(amplitude) {
	vspeed = 0.25f;
	hspeed = 0.15f;
}

void FlyingEnemy::move_vertically() noexcept {
	const float min_y = std::max(MIN_Y, initial_y - amplitude);
	const float max_y = initial_y + amplitude;

	top_left.y += vspeed;
	if (top_left.y < min_y) {
		top_left.y = min_y;
		vspeed = -vspeed;
	} else if (top_left.y > max_y) {
		top_left.y = max_y;
		vspeed = -vspeed;
	}
}

void FlyingEnemy::process_vertical_static_collision(Rect* /*obj*/) noexcept {
	// Учитываем столкновение только сменой направления полёта.
	top_left.y -= vspeed;
	vspeed = -vspeed;
}
