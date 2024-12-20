#include "FlightsPage.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

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
    headerLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: darkblue;");
    instructionLabel->setStyleSheet("font-size: 16px; color: darkblue;");

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
    addFlightButton->setStyleSheet("font-size: 16px; font-weight: bold; color: white; background-color: green; border-radius: 5px; padding: 10px;");
    connect(addFlightButton, &QPushButton::clicked, this, &FlightsPage::addFlightEntry);

    // Navigation buttons
    backButton = new QPushButton("< Household", this);
    QPushButton *nextButton = new QPushButton("Results >", this);

    backButton->setStyleSheet("font-size: 16px; font-weight: bold; color: white; background-color: gray; border-radius: 5px; padding: 10px;");
    nextButton->setStyleSheet("font-size: 16px; font-weight: bold; color: white; background-color: gray; border-radius: 5px; padding: 10px;");

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(nextButton);
    navLayout->setAlignment(Qt::AlignCenter);

    // Add widgets to the main layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(addFlightButton);
    mainLayout->addLayout(navLayout);

    // Apply a global background color
    setStyleSheet("background-color: lightblue;");
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
