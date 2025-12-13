#pragma once

#include <QColor>

#include "coord.hpp"
#include "full_box.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
        class QtFullBox : public FullBox, public QtUIObjectRectAdapter {
        public:
                QtFullBox(
                        const Coord& top_left, const int width, const int height, UIFactory* factory
                );

                QColor get_color() const noexcept override;
        };
}
