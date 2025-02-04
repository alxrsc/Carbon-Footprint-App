#include "FlightsPage.h"

FlightsPage::FlightsPage(QWidget *parent) : QWidget(parent) {
    // Load airports from CSV
    airportList = loadAirportsFromCsv("../assets/airports.csv");

    setupUi();
}

void FlightsPage::setupUi() {
    mainLayout = new QVBoxLayout(this);

    // Header and Instructions
    QLabel *headerLabel = new QLabel("Flights Carbon Footprint Calculator", this);
    QLabel *instructionLabel = new QLabel("Add your flight details. Use the Add Flight button to add more.", this);
    headerLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setAlignment(Qt::AlignCenter);

    // Apply styling for the header and instructions
    headerLabel->setStyleSheet(HEADER_STYLE);
    instructionLabel->setStyleSheet(INSTRUCTION_STYLE);

    // Scroll area for flight entries
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget(this);
    flightListLayout = new QVBoxLayout(scrollWidget);

    scrollWidget->setLayout(flightListLayout);
    scrollArea->setWidget(scrollWidget);

    // Add the first flight entry by default
    addFlightEntry();

    // Add Flight button
    addFlightButton = new QPushButton("Add Flight", this);
    addFlightButton->setStyleSheet(BUTTON_STYLE);
    connect(addFlightButton, &QPushButton::clicked, this, &FlightsPage::addFlightEntry);

    // Calculate Emissions Button
    QPushButton *calculateEmissionsButton = new QPushButton("Calculate Emissions", this);
    calculateEmissionsButton->setStyleSheet(BUTTON_STYLE);
    connect(calculateEmissionsButton, &QPushButton::clicked, this, &FlightsPage::calculateFlightEmissions);
    //mainLayout->addWidget(calculateEmissionsButton);

    // Navigation buttons
    backButton = new QPushButton("< Household", this);
    vehicleButton = new QPushButton("Vehicles >", this);

    backButton->setStyleSheet(BUTTON_STYLE);
    vehicleButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(vehicleButton);
    navLayout->setAlignment(Qt::AlignCenter);

    // Add widgets to the main layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(addFlightButton);
    mainLayout->addWidget(calculateEmissionsButton);
    mainLayout->addLayout(navLayout);

    // Apply a global background color
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();
}

void FlightsPage::addFlightEntry() {
    FlightEntryWidget *flightEntry = new FlightEntryWidget(airportList, this);
    flightListLayout->addWidget(flightEntry);
    flightEntries.append(flightEntry);

    // Connect remove signal
    connect(flightEntry, &FlightEntryWidget::removeRequested, this, &FlightsPage::removeFlightEntry);
}

void FlightsPage::removeFlightEntry(FlightEntryWidget *entry) {
    flightListLayout->removeWidget(entry);
    flightEntries.removeOne(entry);
    entry->deleteLater();
}

QStringList FlightsPage::loadAirportsFromCsv(const QString &filePath) {
    QStringList airportList;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filePath;
        return airportList;
    }

    QTextStream in(&file);

    // Skip the header row
    if (!in.atEnd())
        in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        // Ensure there are enough fields to prevent errors
        if (fields.size() < 4)
            continue;

        QString code = fields[0].simplified();
        airportList.append(code);
    }

    file.close();
    return airportList;
}

void FlightsPage::calculateFlightEmissions() {
    // Clear previous emissions results if necessary
    QStringList results;
    double totalEmissions = 0;

    for (FlightEntryWidget *entry : flightEntries) {
        QString airportFrom = entry->getAirportFrom();
        QString airportTo = entry->getAirportTo();
        QString flightClass = entry->getFlightClass();
        QString roundTrip = entry->isRoundTrip() ? "Y" : "N";
        QString numberOfPassengers = entry->getNumberOfPassengers();

        if (airportFrom.isEmpty() || airportTo.isEmpty() || flightClass.isEmpty() || numberOfPassengers.isEmpty()) {
            QMessageBox::warning(this, "Date lipsă", "Completează toate câmpurile pentru fiecare zbor.");
            continue;
        }

        // Apelează funcția și obține emisiile
        string emissions = get_carbon_footprint_flight(
                airportFrom.toStdString(),
                airportTo.toStdString(),
                flightClass.toStdString(),
                roundTrip.toStdString(),
                numberOfPassengers.toStdString()
        );

        if (emissions == "Error" || emissions.empty()) {
            QMessageBox::warning(this, "Eroare", "Nu s-au putut calcula emisiile pentru zborul de la "
                                                 + airportFrom + " la " + airportTo + ".");
            continue;
        }

        try {
            double emissionValue = std::stod(emissions);
            totalEmissions += emissionValue;

            QString message = QString("Emisiile pentru zborul de la %1 la %2 sunt: %3 kg CO2")
                    .arg(airportFrom, airportTo, QString::number(emissionValue));
            results.append(message);
        } catch (const std::invalid_argument &e) {
            QMessageBox::warning(this, "Eroare", "Format invalid pentru emisiile calculate: "
                                                 + QString::fromStdString(emissions));
        }
    }

    ExpensesPage::flightsCost = totalEmissions;

    // Display all results at once
    if (!results.isEmpty()) {
        QMessageBox::information(this, "Emisii calculate", results.join("\n"));
    }
}

