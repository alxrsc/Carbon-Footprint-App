//
// Created by Alexandru Roșca on 13.01.2025.
//

#include "PublicTransportPage.h"

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
    hotelStayButton = new QPushButton("Hotel Stays >", this);

    backButton->setStyleSheet(BUTTON_STYLE);
    hotelStayButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(hotelStayButton);
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
    kilometersInput->setPlaceholderText("Enter distance in kilometers (e.g., 100)");

    // Label to display emissions
    QLabel *emissionsLabel = new QLabel("Emissions: N/A", entryWidget);

    // Remove button
    QPushButton *removeButton = new QPushButton("Remove", entryWidget);
    removeButton->setStyleSheet(BUTTON_STYLE);

    // Connect to remove entry
    connect(removeButton, &QPushButton::clicked, [=]() {
        removeTransportEntry(entryWidget);
    });

    // Update emissions dynamically
    auto updateEmissions = [=]() {
        std::string transportType = transportTypeComboBox->currentText().toStdString();
        std::string distance = kilometersInput->text().toStdString();
        if (!distance.empty()) {
            string emissions = get_emissions_by_publicTransport(transportType, "Diesel", distance, "km");
            emissionsLabel->setText(QString::fromStdString("Emissions: " + emissions + " kg CO2"));
        } else {
            emissionsLabel->setText("Emissions: N/A");
        }
    };

    connect(transportTypeComboBox, &QComboBox::currentTextChanged, updateEmissions);
    connect(kilometersInput, &QLineEdit::textChanged, updateEmissions);

    entryLayout->addWidget(new QLabel("Transport Type:"));
    entryLayout->addWidget(transportTypeComboBox);
    entryLayout->addWidget(new QLabel("Distance:"));
    entryLayout->addWidget(kilometersInput);
    entryLayout->addWidget(emissionsLabel);
    entryLayout->addWidget(removeButton);

    transportListLayout->addWidget(entryWidget);
    transportEntries.append(entryWidget);
}


void PublicTransportPage::removeTransportEntry(QWidget *entry) {
    transportListLayout->removeWidget(entry);
    transportEntries.removeOne(entry);
    entry->deleteLater();
}

