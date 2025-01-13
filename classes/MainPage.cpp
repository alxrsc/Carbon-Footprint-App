//
// Created by Alexandru Roșca on 12.11.2024.
//


#include "MainPage.h"

MainPage::MainPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void MainPage::setupUI() {
    // Create the button
    helloButton = new QPushButton("Hello", this);
    helloButton->setStyleSheet(BUTTON_STYLE);
    helloButton->setFixedSize(300, 100);

    // Layouts
    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout = new QHBoxLayout();

    hLayout->addStretch();
    hLayout->addWidget(helloButton);
    hLayout->addStretch();

    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();

    setLayout(vLayout);
    setWindowTitle("Main Page");
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    showMaximized();
}
