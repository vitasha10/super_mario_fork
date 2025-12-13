#pragma once

#include <QWidget>

namespace biv {
        class QtGameMap;

        class QtGameWidget : public QWidget {
        public:
                explicit QtGameWidget(QtGameMap* map, QWidget* parent = nullptr);

        protected:
                void paintEvent(QPaintEvent*) override;
                void keyPressEvent(QKeyEvent*) override;
                void keyReleaseEvent(QKeyEvent*) override;

        private:
                QtGameMap* map = nullptr;
        };
}
