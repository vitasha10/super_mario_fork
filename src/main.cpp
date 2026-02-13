#include <QApplication>
#include "game_widget.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    biv::GameWidget widget;
    widget.show();

    return app.exec();
}
