#include "flying_enemy.hpp"

#include <algorithm>

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(
	const Coord& top_left, const int width, const int height,
	const float amplitude
) : RectMapMovableAdapter(top_left, width, height), initial_y(top_left.y), amplitude(amplitude) {
	vspeed = 0.25f;
	hspeed = 0.15f;
}

biv::Rect FlyingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyingEnemy::process_horizontal_static_collision(Rect*) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
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

void FlyingEnemy::process_vertical_static_collision(Rect*) noexcept {
	// Учитываем столкновение только сменой направления полёта.
	top_left.y -= vspeed;
	vspeed = -vspeed;
}
