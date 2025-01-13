//
// Created by Alexandru Roșca on 12.11.2024.
//

#include "HouseholdFootprintPage.h"

HouseholdFootprintPage::HouseholdFootprintPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void HouseholdFootprintPage::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *headerLabel = new QLabel("Household Carbon Footprint Calculator", this);
    headerLabel->setStyleSheet(HEADER_STYLE);

    QFormLayout *formLayout = new QFormLayout();
    for (const QString &field : {"Electricity (kWh):", "Petrol (litres):", "Natural Gas (metric tons):"}) {
        QLineEdit *input = new QLineEdit(this);
        input->setStyleSheet(INPUT_STYLE);
        formLayout->addRow(field, input);
    }

    backButton = new QPushButton("< Method", this);
    flightsButton = new QPushButton("Flights >", this);

    backButton->setStyleSheet(BUTTON_STYLE);
    flightsButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(flightsButton);
    navLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(headerLabel);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(navLayout);

    setLayout(mainLayout);
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    showMaximized();
}


void HouseholdFootprintPage::applyStyles() {
    // Overall page style
    setStyleSheet("background-color: lightblue; font-size: 16px;");

    // Header styles
    headerLabel->setStyleSheet("font-weight: bold; color: darkgreen; font-size: 24px;");

    // Instruction styles
    instructionLabel->setStyleSheet("color: gray; font-size: 14px;");

    // Form field styles
    QList<QLineEdit *> lineEdits = findChildren<QLineEdit *>();
    for (QLineEdit *lineEdit : lineEdits) {
        lineEdit->setStyleSheet("padding: 5px; border: 1px solid gray; border-radius: 4px;");
    }

    // Button styles
    backButton->setStyleSheet("color: green; background-color: lightgray; padding: 10px; border-radius: 5px;");
    flightsButton->setStyleSheet("color: green; background-color: lightgray; padding: 10px; border-radius: 5px;");

}
