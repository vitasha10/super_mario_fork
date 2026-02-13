#pragma once

#include "qt_ui_obj_rect_adapter.hpp"
#include "flying_enemy.hpp"

namespace biv {
    class QtFlyingEnemy : public FlyingEnemy, public QtUIObjectRectAdapter {
    public:
        QtFlyingEnemy(const Coord& top_left, const int width, const int height);
        QColor get_color() const noexcept override;
    };
}
