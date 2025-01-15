#include "FlightEntryWidget.h"

FlightEntryWidget::FlightEntryWidget(const QStringList &airportList, QWidget *parent)
        : QWidget(parent) {
    setupUi(airportList);
}

void FlightEntryWidget::setupUi(const QStringList &airportList) {
    QFormLayout *formLayout = new QFormLayout(this);

    // Departure airport input with autocomplete
    departureAirportInput = new QLineEdit(this);
    setupAutoCompleter(departureAirportInput, airportList);
    formLayout->addRow("From (IATA):", departureAirportInput);

    // Destination airport input with autocomplete
    destinationAirportInput = new QLineEdit(this);
    setupAutoCompleter(destinationAirportInput, airportList);
    formLayout->addRow("To (IATA):", destinationAirportInput);

    // Flight class selection
    classInput = new QComboBox(this);
    classInput->addItems({"Economy", "Premium Economy", "Business", "First Class"});
    formLayout->addRow("Flight Class:", classInput);

    // Round Trip Checkbox
    roundTripCheckBox = new QCheckBox(this);
    roundTripCheckBox->setText("Round Trip");
    formLayout->addRow("Round Trip :", roundTripCheckBox);

    // Radiative Forcing Checkbox
    // radiativeForcingCheckBox = new QCheckBox(this);
    // radiativeForcingCheckBox->setText("Radiative Forcing");
    // formLayout->addRow("Radiative Forcing :", radiativeForcingCheckBox);

    // Number of Passengers input
    numberOfPassengersInput = new QLineEdit(this);
    numberOfPassengersInput->setPlaceholderText("Number of Passengers");
    formLayout->addRow("Number of Passengers:", numberOfPassengersInput);

    // Remove button
    removeButton = new QPushButton("Remove", this);
    formLayout->addRow("", removeButton);

    connect(removeButton, &QPushButton::clicked, this, [this]() {
        emit removeRequested(this);
    });

    setLayout(formLayout);
}

void FlightEntryWidget::setupAutoCompleter(QLineEdit *lineEdit, const QStringList &airportList) {
    QCompleter *completer = new QCompleter(airportList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    lineEdit->setCompleter(completer);
}

QString FlightEntryWidget::getAirportFrom() const {
    return departureAirportInput->text();
}

QString FlightEntryWidget::getAirportTo() const {
    return destinationAirportInput->text();
}

QString FlightEntryWidget::getFlightClass() const {
    return classInput->currentText();
}

bool FlightEntryWidget::isRoundTrip() const {
    return roundTripCheckBox->isChecked();
}

QString FlightEntryWidget::getNumberOfPassengers() const {
    return numberOfPassengersInput->text(); // Corectat pentru a returna valoarea din câmpul de număr de pasageri
}
