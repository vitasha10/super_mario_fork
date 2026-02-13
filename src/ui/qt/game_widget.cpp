#include "game_widget.hpp"

#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>

using biv::GameWidget;

GameWidget::GameWidget(QWidget* parent) : QWidget(parent) {
    ui_factory = new QtUIFactory(&game);
    game_map = dynamic_cast<QtGameMap*>(ui_factory->get_game_map());
    game_level = new FirstLevel(ui_factory);
    mario = ui_factory->get_mario();

    setFixedSize(game_map->get_width() * CELL_SIZE, game_map->get_height_val() * CELL_SIZE);
    setWindowTitle("Super Mario");
    setFocusPolicy(Qt::StrongFocus);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWidget::game_tick);
    timer->start(TICK_MS);
}

GameWidget::~GameWidget() {
    delete game_level;
    delete ui_factory;
}

void GameWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    // Sky background
    painter.fillRect(rect(), QColor(135, 206, 235));

    // Draw game map
    game_map->paint(painter, CELL_SIZE);
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    pressed_keys.insert(event->key());
    QWidget::keyPressEvent(event);
}

void GameWidget::keyReleaseEvent(QKeyEvent* event) {
    pressed_keys.remove(event->key());
    QWidget::keyReleaseEvent(event);
}

void GameWidget::game_tick() {
    if (game.is_finished()) {
        timer->stop();
        QMessageBox::information(this, "Super Mario", "Game Over!");
        close();
        return;
    }

    handle_input();
    update_game_state();
    check_level_state();

    update();
}

void GameWidget::handle_input() {
    if (pressed_keys.contains(Qt::Key_A) || pressed_keys.contains(Qt::Key_Left)) {
        mario->move_map_left();
        if (!game.check_static_collisions(mario)) {
            game.move_map_left();
        }
        mario->move_map_right();
    }
    if (pressed_keys.contains(Qt::Key_D) || pressed_keys.contains(Qt::Key_Right)) {
        mario->move_map_right();
        if (!game.check_static_collisions(mario)) {
            game.move_map_right();
        }
        mario->move_map_left();
    }
    if (pressed_keys.contains(Qt::Key_Space) || pressed_keys.contains(Qt::Key_Up) || pressed_keys.contains(Qt::Key_W)) {
        mario->jump();
    }
    if (pressed_keys.contains(Qt::Key_Escape)) {
        game.finish();
    }
}

void GameWidget::update_game_state() {
    game.move_objs_horizontally();
    game.check_horizontally_static_collisions();

    game.move_objs_vertically();
    game.check_mario_collision();
    game.check_vertically_static_collisions();

    if (game_map->is_below_map(mario->get_top()) || !mario->is_active()) {
        game_level->restart();
        mario = ui_factory->get_mario();
    }
}

void GameWidget::check_level_state() {
    if (game.is_level_end()) {
        if (!game_level->is_final()) {
            game_level = game_level->get_next();
            mario = ui_factory->get_mario();
            current_level_num++;
            setWindowTitle(QString("Super Mario - Level %1").arg(current_level_num));
            game.start_level();
        } else {
            game.finish();
        }
    }
}
