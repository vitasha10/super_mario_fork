#include "qt_box.hpp"

using biv::QtBox;

QtBox::QtBox(const Coord& top_left, const int width, const int height)
    : Box(top_left, width, height) {}

QColor QtBox::get_color() const noexcept {
    return QColor(139, 90, 43); // Brown
}
