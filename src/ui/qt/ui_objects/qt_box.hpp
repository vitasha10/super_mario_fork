#pragma once

#include "qt_ui_obj_rect_adapter.hpp"
#include "box.hpp"

namespace biv {
    class QtBox : public Box, public QtUIObjectRectAdapter {
    public:
        QtBox(const Coord& top_left, const int width, const int height);
        QColor get_color() const noexcept override;
    };
}
