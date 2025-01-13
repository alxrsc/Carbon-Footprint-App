//
// Created by Alexandru Roșca on 13.01.2025.
//

#include "PublicTransportPage.h"

// Common Styles
const QString GLOBAL_BACKGROUND_STYLE = "background: linear-gradient(to bottom, #e0f7fa, #80deea); font-family: Arial, sans-serif;";
const QString HEADER_STYLE = "font-size: 24px; font-weight: bold; color: #004d40; text-align: center;";
const QString INSTRUCTION_STYLE = "font-size: 16px; color: #004d40; text-align: center; margin: 10px 0;";
const QString BUTTON_STYLE = "QPushButton {"
                             "font-size: 16px; font-weight: bold; color: white; background-color: #00796b; border-radius: 5px; padding: 10px;"
                             "} QPushButton:hover { background-color: #004d40; }";

PublicTransportPage::PublicTransportPage(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void PublicTransportPage::setupUi() {
    mainLayout = new QVBoxLayout(this);

    // Header and Instructions
    QLabel *headerLabel = new QLabel("Public Transport Carbon Footprint Calculator", this);
    QLabel *instructionLabel = new QLabel("Add your public transport details. Use the Add Transport button to add more.", this);
    headerLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setAlignment(Qt::AlignCenter);

    // Apply styling for the header and instructions
    headerLabel->setStyleSheet(HEADER_STYLE);
    instructionLabel->setStyleSheet(INSTRUCTION_STYLE);

    // Scroll area for transport entries
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget(this);
    transportListLayout = new QVBoxLayout(scrollWidget);

    scrollWidget->setLayout(transportListLayout);
    scrollArea->setWidget(scrollWidget);

    // Add the first transport entry by default
    addTransportEntry();

    // Add Transport button
    addTransportButton = new QPushButton("Add Transport", this);
    addTransportButton->setStyleSheet(BUTTON_STYLE);
    connect(addTransportButton, &QPushButton::clicked, this, &PublicTransportPage::addTransportEntry);

    // Navigation buttons
    backButton = new QPushButton("< Back", this);
    nextButton = new QPushButton("Public Transport >", this);

    backButton->setStyleSheet(BUTTON_STYLE);
    nextButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(nextButton);
    navLayout->setAlignment(Qt::AlignCenter);

    // Add widgets to the main layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(addTransportButton);
    mainLayout->addLayout(navLayout);

    // Apply a global background color
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();
}

void PublicTransportPage::addTransportEntry() {
    QWidget *entryWidget = new QWidget(this);
    QHBoxLayout *entryLayout = new QHBoxLayout(entryWidget);

    // Dropdown for transport type
    QComboBox *transportTypeComboBox = new QComboBox(entryWidget);
    transportTypeComboBox->addItems({
                                            "Bus-LocalAverage",
                                            "Bus-Coach",
                                            "Taxi-Local",
                                            "Train-National",
                                            "Train-Local",
                                            "Train-Tram"
                                    });

    // Input for kilometers
    QLineEdit *kilometersInput = new QLineEdit(entryWidget);
    kilometersInput->setPlaceholderText("Enter distance (e.g., 100 km)");

    // Remove button
    QPushButton *removeButton = new QPushButton("Remove", entryWidget);
    removeButton->setStyleSheet(BUTTON_STYLE);

    connect(removeButton, &QPushButton::clicked, [=]() {
        removeTransportEntry(entryWidget);
    });

    entryLayout->addWidget(new QLabel("Transport Type:"));
    entryLayout->addWidget(transportTypeComboBox);
    entryLayout->addWidget(new QLabel("Distance:"));
    entryLayout->addWidget(kilometersInput);
    entryLayout->addWidget(removeButton);

    transportListLayout->addWidget(entryWidget);
    transportEntries.append(entryWidget);
}

void PublicTransportPage::removeTransportEntry(QWidget *entry) {
    transportListLayout->removeWidget(entry);
    transportEntries.removeOne(entry);
    entry->deleteLater();
}

