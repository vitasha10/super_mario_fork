#include "jumping_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(
	const Coord& top_left, const int width, const int height
) : RectMapMovableAdapter(top_left, width, height) {
	hspeed = 0.1f;
}

biv::Rect JumpingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed JumpingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void JumpingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void JumpingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void JumpingEnemy::move_vertically() noexcept {
	if (on_ground) {
		jump();
		on_ground = false;
	}
	Movable::move_vertically();
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	top_left.x += hspeed;
	if (!has_collision(obj)) {
		process_horizontal_static_collision(obj);
	} else {
		top_left.x -= hspeed;
	}
	
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
	on_ground = true;
}
