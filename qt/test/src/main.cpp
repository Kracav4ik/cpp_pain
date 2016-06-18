#include <QApplication>

#include "main_window.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow* window = new MainWindow();
    return app.exec();
}
