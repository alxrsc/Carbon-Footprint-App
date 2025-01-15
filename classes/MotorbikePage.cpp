// MotorbikePage.cpp
#include "MotorbikePage.h"
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>

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

    // Calculate button
    calculateButton = new QPushButton("Calculate Carbon Footprint", this);
    calculateButton->setStyleSheet(BUTTON_STYLE);
    connect(calculateButton, &QPushButton::clicked, this, &MotorbikePage::calculateCarbonFootprint);

    // Result display
    resultLabel = new QLabel("", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("font-size: 16px; color: green;");

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
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(resultLabel);
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
    sizeComboBox->setObjectName("SizeComboBox");

    // Dropdown for fuel type
    QComboBox *fuelComboBox = new QComboBox(entryWidget);
    fuelComboBox->addItems({"Petrol", "Diesel"});
    fuelComboBox->setObjectName("FuelComboBox");

    // Input for kilometers
    QLineEdit *kilometersInput = new QLineEdit(entryWidget);
    kilometersInput->setPlaceholderText("Enter distance in kilometers (e.g. 100)");
    kilometersInput->setObjectName("DistanceInput");

    // Remove button
    QPushButton *removeButton = new QPushButton("Remove", entryWidget);
    removeButton->setStyleSheet(BUTTON_STYLE);

    connect(removeButton, &QPushButton::clicked, [this, entryWidget]() {
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

void MotorbikePage::calculateCarbonFootprint() {
    double totalCarbonFootprint = 0.0;

    for (QWidget *entry : motorbikeEntries) {
        QComboBox *sizeComboBox = entry->findChild<QComboBox *>("SizeComboBox");
        QComboBox *fuelComboBox = entry->findChild<QComboBox *>("FuelComboBox");
        QLineEdit *kilometersInput = entry->findChild<QLineEdit *>("DistanceInput");

        if (!sizeComboBox || !fuelComboBox || !kilometersInput) {
            qDebug() << "One or more inputs are missing.";
            continue;
        }

        QString command = "python3";
        QStringList arguments;
        arguments << "../backend-api-scripts/emissions_by_motorcycle.py"
                  << sizeComboBox->currentText()
                  << fuelComboBox->currentText()
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

    ExpensesPage::motorcycleCost = totalCarbonFootprint;

    resultLabel->setText(QString("Total Carbon Footprint: %1 kg CO₂").arg(totalCarbonFootprint));
}