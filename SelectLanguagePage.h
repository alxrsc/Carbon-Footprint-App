//
// Created by Alexandru Roșca on 12.11.2024.
//

#ifndef SELECTLANGUAGEPAGE_H
#define SELECTLANGUAGEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class SelectLanguagePage : public QWidget {
Q_OBJECT

public:
    QPushButton *englishButton;
    QPushButton *romanianButton;
    QPushButton *spanishButton;

    SelectLanguagePage(QWidget *parent = nullptr);
    virtual ~SelectLanguagePage() = default;  // Virtual destructor
};

#endif // SELECTLANGUAGEPAGE_H

