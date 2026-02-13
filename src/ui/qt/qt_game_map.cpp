#include "qt_game_map.hpp"

#include <algorithm>

using biv::QtGameMap;

QtGameMap::QtGameMap(const int height, const int width)
    : GameMap(height, width) {}

void QtGameMap::add_obj(QtUIObject* obj) {
    objs.push_back(obj);
}

void QtGameMap::clear() noexcept {}

void QtGameMap::refresh() noexcept {}

void QtGameMap::remove_obj(QtUIObject* obj) {
    objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
}

void QtGameMap::remove_objs() {
    objs.clear();
}

void QtGameMap::show() const noexcept {}

void QtGameMap::paint(QPainter& painter, int cell_size) const {
    // Draw water at bottom 3 rows
    painter.setBrush(QColor(64, 164, 223));
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, (height - 3) * cell_size, width * cell_size, 3 * cell_size);

    // Draw objects
    for (const QtUIObject* obj : objs) {
        int left = obj->get_left();
        int top_val = obj->get_top();
        int w = obj->get_right() - left;
        int h = obj->get_bottom() - top_val;

        painter.setBrush(obj->get_color());
        painter.setPen(Qt::NoPen);
        painter.drawRect(left * cell_size, top_val * cell_size, w * cell_size, h * cell_size);
    }
}

int QtGameMap::get_width() const noexcept {
    return width;
}

int QtGameMap::get_height_val() const noexcept {
    return height;
}

const std::vector<biv::QtUIObject*>& QtGameMap::get_objs() const {
    return objs;
}
