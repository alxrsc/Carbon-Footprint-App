//
// Created by Alexandru Roșca on 12.11.2024.
//

#include "MainPage.h"

MainPage::MainPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    helloButton = new QPushButton("Hello", this);
    helloButton->setStyleSheet("background-color: lightblue;");
    layout->addWidget(helloButton);
    setLayout(layout);
    setWindowTitle("Main Page");
    showMaximized();
    setStyleSheet("background-color: lightgreen;");
}