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

//    cout << get_emissions_by_vehicle_model("Toyoya", "Prius", "24000", "km") << endl;

//    return 0;
}