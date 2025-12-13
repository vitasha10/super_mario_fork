#include "qt_game_widget.hpp"

#include <QKeyEvent>
#include <QPainter>
#include <QPaintEvent>

#include "qt_game_map.hpp"
#include "input_bridge.hpp"

using biv::QtGameWidget;

QtGameWidget::QtGameWidget(biv::QtGameMap* map, QWidget* parent)
        : QWidget(parent), map(map) {
        setFocusPolicy(Qt::StrongFocus);
        setWindowTitle("Super Mario (Qt)");
}

void QtGameWidget::paintEvent(QPaintEvent*) {
        if (map == nullptr) {
                return;
        }

        const int scale = map->get_scale();
        const int water_height = 3 * scale;
        const int water_start_y = map->get_view_height() - water_height;

        QPainter painter(this);
        painter.fillRect(rect(), QColor(16, 18, 48));
        painter.fillRect(0, water_start_y, map->get_view_width(), water_height, QColor(0, 114, 206));

        for (const auto* obj: map->get_objects()) {
                const int left = obj->get_left() * scale;
                const int top = obj->get_top() * scale;
                const int width = (obj->get_right() - obj->get_left()) * scale;
                const int height = (obj->get_bottom() - obj->get_top()) * scale;
                painter.fillRect(left, top, width, height, obj->get_color());
        }
}

void QtGameWidget::keyPressEvent(QKeyEvent* event) {
        if (event->isAutoRepeat()) {
                QWidget::keyPressEvent(event);
                return;
        }

        switch (event->key()) {
                case Qt::Key_Left:
                case Qt::Key_A:
                        biv::os::set_input_state(biv::os::UserInput::MAP_LEFT, true);
                        break;
                case Qt::Key_Right:
                case Qt::Key_D:
                        biv::os::set_input_state(biv::os::UserInput::MAP_RIGHT, true);
                        break;
                case Qt::Key_Space:
                case Qt::Key_W:
                case Qt::Key_Up:
                        biv::os::set_input_state(biv::os::UserInput::MARIO_JUMP, true);
                        break;
                case Qt::Key_Escape:
                        biv::os::set_input_state(biv::os::UserInput::EXIT, true);
                        break;
                default:
                        break;
        }

        QWidget::keyPressEvent(event);
}

void QtGameWidget::keyReleaseEvent(QKeyEvent* event) {
        if (event->isAutoRepeat()) {
                QWidget::keyReleaseEvent(event);
                return;
        }

        switch (event->key()) {
                case Qt::Key_Left:
                case Qt::Key_A:
                        biv::os::set_input_state(biv::os::UserInput::MAP_LEFT, false);
                        break;
                case Qt::Key_Right:
                case Qt::Key_D:
                        biv::os::set_input_state(biv::os::UserInput::MAP_RIGHT, false);
                        break;
                case Qt::Key_Space:
                case Qt::Key_W:
                case Qt::Key_Up:
                        biv::os::set_input_state(biv::os::UserInput::MARIO_JUMP, false);
                        break;
                case Qt::Key_Escape:
                        biv::os::set_input_state(biv::os::UserInput::EXIT, false);
                        break;
                default:
                        break;
        }

        QWidget::keyReleaseEvent(event);
}
