#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "MainPage.h"
#include "SelectLanguagePage.h"
#include "FootprintMethodPage.h"
#include "HouseholdFootprintPage.h" // Include the new HouseholdFootprintPage header

class MainController : public QObject {
Q_OBJECT

public:
    MainPage mainPage;
    SelectLanguagePage languagePage;
    FootprintMethodPage methodPage;          // Page for selecting footprint calculation method
    HouseholdFootprintPage householdFootprintPage; // Page for household footprint calculation
    QString selectedLanguage;                // To store the selected language

    MainController();
    virtual ~MainController() = default;

    void showMainPage();
    void showLanguagePage();
    void showMethodPage();
    void showHouseholdFootprintPage(); // New method to show HouseholdFootprintPage
    void backToSelectLanguagePage();

private slots:
    void setLanguageEnglish();
    void setLanguageRomanian();
    void setLanguageSpanish();
};

#endif // MAINCONTROLLER_H
