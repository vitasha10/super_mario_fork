#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	class JumpingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			bool on_ground = true;

		public:
			JumpingEnemy(const Coord& top_left, const int width, const int height);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void move_vertically() noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
	};
}
