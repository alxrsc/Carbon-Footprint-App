//
// Created by Alexandru Roșca on 12.11.2024.
//

#include "MainController.h"

MainController::MainController() {
    QObject::connect(mainPage.helloButton, &QPushButton::clicked, this, &MainController::showLanguagePage);
    QObject::connect(languagePage.englishButton, &QPushButton::clicked, this, &MainController::backToMainPage);
    QObject::connect(languagePage.romanianButton, &QPushButton::clicked, this, &MainController::backToMainPage);
    QObject::connect(languagePage.spanishButton, &QPushButton::clicked, this, &MainController::backToMainPage);
}

void MainController::showMainPage() {
    languagePage.hide();
    mainPage.show();
}

void MainController::showLanguagePage() {
    mainPage.hide();
    languagePage.show();
}

void MainController::backToMainPage() {
    languagePage.hide();
    mainPage.show();
}
