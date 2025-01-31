#ifndef FLIGHTSPAGE_H
#define FLIGHTSPAGE_H

#include "CommonStyles.h"
#include "../Utils/FlightEntryWidget.h"
#include "../APICalls.h"
#include "ExpensesPage.h"

#include <QStringList>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

class FlightsPage : public QWidget {
    Q_OBJECT

    public:
    explicit FlightsPage(QWidget *parent = nullptr);
    QPushButton *getBackButton() const { return backButton; }
    QPushButton *getVehicleButton() const { return vehicleButton; }

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *flightListLayout;
    QScrollArea *scrollArea;
    QPushButton *addFlightButton;
    QList<FlightEntryWidget *> flightEntries;
    QStringList airportList;
    QPushButton *backButton;
    QPushButton *vehicleButton;

    void setupUi();
    void addFlightEntry();
    void removeFlightEntry(FlightEntryWidget *entry);
    void calculateFlightEmissions();
    QStringList loadAirportsFromCsv(const QString &filePath);

};

#endif // FLIGHTSPAGE_H
