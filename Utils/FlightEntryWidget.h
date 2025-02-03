// Created by Alexandru Roșca on 14.12.2024.

#ifndef CARBONFOOTPRINTAPP_FLIGHTENTRYWIDGET_H
#define CARBONFOOTPRINTAPP_FLIGHTENTRYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QCompleter>
#include <QStringList>
#include "../Utils/HotelStayEntryWidget.h"


class FlightEntryWidget : public QWidget {
    Q_OBJECT

    public:
    explicit FlightEntryWidget(const QStringList &airportList, QWidget *parent = nullptr);

    // Public fields for accessing inputs
    QLineEdit *departureAirportInput;
    QLineEdit *destinationAirportInput;
    QComboBox *classInput;
    QCheckBox *roundTripCheckBox;
    //QCheckBox *radiativeForcingCheckBox;
    QLineEdit *numberOfPassengersInput;

    QString getAirportFrom() const;
    QString getAirportTo() const;
    QString getFlightClass() const;
    bool isRoundTrip() const;
    QString getNumberOfPassengers() const;

    signals:
        void removeRequested(FlightEntryWidget *entry);

private:
    QPushButton *removeButton;

    void setupAutoCompleter(QLineEdit *lineEdit, const QStringList &airportList);
    void setupUi(const QStringList &airportList);
};

#endif //CARBONFOOTPRINTAPP_FLIGHTENTRYWIDGET_H
