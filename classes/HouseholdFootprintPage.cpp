//
// Created by Alexandru Roșca on 12.11.2024.
//

#include "HouseholdFootprintPage.h"
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>

HouseholdFootprintPage::HouseholdFootprintPage(QWidget *parent) : QWidget(parent) {
    setupUi();
    applyStyles();
}

void HouseholdFootprintPage::setupUi() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Header and Instructions
    headerLabel = new QLabel("Household Carbon Footprint Calculator", this);
    instructionLabel = new QLabel("Enter your consumption of each type of energy, and press Calculate", this);
    headerLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setAlignment(Qt::AlignCenter);

    // Form layout for energy consumption inputs
    formLayout = new QFormLayout;
    formLayout->addRow("Please state your contry:", new QLineEdit(this));
    formLayout->addRow("Electricity (kWh):", new QLineEdit(this));
    formLayout->addRow("Petrol (litres):", new QLineEdit(this));
    formLayout->addRow("Coal (metric tons):", new QLineEdit(this));
    formLayout->addRow("Diesel (litres):", new QLineEdit(this));
    formLayout->addRow("LPG (litres):", new QLineEdit(this));
    formLayout->addRow("Natural Gas (metric tons):", new QLineEdit(this));

    // Navigation Buttons
    backButton = new QPushButton("< Welcome", this);
    nextButton = new QPushButton("Flights >", this);

    // Arrange layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addLayout(formLayout);

    // Bottom navigation layout
    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(nextButton);
    navLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(navLayout);

    showMaximized();
    setLayout(mainLayout);

    // connect the buttons to their respective slots
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
    nextButton->setStyleSheet("color: green; background-color: lightgray; padding: 10px; border-radius: 5px;");

}
