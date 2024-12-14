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

    // Connect the backButton on householdFootprintPage to go back to main page
    QObject::connect(householdFootprintPage.getBackButton(), &QPushButton::clicked, this, &MainController::showMethodPage);

    // Connect the nextButton on householdFootprintPage to show FlightsPage
    QObject::connect(householdFootprintPage.getNextButton(), &QPushButton::clicked, this, &MainController::showFlightsPage);

    // Connect the backButton on flightsPage to go back to householdFootprintPage
    QObject::connect(flightsPage.getBackButton(), &QPushButton::clicked, this, &MainController::showHouseholdFootprintPage);
}

void MainController::showMainPage() {
    methodPage.hide();
    householdFootprintPage.hide(); // Hide household page when going back to main
    flightsPage.hide(); // Hide flights page when going back to main
    mainPage.show();
}

void MainController::showMethodPage() {
    // Hide the main page and show the method page
    mainPage.hide();
    householdFootprintPage.hide();
    flightsPage.hide();
    methodPage.show();
}

void MainController::showHouseholdFootprintPage() {
    // Hide the method page and show the household footprint page
    mainPage.hide();
    methodPage.hide();
    flightsPage.hide();
    householdFootprintPage.show();
}

void MainController::showFlightsPage() {
    // Hide the method page and show the flights page
    mainPage.hide();
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.show();
}

void MainController::backToMainPage() {
    // Hide the method page and show the main page
    methodPage.hide();
    householdFootprintPage.hide();
    mainPage.show();
}