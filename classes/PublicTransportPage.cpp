// Created by Alexandru Roșca on 13.01.2025.

#include "PublicTransportPage.h"
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

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

    headerLabel->setStyleSheet(HEADER_STYLE);
    instructionLabel->setStyleSheet(INSTRUCTION_STYLE);

    // Scroll area for transport entries
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget(this);
    transportListLayout = new QVBoxLayout(scrollWidget);
    scrollWidget->setLayout(transportListLayout);
    scrollArea->setWidget(scrollWidget);

    addTransportEntry();

    // Add Transport button
    addTransportButton = new QPushButton("Add Transport", this);
    addTransportButton->setStyleSheet(BUTTON_STYLE);
    connect(addTransportButton, &QPushButton::clicked, this, &PublicTransportPage::addTransportEntry);

    // Calculate button
    calculateButton = new QPushButton("Calculate Carbon Footprint", this);
    calculateButton->setStyleSheet(BUTTON_STYLE);
    connect(calculateButton, &QPushButton::clicked, this, &PublicTransportPage::calculateCarbonFootprint);

    // Result display
    resultLabel = new QLabel("", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("font-size: 16px; color: green;");

    // Navigation buttons
    backButton = new QPushButton("< Motorbikes", this);
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
    mainLayout->addWidget(calculateButton);
    mainLayout->addLayout(navLayout);

    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();
}

void PublicTransportPage::addTransportEntry() {
    PublicTransportEntryWidget *entryWidget = new PublicTransportEntryWidget(this);
    QHBoxLayout *entryLayout = new QHBoxLayout(entryWidget);

    transportListLayout->addWidget(entryWidget);
    transportEntries.append(entryWidget);
}

void PublicTransportPage::removeTransportEntry(PublicTransportEntryWidget *entry) {
    transportListLayout->removeWidget(entry);
    transportEntries.removeOne(entry);
    entry->deleteLater();
}

void PublicTransportPage::calculateCarbonFootprint() {
    QStringList results;
    double totalCarbonFootprint = 0.0;

    for (PublicTransportEntryWidget *entry : transportEntries) {
        QString transportType = entry->getTransportType();
        QString distance = entry->getDistance();

        if (transportType.isEmpty() || distance.isEmpty()) {
            QMessageBox::warning(this, "Missing data", "Complete every field for each public transport.");
            continue;
        }

        string emissions = get_emissions_by_publicTransport(transportType.toStdString(), "Diesel", distance.toStdString(), "km");

        if (emissions == "Error" || emissions.empty()) {
            QMessageBox::warning(this, "Error", "We could not calculate the emissions for the transport: " + transportType + ".");
            continue;
        }

        try {
            double emissionValue = std::stod(emissions);
            totalCarbonFootprint += emissionValue;

            QString message = QString("Emissions for the %1 are: %2 kg CO2")
                    .arg(transportType, QString::number(emissionValue));
            results.append(message);
        } catch (const std::invalid_argument &e) {
            QMessageBox::warning(this, "Error", "Invalid format for the calculated emissions: "
                                                 + QString::fromStdString(emissions));
        }
    }

    ExpensesPage::publicTransportCost = totalCarbonFootprint;

    if (!results.isEmpty()) {
        QMessageBox::information(this, "Calculated emissions", results.join("\n"));
    }
}
