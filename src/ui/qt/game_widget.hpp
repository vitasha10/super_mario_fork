#pragma once

#include <QWidget>
#include <QTimer>
#include <QSet>

#include "game.hpp"
#include "qt_ui_factory.hpp"
#include "qt_game_map.hpp"
#include "first_level.hpp"
#include "game_level.hpp"

namespace biv {
    class GameWidget : public QWidget {
        Q_OBJECT

    private:
        static const int CELL_SIZE = 16;
        static const int TICK_MS = 16;

        Game game;
        QtUIFactory* ui_factory;
        QtGameMap* game_map;
        GameLevel* game_level;
        Mario* mario;

        QTimer* timer;
        QSet<int> pressed_keys;
        int current_level_num = 1;

    public:
        explicit GameWidget(QWidget* parent = nullptr);
        ~GameWidget();

    protected:
        void paintEvent(QPaintEvent* event) override;
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;

    private slots:
        void game_tick();

    private:
        void handle_input();
        void update_game_state();
        void check_level_state();
    };
}
