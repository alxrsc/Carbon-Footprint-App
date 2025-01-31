#include "ExpensesPage.h"

double ExpensesPage::hotelStayCost = 0.0;
double ExpensesPage::householdCost = 0.0;
double ExpensesPage::flightsCost = 0.0;
double ExpensesPage::vehiclesCost = 0.0;
double ExpensesPage::motorcycleCost = 0.0;
double ExpensesPage::publicTransportCost = 0.0;

ExpensesPage::ExpensesPage(QWidget *parent) : QWidget(parent) {
    setupUi();
}



void ExpensesPage::setupUi() {
    mainLayout = new QVBoxLayout(this);

    // Scroll area for expense entries
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget(this);
    QVBoxLayout *expenseListLayout = new QVBoxLayout(scrollWidget);

    // Example of calculated results
    QLabel *householdCostLabel = new QLabel("Household cost: 0.0 kg CO2", this);
    QLabel *flightsCostLabel = new QLabel("Flights cost: 0.0 kg CO2", this);
    QLabel *vehiclesCostLabel = new QLabel("Vehicles cost: 0.0 kg CO2", this);
    QLabel *motorcycleCostLabel = new QLabel("Motorcycle cost: 0.0 kg CO2", this);
    QLabel *publicTransportCostLabel = new QLabel("Public transport cost: 0.0 kg CO2", this);
    QLabel *hotelCostLabel = new QLabel("Hotel stay cost: 0.0 kg CO2", this);

    // Carbon footprint summary
    QLabel *carbonFootprintLabel = new QLabel("Total Carbon Footprint: 0.0 kg CO2", this);

    // Adding labels to the expense list layout in the specified order
    expenseListLayout->addWidget(householdCostLabel);
    expenseListLayout->addWidget(flightsCostLabel);
    expenseListLayout->addWidget(vehiclesCostLabel);
    expenseListLayout->addWidget(motorcycleCostLabel);
    expenseListLayout->addWidget(publicTransportCostLabel);
    expenseListLayout->addWidget(hotelCostLabel);
    expenseListLayout->addWidget(carbonFootprintLabel);

    scrollWidget->setLayout(expenseListLayout);
    scrollArea->setWidget(scrollWidget);

    // Navigation buttons
    backButton = new QPushButton("< Hotel Stay", this);
    backButton->setStyleSheet(BUTTON_STYLE);

    QPushButton *updateButton = new QPushButton("Update Results", this);
    updateButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(updateButton);
    navLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(navLayout);

    // Apply a global background color
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();

    // Signal for updating results
    connect(updateButton, &QPushButton::clicked, this, [=]() {
        // Mock calculation logic (replace with your actual logic)
        double householdCost = ExpensesPage::householdCost;  // Replace with script output
        double flightsCost = ExpensesPage::flightsCost;   // Replace with script output
        double vehiclesCost = ExpensesPage::vehiclesCost; // Replace with script output
        double motorcycleCost = ExpensesPage::motorcycleCost; // Replace with script output
        double publicTransportCost = ExpensesPage::publicTransportCost; // Replace with script output
        double hotelCost = ExpensesPage::hotelStayCost;    // Replace with script output
        double totalCarbonFootprint = householdCost + flightsCost + vehiclesCost +
                                      motorcycleCost + publicTransportCost + hotelCost;

        // Update labels
        householdCostLabel->setText(QString("Household cost: %1 kg CO2").arg(householdCost));
        flightsCostLabel->setText(QString("Flights cost: %1 kg CO2").arg(flightsCost));
        vehiclesCostLabel->setText(QString("Vehicles cost: %1 kg CO2").arg(vehiclesCost));
        motorcycleCostLabel->setText(QString("Motorcycle cost: %1 kg CO2").arg(motorcycleCost));
        publicTransportCostLabel->setText(QString("Public transport cost: %1 kg CO2").arg(publicTransportCost));
        hotelCostLabel->setText(QString("Hotel stay cost: %1 kg CO2").arg(hotelCost));
        carbonFootprintLabel->setText(QString("Total Carbon Footprint: %1 kg CO2").arg(totalCarbonFootprint));
    });
}
