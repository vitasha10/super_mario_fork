#include "qt_game_map.hpp"

#include <algorithm>

#include "qt_game_widget.hpp"

using biv::QtGameMap;

QtGameMap::QtGameMap(const int height, const int width, QWidget* parent)
        : GameMap(height, width), scale(6) {
        configure_widget(parent);
}

QtGameMap::~QtGameMap() {
        delete view;
}

void QtGameMap::add_obj(biv::QtUIObject* obj) {
        objs.push_back(obj);
}

void QtGameMap::clear() noexcept {}

int QtGameMap::get_scale() const noexcept {
        return scale;
}

int QtGameMap::get_view_height() const noexcept {
        return height * scale;
}

int QtGameMap::get_view_width() const noexcept {
        return width * scale;
}

const std::vector<biv::QtUIObject*>& QtGameMap::get_objects() const noexcept {
        return objs;
}

void QtGameMap::refresh() noexcept {
        if (view != nullptr) {
                view->update();
        }
}

void QtGameMap::remove_obj(biv::QtUIObject* obj) {
        objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
}

void QtGameMap::remove_objs() {
        objs.clear();
}

void QtGameMap::show() const noexcept {
        if (view != nullptr) {
                view->show();
                view->update();
        }
}

QWidget* QtGameMap::widget() const noexcept {
        return view;
}

void QtGameMap::close_widget() const noexcept {
        if (view != nullptr) {
                view->close();
        }
}

void QtGameMap::configure_widget(QWidget* parent) {
        view = new QtGameWidget(this, parent);
        view->setFixedSize(get_view_width(), get_view_height());
}
