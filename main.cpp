#include <QApplication>
#include "classes/MainController.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainController controller;
    controller.showMainPage();

    return app.exec();
}