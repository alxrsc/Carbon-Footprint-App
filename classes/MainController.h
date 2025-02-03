#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "MainPage.h"
#include "HouseholdFootprintPage.h" // Include the new HouseholdFootprintPage header
#include "FlightsPage.h" // Include the new FlightsPage header
#include "VehiclePage.h"
#include "MotorbikePage.h"
#include "PublicTransportPage.h"
#include "HotelStayPage.h"
#include "ExpensesPage.h"

class MainController : public QObject {
Q_OBJECT

public:
    MainPage mainPage;                          // Main page of the application
    HouseholdFootprintPage householdFootprintPage; // Page for household footprint calculation
    FlightsPage flightsPage; // Page for flights footprint calculation
    VehiclePage vehiclePage;                  // Page for vehicles footprint calculation
    MotorbikePage motorbikePage;              // Page for motorbikes footprint calculation
    PublicTransportPage publicTransportPage;  // Page for public transport footprint calculation
    HotelStayPage hotelStayPage;              // Page for hotel stay footprint calculation
    ExpensesPage expensesPage;                // Page for expenses footprint calculation

    MainController();
    virtual ~MainController() = default;

    void showMainPage();
    void showHouseholdFootprintPage(); // New method to show HouseholdFootprintPage
    void showFlightsPage(); // New method to show FlightsPage
    void showVehiclePage();
    void showMotorbikePage();
    void showPublicTransportPage();
    void showHotelStayPage();
    void showExpensesPage();

};

#endif // MAINCONTROLLER_H
