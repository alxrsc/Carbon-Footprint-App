#include "HouseholdFootprintPage.h"
#include <QDebug>

HouseholdFootprintPage::HouseholdFootprintPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void HouseholdFootprintPage::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    headerLabel = new QLabel("Household Carbon Footprint Calculator", this);
    headerLabel->setStyleSheet(HEADER_STYLE);

    instructionLabel = new QLabel("Enter your household fuel usage details below:", this);
    instructionLabel->setStyleSheet(INSTRUCTION_STYLE);

    formLayout = new QFormLayout();

    electricityInput = new QLineEdit(this);
    electricityInput->setPlaceholderText("Enter electricity usage in kWh");
    electricityInput->setStyleSheet(INPUT_STYLE);

    petrolInput = new QLineEdit(this);
    petrolInput->setPlaceholderText("Enter petrol usage in litres");
    petrolInput->setStyleSheet(INPUT_STYLE);

    naturalGasInput = new QLineEdit(this);
    naturalGasInput->setPlaceholderText("Enter natural gas usage in metric tons");
    naturalGasInput->setStyleSheet(INPUT_STYLE);

    formLayout->addRow("Electricity (kWh):", electricityInput);
    formLayout->addRow("Petrol (litres):", petrolInput);
    formLayout->addRow("Natural Gas (metric tons):", naturalGasInput);

    calculateButton = new QPushButton("Calculate Carbon Footprint", this);
    calculateButton->setStyleSheet(BUTTON_STYLE);
    connect(calculateButton, &QPushButton::clicked, this, &HouseholdFootprintPage::calculateCarbonFootprint);

    resultLabel = new QLabel("", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("font-size: 16px; color: green;");

    backButton = new QPushButton("< Method", this);
    flightsButton = new QPushButton("Flights >", this);

    backButton->setStyleSheet(BUTTON_STYLE);
    flightsButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(flightsButton);
    navLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(resultLabel);
    mainLayout->addLayout(navLayout);

    setLayout(mainLayout);
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    showMaximized();
}

void HouseholdFootprintPage::calculateCarbonFootprint() {
    double electricity = electricityInput->text().toDouble();
    double petrol = petrolInput->text().toDouble();
    double naturalGas = naturalGasInput->text().toDouble();

    double totalCarbonFootprint = (electricity * 0.233) + (petrol * 2.31) + (naturalGas * 2.75); // Example factors

    ExpensesPage::householdCost = totalCarbonFootprint;

    if (totalCarbonFootprint > 0) {
        resultLabel->setText(QString("Total Carbon Footprint: %1 kg CO₂").arg(totalCarbonFootprint));
    } else {
        resultLabel->setText("Please enter valid numbers for all fields.");
    }
}
