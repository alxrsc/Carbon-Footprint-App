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

    infoLabel = new QLabel(this);
    infoLabel->setText(
    "\"Gender, Digitalization, Green: Ensuring a Sustainable Future for all in Europe\"\n"
    "Ref. Project: 2023-1-RO01-KA220-HED-000154433, leader: University of Agricultural Sciences and Veterinary Medicine\n"
    "in which UNSTPB is a partner, alongside: Universitat Autònoma de Barcelona, Spain,\n"
    "University of Porto, Portugal, and Uzhhorod National University, Ukraine"

    );
    infoLabel->setWordWrap(true);  // Enable word wrapping
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet("font-size: 16px; padding: 10px;");

    creditsLabel = new QLabel(this);
    creditsLabel->setText("Team members:\n\n"
                          "- leader - Alexandru Roșca (alexandrurosca968@gmail.com)\n"
                          "- Maria-Beatrice Surugiu (surugium514@gmail.com)\n"
                          "- Petrișor-Andrei Leu (leupetrisorandrei.bd@gmail.com)\n"
                          "- Andu Bădescu (badescuandu2@gmail.com)\n\n"
                          "Coordinating teachers:\n\n"
                          "- Mihai Caramihai\n"
                          "- Daniel Chiș");
    creditsLabel->setWordWrap(true);
    creditsLabel->setAlignment(Qt::AlignCenter);
    creditsLabel->setStyleSheet("font-size: 16px; padding: 10px;");

    // Layouts
    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout = new QHBoxLayout();

    hLayout->addStretch();
    hLayout->addWidget(helloButton);
    hLayout->addStretch();

    vLayout->addStretch();
    vLayout->addWidget(infoLabel);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(creditsLabel);
    vLayout->addStretch();

    setLayout(vLayout);
    setWindowTitle("Main Page");
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    showMaximized();
}
