#include <QApplication>
#include "classes/MainController.h"
#include "APICalls.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainController controller;
    controller.showMainPage();


    return app.exec();
}