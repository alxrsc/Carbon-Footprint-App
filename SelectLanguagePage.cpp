//
// Created by Alexandru Roșca on 12.11.2024.
//

#include "SelectLanguagePage.h"

SelectLanguagePage::SelectLanguagePage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    englishButton = new QPushButton("English", this);
    romanianButton = new QPushButton("Romanian", this);
    spanishButton = new QPushButton("Spanish", this);
    layout->addWidget(englishButton);
    layout->addWidget(romanianButton);
    layout->addWidget(spanishButton);
    englishButton->setStyleSheet("background-color: lightblue;");
    romanianButton->setStyleSheet("background-color: lightblue;");
    spanishButton->setStyleSheet("background-color: lightblue;");
    setLayout(layout);
    setWindowTitle("Select Language");
    showMaximized();
    setStyleSheet("background-color: lightgreen;");
}