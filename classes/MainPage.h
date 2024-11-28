//
// Created by Alexandru Roșca on 12.11.2024.
//

#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainPage : public QWidget {
Q_OBJECT

public:
    QPushButton *helloButton;

    MainPage(QWidget *parent = nullptr);
    virtual ~MainPage() = default;  // Virtual destructor
};

#endif // MAINPAGE_H