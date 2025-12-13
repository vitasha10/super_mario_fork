#include "qt_mario.hpp"

using biv::QtMario;

QtMario::QtMario(const Coord& top_left, const int width, const int height)
        : Mario(top_left, width, height) {}

QColor QtMario::get_color() const noexcept {
        return QColor(208, 43, 43);
}
