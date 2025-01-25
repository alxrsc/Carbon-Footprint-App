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

    projectInfoLabel = new QLabel(this);
    projectInfoLabel->setText(
            "Gender, Digitalization, Green: Ensuring a Sustainable Future for all in Europe\"<br> Ref. Project: 2023-1-RO01- KA220-HED-000154433,<br> Partnership: Universitatea de Stiinte Agricole si Medicina Veterinara, Bucuresti, Romania, Universitatea Nationala de Stiinta si Tehnologie POLITEHNICA București, Romania,<br> Universitat Autonoma de Barcelona, Espana, Universidade do Porto, República Portuguesa, Uzhgorodskyi Nacionalnyi Universitet, Ukraina."
    );
    projectInfoLabel->setWordWrap(true);
    projectInfoLabel->setStyleSheet("font-size: 16px; padding: 10px;");
    projectInfoLabel->setAlignment(Qt::AlignCenter);

    projectCredits = new QLabel(this);
    projectCredits->setText(
            "<b>The team:</b><br>"
            "- <b>team leader</b> - Roșca Alexandru (alexandrurosca968@gmail.com)<br>"
            "- Bădescu Andu (badescuandu2@gmail.com)<br>"
            "- Leu Petrișor-Andrei (leupetrisorandrei.bd@gmail.com)<br>"
            "- Surugiu Maria-Beatrice (surugium514@gmail.com)<br>"
            "<br><br>"
            "<b>Project coordinators:</b><br>"
            "- Mihai Caramihai<br>"
            "- Daniel Chiș<br>"

            );
    projectCredits->setWordWrap(true);
    projectCredits->setStyleSheet("font-size: 16px; padding: 10px;");
    projectCredits->setAlignment(Qt::AlignCenter);

    // Layouts
    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout = new QHBoxLayout();

    hLayout->addStretch();
    hLayout->addWidget(helloButton);
    hLayout->addStretch();

    vLayout->addWidget(projectInfoLabel); // Add the label to the vertical layout
    vLayout->addLayout(hLayout);
    vLayout->addWidget(projectCredits); // Add the label to the vertical layout
    vLayout->addStretch();

    setLayout(vLayout);
    setWindowTitle("Main Page");
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    showMaximized();
}
