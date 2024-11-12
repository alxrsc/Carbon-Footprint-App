#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "MainPage.h"
#include "SelectLanguagePage.h"
#include "FootprintMethodPage.h"

class MainController : public QObject {
Q_OBJECT

public:
    MainPage mainPage;
    SelectLanguagePage languagePage;
    FootprintMethodPage methodPage;  // New page for selecting footprint calculation method
    QString selectedLanguage;        // To store the selected language

    MainController();
    virtual ~MainController() = default;

    void showMainPage();
    void showLanguagePage();
    void backToSelectLanguagePage();
    void showMethodPage();

private slots:
    void setLanguageEnglish();
    void setLanguageRomanian();
    void setLanguageSpanish();
};

#endif // MAINCONTROLLER_H
