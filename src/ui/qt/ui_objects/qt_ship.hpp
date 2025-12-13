#pragma once

#include <QColor>

#include "coord.hpp"
#include "qt_ui_obj_rect_adapter.hpp"
#include "ship.hpp"

namespace biv {
        class QtShip : public Ship, public QtUIObjectRectAdapter {
        public:
                QtShip(const Coord& top_left, const int width, const int height);

                QColor get_color() const noexcept override;
        };
}
