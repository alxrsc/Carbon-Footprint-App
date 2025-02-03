// MotorbikePage.cpp
#include "MotorbikePage.h"
#include "../Utils/MotorbikeEntryWidget.h"

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
    mainLayout->addLayout(navLayout);

    // Apply a global background color
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();
}

void MotorbikePage::addMotorbikeEntry() {
    MotorbikeEntryWidget *motorbikeEntry = new MotorbikeEntryWidget(this);
    motorbikeListLayout->addWidget(motorbikeEntry);
    motorbikeEntries.append(motorbikeEntry);
    connect(motorbikeEntry, &MotorbikeEntryWidget::removeRequested, this, &MotorbikePage::removeMotorbikeEntry);


    // // Dropdown for motorbike size
    // QComboBox *sizeComboBox = new QComboBox(entryWidget);
    // sizeComboBox->addItems({"Motorbike-Size-Small", "Motorbike-Size-Medium", "Motorbike-Size-Large", "Motorbike-Size-Average"});
    // sizeComboBox->setObjectName("SizeComboBox");
    //
    // // Dropdown for fuel type
    // QComboBox *fuelComboBox = new QComboBox(entryWidget);
    // fuelComboBox->addItems({"Petrol", "Diesel"});
    // fuelComboBox->setObjectName("FuelComboBox");
    //
    // // Input for kilometers
    // QLineEdit *kilometersInput = new QLineEdit(entryWidget);
    // kilometersInput->setPlaceholderText("Enter distance in kilometers (e.g. 100)");
    // kilometersInput->setObjectName("DistanceInput");

    // // Remove button
    // QPushButton *removeButton = new QPushButton("Remove", entryWidget);
    // removeButton->setStyleSheet(BUTTON_STYLE);
    //
    // connect(removeButton, &QPushButton::clicked, [this, entryWidget]() {
    //     removeMotorbikeEntry(entryWidget);
    // });

    // entryLayout->addWidget(new QLabel("Size:"));
    // entryLayout->addWidget(sizeComboBox);
    // entryLayout->addWidget(new QLabel("Fuel:"));
    // entryLayout->addWidget(fuelComboBox);
    // entryLayout->addWidget(new QLabel("Distance:"));
    // entryLayout->addWidget(kilometersInput);
    // // entryLayout->addWidget(removeButton);


}

void MotorbikePage::removeMotorbikeEntry(QWidget *entry) {
    motorbikeListLayout->removeWidget(entry);
    motorbikeEntries.removeOne(entry);
    entry->deleteLater();
}


void MotorbikePage::calculateCarbonFootprint() {
    QStringList results;
    double total = 0.0;

    try {
        if (motorbikeEntries.isEmpty()) {
            throw std::invalid_argument("Adaugă cel puțin o motocicletă pentru a calcula amprenta de carbon!");
        }

        for (MotorbikeEntryWidget *entry : motorbikeEntries) {
            QString size = entry->getSize();
            QString fuel = entry->getFuelType();
            QString distance = entry->getDistance();

            if (size.isEmpty() || fuel.isEmpty() || distance.isEmpty()) {
                throw std::invalid_argument("Completează toate câmpurile pentru fiecare motocicletă.");
            }

            bool ok;
            double distanceValue = distance.toDouble(&ok);
            if (!ok || distanceValue <= 0) {
                throw std::invalid_argument("Distanța introdusă nu este validă.");
            }

            // Apelează funcția și obține emisiile
            std::string emissions = get_emissions_by_motorcycle(size.toStdString(), fuel.toStdString(), std::to_string(distanceValue), "km");
            cout << "Emissions: " << emissions << endl;

            if (emissions == "Error" || emissions.empty()) {
                throw std::runtime_error("Nu s-au putut calcula emisiile pentru motocicleta " + size.toStdString() + " cu combustibil " + fuel.toStdString() + ".");
            }

            double emissionValue = std::stod(emissions);
            total += emissionValue;

            results.append(QString("Emisiile pentru motocicleta %1 (%2) sunt: %3 kg CO2")
                           .arg(size, fuel, QString::number(emissionValue)));
        }

        QString message = QString("Total Carbon Footprint: %1 kg CO₂").arg(total);
        results.append(message);
        ExpensesPage::motorcycleCost = total;

        QMessageBox::information(this, "Emisii calculate", results.join("\n"));
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(e.what()));
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Eroare", QString::fromStdString(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Eroare", "A apărut o eroare neașteptată la calcularea emisiilor.");
    }
}
