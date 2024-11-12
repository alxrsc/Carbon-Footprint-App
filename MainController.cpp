#include "MainController.h"

MainController::MainController() {
    QObject::connect(mainPage.helloButton, &QPushButton::clicked, this, &MainController::showLanguagePage);
    QObject::connect(languagePage.englishButton, &QPushButton::clicked, this, &MainController::setLanguageEnglish);
    QObject::connect(languagePage.romanianButton, &QPushButton::clicked, this, &MainController::setLanguageRomanian);
    QObject::connect(languagePage.spanishButton, &QPushButton::clicked, this, &MainController::setLanguageSpanish);

    QObject::connect(methodPage.backButton, &QPushButton::clicked, this, &MainController::backToSelectLanguagePage);
}

void MainController::showMainPage() {
    languagePage.hide();
    methodPage.hide();
    mainPage.show();
}

void MainController::showLanguagePage() {
    mainPage.hide();
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
