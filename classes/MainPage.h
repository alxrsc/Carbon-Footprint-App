//
// Created by Alexandru Roșca on 12.11.2024.
//

#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "CommonStyles.h"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class MainPage : public QWidget {
Q_OBJECT

    void setupUI();

public:
    QPushButton *helloButton;
    QLabel *projectInfoLabel;
    QLabel *projectCredits;


    MainPage(QWidget *parent = nullptr);
    virtual ~MainPage() = default;  // Virtual destructor
};

#endif // MAINPAGE_H
