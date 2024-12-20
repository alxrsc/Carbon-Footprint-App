#ifndef FLIGHTSPAGE_H
#define FLIGHTSPAGE_H

#include <QStringList>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include "FlightEntryWidget.h"

class FlightsPage : public QWidget {
Q_OBJECT

public:
    explicit FlightsPage(QWidget *parent = nullptr);
    QPushButton* getBackButton() const { return backButton; }
    QPushButton* getAddFlightButton() const { return addFlightButton; }

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *flightListLayout;
    QScrollArea *scrollArea;
    QPushButton *addFlightButton;
    QList<FlightEntryWidget *> flightEntries;
    QStringList airportList;
    QPushButton *backButton;

    void setupUi();
    void addFlightEntry();
    void removeFlightEntry(FlightEntryWidget *entry);
    QStringList loadAirportsFromCsv(const QString &filePath);
};

#endif // FLIGHTSPAGE_H
