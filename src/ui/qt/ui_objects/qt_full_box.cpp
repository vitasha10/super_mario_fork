#include "qt_full_box.hpp"

using biv::QtFullBox;

QtFullBox::QtFullBox(
        const Coord& top_left, const int width, const int height, UIFactory* factory
) : FullBox(top_left, width, height, factory) {}

QColor QtFullBox::get_color() const noexcept {
        return QColor(235, 120, 52);
}
