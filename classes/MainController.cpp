#include "MainController.h"

MainController::MainController() {
    // Connect main page button to show language selection page
    QObject::connect(mainPage.helloButton, &QPushButton::clicked, this, &MainController::showMethodPage);

    // Connect back button on methodPage to go back to language selection
    QObject::connect(methodPage.getBackButton(), &QPushButton::clicked, this, &MainController::backToMainPage);

    // Connect the householdButton on methodPage to show HouseholdFootprintPage
    QObject::connect(methodPage.getHouseholdButton(), &QPushButton::clicked, this, &MainController::showHouseholdFootprintPage);

    // Connect the submitPeopleCount signal from methodPage to showMethodPage slot
    QObject::connect(&methodPage, &FootprintMethodPage::peopleCountEntered, this, &MainController::showHouseholdFootprintPage);
}

void MainController::showMainPage() {
    methodPage.hide();
    householdFootprintPage.hide(); // Hide household page when going back to main
    mainPage.show();
}

void MainController::showMethodPage() {
    // Hide the main page and show the method page
    mainPage.hide();
    householdFootprintPage.hide();
    methodPage.show();
}

void MainController::showHouseholdFootprintPage() {
    // Hide the method page and show the household footprint page
    methodPage.hide();
    householdFootprintPage.show();
}

void MainController::backToMainPage() {
    // Hide the method page and show the main page
    methodPage.hide();
    householdFootprintPage.hide();
    mainPage.show();
}