#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "MainPage.h"
#include "FootprintMethodPage.h"
#include "HouseholdFootprintPage.h" // Include the new HouseholdFootprintPage header
#include "FlightsPage.h" // Include the new FlightsPage header
#include "VehiclePage.h"
#include "MotorbikePage.h"

class MainController : public QObject {
Q_OBJECT

public:
    MainPage mainPage;                          // Main page of the application
    FootprintMethodPage methodPage;          // Page for selecting footprint calculation method
    HouseholdFootprintPage householdFootprintPage; // Page for household footprint calculation
    FlightsPage flightsPage; // Page for flights footprint calculation
    VehiclePage vehiclePage;                  // Page for vehicles footprint calculation
    MotorbikePage motorbikePage;              // Page for motorbikes footprint calculation

    MainController();
    virtual ~MainController() = default;

    void showMainPage();
    void showMethodPage();
    void showHouseholdFootprintPage(); // New method to show HouseholdFootprintPage
    void showFlightsPage(); // New method to show FlightsPage
    void showVehiclePage();
    void showMotorbikePage();
    void backToMainPage();

};

#endif // MAINCONTROLLER_H
