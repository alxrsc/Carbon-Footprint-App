//
// Created by Alexandru Roșca on 13.01.2025.
//

#include "MotorbikePage.h"

// Common Styles
const QString GLOBAL_BACKGROUND_STYLE = "background: linear-gradient(to bottom, #e0f7fa, #80deea); font-family: Arial, sans-serif;";
const QString HEADER_STYLE = "font-size: 24px; font-weight: bold; color: #004d40; text-align: center;";
const QString INSTRUCTION_STYLE = "font-size: 16px; color: #004d40; text-align: center; margin: 10px 0;";
const QString BUTTON_STYLE = "QPushButton {"
                             "font-size: 16px; font-weight: bold; color: white; background-color: #00796b; border-radius: 5px; padding: 10px;"
                             "} QPushButton:hover { background-color: #004d40; }";

MotorbikePage::MotorbikePage(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void MotorbikePage::setupUi() {
    mainLayout = new QVBoxLayout(this);

    // Header and Instructions
    QLabel *headerLabel = new QLabel("Motorbike Carbon Footprint Calculator", this);
    QLabel *instructionLabel = new QLabel("Add your motorbike details. Use the Add Motorbike button to add more.", this);
    headerLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setAlignment(Qt::AlignCenter);

    // Apply styling for the header and instructions
    headerLabel->setStyleSheet(HEADER_STYLE);
    instructionLabel->setStyleSheet(INSTRUCTION_STYLE);

    // Scroll area for motorbike entries
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget(this);
    motorbikeListLayout = new QVBoxLayout(scrollWidget);

    scrollWidget->setLayout(motorbikeListLayout);
    scrollArea->setWidget(scrollWidget);

    // Add the first motorbike entry by default
    addMotorbikeEntry();

    // Add Motorbike button
    addMotorbikeButton = new QPushButton("Add Motorbike", this);
    addMotorbikeButton->setStyleSheet(BUTTON_STYLE);
    connect(addMotorbikeButton, &QPushButton::clicked, this, &MotorbikePage::addMotorbikeEntry);

    // Navigation buttons
    backButton = new QPushButton("< Back", this);
    publicTransportButton = new QPushButton("Public Transport >", this);

    backButton->setStyleSheet(BUTTON_STYLE);
    publicTransportButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(publicTransportButton);
    navLayout->setAlignment(Qt::AlignCenter);

    // Add widgets to the main layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(addMotorbikeButton);
    mainLayout->addLayout(navLayout);

    // Apply a global background color
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();
}

void MotorbikePage::addMotorbikeEntry() {
    QWidget *entryWidget = new QWidget(this);
    QHBoxLayout *entryLayout = new QHBoxLayout(entryWidget);

    // Dropdown for motorbike size
    QComboBox *sizeComboBox = new QComboBox(entryWidget);
    sizeComboBox->addItems({"Motorbike-Size-Small", "Motorbike-Size-Medium", "Motorbike-Size-Large", "Motorbike-Size-Average"});

    // Dropdown for fuel type
    QComboBox *fuelComboBox = new QComboBox(entryWidget);
    fuelComboBox->addItems({"Petrol", "Diesel"});

    // Input for kilometers
    QLineEdit *kilometersInput = new QLineEdit(entryWidget);
    kilometersInput->setPlaceholderText("Enter distance in kilometers (e.g. 100)");

    // Remove button
    QPushButton *removeButton = new QPushButton("Remove", entryWidget);
    removeButton->setStyleSheet(BUTTON_STYLE);

    connect(removeButton, &QPushButton::clicked, [=]() {
        removeMotorbikeEntry(entryWidget);
    });

    entryLayout->addWidget(new QLabel("Size:"));
    entryLayout->addWidget(sizeComboBox);
    entryLayout->addWidget(new QLabel("Fuel:"));
    entryLayout->addWidget(fuelComboBox);
    entryLayout->addWidget(new QLabel("Distance:"));
    entryLayout->addWidget(kilometersInput);
    entryLayout->addWidget(removeButton);

    motorbikeListLayout->addWidget(entryWidget);
    motorbikeEntries.append(entryWidget);
}

void MotorbikePage::removeMotorbikeEntry(QWidget *entry) {
    motorbikeListLayout->removeWidget(entry);
    motorbikeEntries.removeOne(entry);
    entry->deleteLater();
}
