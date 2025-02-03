#include "HouseholdFootprintPage.h"
#include <QDebug>
#include <QProcess>

HouseholdFootprintPage::HouseholdFootprintPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void HouseholdFootprintPage::setupUI() {
    mainLayout = new QVBoxLayout(this);

    // Title
    QLabel *title = new QLabel("Household Carbon Footprint Calculator", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(HEADER_STYLE);
    mainLayout->addWidget(title);

    // Scroll area for input fields
    scrollArea = new QScrollArea(this);
    auto *scrollWidget = new QWidget(this);

    // Inițializare layout corect
    formLayout = new QFormLayout();
    scrollWidget->setLayout(formLayout);

    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    // Inputs
    electricityInput = new QLineEdit(this);
    electricityInput->setPlaceholderText("Enter electricity usage in kWh");
    electricityInput->setStyleSheet(INPUT_STYLE);
    formLayout->addRow(new QLabel("Electricity (kWh):", this), electricityInput);

    petrolInput = new QLineEdit(this);
    petrolInput->setPlaceholderText("Enter petrol usage in litres");
    petrolInput->setStyleSheet(INPUT_STYLE);
    formLayout->addRow(new QLabel("Petrol (litres):", this), petrolInput);

    naturalGasInput = new QLineEdit(this);
    naturalGasInput->setPlaceholderText("Enter natural gas usage in metric tons");
    naturalGasInput->setStyleSheet(INPUT_STYLE);
    formLayout->addRow(new QLabel("Natural Gas (metric tons):", this), naturalGasInput);

    // Calculate Button
    calculateButton = new QPushButton("Calculate Carbon Footprint", this);
    calculateButton->setStyleSheet(BUTTON_STYLE);
    connect(calculateButton, &QPushButton::clicked, this, &HouseholdFootprintPage::calculateCarbonFootprint);


    // Result Label
    resultLabel = new QLabel("", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("font-size: 16px");
    mainLayout->addWidget(resultLabel);

    // Navigation Buttons
    backButton = new QPushButton("< Method", this);
    backButton->setStyleSheet(BUTTON_STYLE);

    flightsButton = new QPushButton("Flights >", this);
    flightsButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    mainLayout->addWidget(calculateButton);
    navLayout->addWidget(backButton);
    navLayout->addWidget(flightsButton);
    navLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(navLayout);



    // Apply global background style and maximize
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();
}



void HouseholdFootprintPage::calculateCarbonFootprint() {
    QStringList results;
    double total = 0;

    try {
        QString electricity = electricityInput->text();
        QString petrol = petrolInput->text();
        QString naturalGas = naturalGasInput->text();

        if (electricity.isEmpty() && petrol.isEmpty() && naturalGas.isEmpty()) {
            throw std::invalid_argument("Complete at least one field!");
        }

        if (!electricity.isEmpty()) {
            std::string co2 = get_emissions_by_electricity("EU-27", electricity.toStdString(), "kWh");
            double co2_value = std::stod(co2);
            total += co2_value;
            results.append(QString("Electricity CO₂: %1 kg").arg(QString::fromStdString(co2)));
        }

        if (!petrol.isEmpty()) {
            std::string co2 = get_emissions_by_house_fuel("transport", "Regular Petrol", petrol.toStdString());
            double co2_value = std::stod(co2);
            total += co2_value;
            results.append(QString("Petrol CO₂: %1 kg").arg(QString::fromStdString(co2)));
        }

        if (!naturalGas.isEmpty()) {
            std::string co2 = get_emissions_by_house_fuel("commercial", "Natural Gas", naturalGas.toStdString());
            double co2_value = std::stod(co2);
            total += co2_value;
            results.append(QString("Natural Gas CO₂: %1 kg").arg(QString::fromStdString(co2)));
        }

        QString message = QString("Total Carbon Footprint: %1 kg CO₂").arg(total);
        results.append(message);
        ExpensesPage::householdCost = total;

        QMessageBox::information(this, "Calculated emissions", results.join("\n"));
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Error", "An unexpected error occurred while calculating emissions.");
    }
}


