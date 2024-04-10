#include "App.h"

int32_t main(int32_t argc, char *argv[]) {
    QApplication a(argc, argv);
    App window(1000, 700);
    window.render();
    return QApplication::exec();
}