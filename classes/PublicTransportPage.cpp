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

    // Calculate button
    calculateButton = new QPushButton("Calculate Carbon Footprint", this);
    calculateButton->setStyleSheet(BUTTON_STYLE);
    connect(calculateButton, &QPushButton::clicked, this, &PublicTransportPage::calculateCarbonFootprint);

    // Result display
    resultLabel = new QLabel("", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("font-size: 16px; color: green;");

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
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(resultLabel);
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
    transportTypeComboBox->setObjectName("TransportTypeComboBox");

    // Input for kilometers
    QLineEdit *kilometersInput = new QLineEdit(entryWidget);
    kilometersInput->setPlaceholderText("Enter distance in kilometers (e.g., 100)");
    kilometersInput->setObjectName("DistanceInput");

    // Remove button
    QPushButton *removeButton = new QPushButton("Remove", entryWidget);
    removeButton->setStyleSheet(BUTTON_STYLE);

    connect(removeButton, &QPushButton::clicked, [this, entryWidget]() {
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

void PublicTransportPage::calculateCarbonFootprint() {
    double totalCarbonFootprint = 0.0;

    for (QWidget *entry : transportEntries) {
        QComboBox *transportTypeComboBox = entry->findChild<QComboBox *>("TransportTypeComboBox");
        QLineEdit *kilometersInput = entry->findChild<QLineEdit *>("DistanceInput");

        if (!transportTypeComboBox || !kilometersInput) {
            qDebug() << "One or more inputs are missing.";
            continue;
        }

        QString command = "python3";
        QStringList arguments;
        arguments << "../backend-api-scripts/emissions_by_publicTransport.py"
                  << transportTypeComboBox->currentText()
                  << kilometersInput->text()
                  << "km";

        qDebug() << "Command:" << command << arguments;

        QProcess process;
        process.start(command, arguments);
        process.waitForFinished();

        QByteArray output = process.readAllStandardOutput();
        QByteArray error = process.readAllStandardError();

        if (!error.isEmpty()) {
            qDebug() << "Error:" << error;
            continue;
        }

        if (output.isEmpty()) {
            qDebug() << "No output received from the script.";
            continue;
        }

        qDebug() << "Output from script:" << output;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(output);
        if (jsonResponse.isObject()) {
            QJsonObject responseObject = jsonResponse.object();
            if (responseObject.contains("co2e_kg")) {
                totalCarbonFootprint += responseObject["co2e_kg"].toDouble();
            } else {
                qDebug() << "Key 'co2e_kg' not found in JSON response.";
            }
        } else {
            qDebug() << "Invalid JSON response:" << output;
        }
    }

    ExpensesPage::publicTransportCost = totalCarbonFootprint;

    resultLabel->setText(QString("Total Carbon Footprint: %1 kg CO₂").arg(totalCarbonFootprint));
}
