//
// Created by Alexandru Roșca on 12.11.2024.
//

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "MainPage.h"
#include "SelectLanguagePage.h"

class MainController : public QObject {
Q_OBJECT

public:
    MainPage mainPage;
    SelectLanguagePage languagePage;

    MainController();
    virtual ~MainController() = default;  // Virtual destructor

    void showMainPage();
    void showLanguagePage();
    void backToMainPage();
};

#endif // MAINCONTROLLER_H
