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

    // Connect the motorbikeButton on vehiclePage to show MotorbikePage
    QObject::connect(vehiclePage.getMotorbikeButton(), &QPushButton::clicked, this, &MainController::showMotorbikePage);

    // Connect the backButton on motorbikePage to go back to vehiclePage
    QObject::connect(motorbikePage.getBackButton(), &QPushButton::clicked, this, &MainController::showVehiclePage);

    // Connect the publicTransportButton on motorbikePage to show PublicTransportPage
    QObject::connect(motorbikePage.getPublicTransportButton(), &QPushButton::clicked, this, &MainController::showPublicTransportPage);

    // Connect the backButton on publicTransportPage to go back to motorbikePage
    QObject::connect(publicTransportPage.getBackButton(), &QPushButton::clicked, this, &MainController::showMotorbikePage);
}

void MainController::showMainPage() {
    mainPage.show();
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.hide();
    vehiclePage.hide();
    motorbikePage.hide();
    publicTransportPage.hide();
}

void MainController::showMethodPage() {
    // Hide the main page and show the method page
    mainPage.hide();
    methodPage.show();
    householdFootprintPage.hide();
    flightsPage.hide();
    vehiclePage.hide();
    motorbikePage.hide();
    publicTransportPage.hide();
}

void MainController::showHouseholdFootprintPage() {
    // Hide the method page and show the household footprint page
    mainPage.hide();
    methodPage.hide();
    householdFootprintPage.show();
    flightsPage.hide();
    vehiclePage.hide();
    motorbikePage.hide();
    publicTransportPage.hide();
}

void MainController::showFlightsPage() {
    // Hide the method page and show the flights page
    mainPage.hide();
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.show();
    vehiclePage.hide();
    motorbikePage.hide();
    publicTransportPage.hide();
}

void MainController::showVehiclePage() {
    vehiclePage.show();
    mainPage.hide();
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.hide();
    motorbikePage.hide();
    publicTransportPage.hide();
}

void MainController::showMotorbikePage() {
    mainPage.hide();
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.hide();
    vehiclePage.hide();
    motorbikePage.show();
    publicTransportPage.hide();
}

void MainController::showPublicTransportPage() {
    mainPage.hide();
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.hide();
    vehiclePage.hide();
    motorbikePage.hide();
    publicTransportPage.show();
}

void MainController::backToMainPage() {
    // Hide the method page and show the main page
    mainPage.show();
    methodPage.hide();
    householdFootprintPage.hide();
    flightsPage.hide();
    vehiclePage.hide();
    motorbikePage.hide();
    publicTransportPage.hide();
}