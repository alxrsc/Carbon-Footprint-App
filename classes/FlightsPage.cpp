#include "FlightsPage.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Common Styles
const QString GLOBAL_BACKGROUND_STYLE = "background: linear-gradient(to bottom, #e0f7fa, #80deea); font-family: Arial, sans-serif;";
const QString HEADER_STYLE = "font-size: 24px; font-weight: bold; color: #004d40; text-align: center;";
const QString INSTRUCTION_STYLE = "font-size: 16px; color: #004d40; text-align: center; margin: 10px 0;";
const QString BUTTON_STYLE = "QPushButton {"
                             "font-size: 16px; font-weight: bold; color: white; background-color: #00796b; border-radius: 5px; padding: 10px;"
                             "} QPushButton:hover { background-color: #004d40; }";

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
