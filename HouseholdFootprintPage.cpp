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
#include <QHBoxLayout>

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
    formLayout->addRow("Electricity (kWh):", new QLineEdit(this));
    formLayout->addRow("Natural Gas (kWh):", new QLineEdit(this));
    formLayout->addRow("Heating Oil (litres):", new QLineEdit(this));
    formLayout->addRow("Coal (metric tons):", new QLineEdit(this));
    formLayout->addRow("LPG (litres):", new QLineEdit(this));
    formLayout->addRow("Propane (litres):", new QLineEdit(this));
    formLayout->addRow("Wooden Pellets (metric tons):", new QLineEdit(this));

    // Number of people in the household
    peopleLabel = new QLabel("How many people are in your household?", this);
    peopleComboBox = new QComboBox(this);
    peopleComboBox->addItems({"1", "2", "3", "4", "5", "6+"});

    // Calculate Button
    calculateButton = new QPushButton("Calculate Household Footprint", this);

    // Offset and Results Section
    resultsLabel = new QLabel("Total Household Footprint = 0.01 metric tons of CO2e", this);
    resultsLabel->setAlignment(Qt::AlignCenter);
    offsetButton = new QPushButton("Offset Now", this);

    // Navigation Buttons
    backButton = new QPushButton("< Welcome", this);
    nextButton = new QPushButton("Flights >", this);

    // Arrange layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(peopleLabel);
    mainLayout->addWidget(peopleComboBox);
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(resultsLabel);
    mainLayout->addWidget(offsetButton);

    // Bottom navigation layout
    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(nextButton);
    mainLayout->addLayout(navLayout);

    setLayout(mainLayout);
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
    calculateButton->setStyleSheet("color: lightgreen; background-color: gray; padding: 10px; border-radius: 5px;");
    offsetButton->setStyleSheet("color: lightgreen; background-color: gray; padding: 10px; border-radius: 5px;");
    backButton->setStyleSheet("color: green; background-color: lightgray; padding: 10px; border-radius: 5px;");
    nextButton->setStyleSheet("color: green; background-color: lightgray; padding: 10px; border-radius: 5px;");

    // Results label style
    resultsLabel->setStyleSheet("font-weight: bold; color: green; font-size: 18px;");
}
