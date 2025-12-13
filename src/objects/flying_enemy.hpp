#pragma once

#include "enemy.hpp"

namespace biv {
	class FlyingEnemy : public Enemy {
		private:
			float initial_y;
			float amplitude;

		public:
			FlyingEnemy(
				const Coord& top_left, const int width, const int height,
				const float amplitude = 5.0f
			);

			void move_vertically() noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
	};
}
