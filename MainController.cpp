#include "MainController.h"

MainController::MainController() {
    // Connect main page button to show language selection page
    QObject::connect(mainPage.helloButton, &QPushButton::clicked, this, &MainController::showLanguagePage);

    // Connect language selection buttons
    QObject::connect(languagePage.englishButton, &QPushButton::clicked, this, &MainController::setLanguageEnglish);
    QObject::connect(languagePage.romanianButton, &QPushButton::clicked, this, &MainController::setLanguageRomanian);
    QObject::connect(languagePage.spanishButton, &QPushButton::clicked, this, &MainController::setLanguageSpanish);

    // Connect back button on methodPage to go back to language selection
    QObject::connect(methodPage.getBackButton(), &QPushButton::clicked, this, &MainController::backToSelectLanguagePage);

    // Connect the householdButton on methodPage to show HouseholdFootprintPage
    QObject::connect(methodPage.getHouseholdButton(), &QPushButton::clicked, this, &MainController::showHouseholdFootprintPage);

    // Connect the submitPeopleCount signal from methodPage to showMethodPage slot
    QObject::connect(&methodPage, &FootprintMethodPage::peopleCountEntered, this, &MainController::showHouseholdFootprintPage);
}

void MainController::showMainPage() {
    languagePage.hide();
    methodPage.hide();
    householdFootprintPage.hide(); // Hide household page when going back to main
    mainPage.show();
}

void MainController::showLanguagePage() {
    mainPage.hide();
    methodPage.hide();
    householdFootprintPage.hide(); // Hide household page if returning to language page
    languagePage.show();
}

void MainController::backToSelectLanguagePage() {
    methodPage.hide();
    mainPage.show();
}

void MainController::showMethodPage() {
    languagePage.hide();
    methodPage.show();
}

void MainController::showHouseholdFootprintPage() {
    // Hide the method page and show the household footprint page
    methodPage.hide();
    householdFootprintPage.show();
}

// Slot functions to set language
void MainController::setLanguageEnglish() {
    selectedLanguage = "English";
    methodPage.updateLanguage(selectedLanguage);
    showMethodPage();
}

void MainController::setLanguageRomanian() {
    selectedLanguage = "Romanian";
    methodPage.updateLanguage(selectedLanguage);
    showMethodPage();
}

void MainController::setLanguageSpanish() {
    selectedLanguage = "Spanish";
    methodPage.updateLanguage(selectedLanguage);
    showMethodPage();
}
