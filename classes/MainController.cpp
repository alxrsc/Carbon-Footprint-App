#include "MainController.h"

MainController::MainController() {
    // Connect the helloButton on mainPage to showMethodPage slot
    QObject::connect(mainPage.helloButton, &QPushButton::clicked, this, &MainController::showMethodPage);

    // Connect the backButton on methodPage to go back to main page
    QObject::connect(methodPage.getBackButton(), &QPushButton::clicked, this, &MainController::backToMainPage);

    // Connect the householdButton on methodPage to showHouseholdFootprintPage slot
    QObject::connect(methodPage.getHouseholdButton(), &QPushButton::clicked, this, &MainController::showHouseholdFootprintPage);

    // Connect the peopleCountEntered signal from FootprintMethodPage to showHouseholdFootprintPage slot
    QObject::connect(&methodPage, &FootprintMethodPage::peopleCountEntered, this, &MainController::showHouseholdFootprintPage);

    // Connect the backButton on householdFootprintPage to go back to methodPage
    QObject::connect(householdFootprintPage.getBackButton(), &QPushButton::clicked, this, &MainController::showMethodPage);

    // Connect the nextButton on householdFootprintPage to show FlightsPage
    QObject::connect(householdFootprintPage.getFlightsButton(), &QPushButton::clicked, this, &MainController::showFlightsPage);

    // Connect the backButton on flightsPage to go back to householdFootprintPage
    QObject::connect(flightsPage.getBackButton(), &QPushButton::clicked, this, &MainController::showHouseholdFootprintPage);

    // Connect the nextButton on flightsPage to show VehiclePage
    QObject::connect(flightsPage.getVehicleButton(), &QPushButton::clicked, this, &MainController::showVehiclePage);

    // Connect the backButton on vehiclePage to go back to flightsPage
    QObject::connect(vehiclePage.getBackButton(), &QPushButton::clicked, this, &MainController::showFlightsPage);
}

void MainController::showMainPage() {
    mainPage.show();
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.hide();
    vehiclePage.hide();
}

void MainController::showMethodPage() {
    // Hide the main page and show the method page
    mainPage.hide();
    methodPage.show();
    householdFootprintPage.hide();
    flightsPage.hide();
    vehiclePage.hide();
}

void MainController::showHouseholdFootprintPage() {
    // Hide the method page and show the household footprint page
    mainPage.hide();
    methodPage.hide();
    householdFootprintPage.show();
    flightsPage.hide();
    vehiclePage.hide();
}

void MainController::showFlightsPage() {
    // Hide the method page and show the flights page
    mainPage.hide();
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.show();
    vehiclePage.hide();
}

void MainController::showVehiclePage() {
    vehiclePage.show();
    mainPage.hide();
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.hide();

}

void MainController::backToMainPage() {
    // Hide the method page and show the main page
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.hide();
    vehiclePage.hide();
    mainPage.show();
}