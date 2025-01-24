#include <QApplication>

#include "kotiki-engine/graphics/palette.hpp"
#include "kotiki-engine/graphics/main_window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    graphics::theme::SetPalette(app);

    graphics::MainWindow main_window;

    return app.exec();
}
