//
// Created by Alexandru Roșca on 23.12.2024.
//

#ifndef CARBONFOOTPRINTAPP_VEHICLEPAGE_H
#define CARBONFOOTPRINTAPP_VEHICLEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QList>
#include "../Utils/VehicleEntryWidget.h"

class VehiclePage : public QWidget {
Q_OBJECT

public:
    explicit VehiclePage(QWidget *parent = nullptr);
    QPushButton *getBackButton() const { return backButton; }

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *vehicleListLayout;
    QScrollArea *scrollArea;
    QPushButton *addVehicleButton;
    QList<VehicleEntryWidget *> vehicleEntries;
    QPushButton *backButton;

    void setupUI();
    void addVehicleEntry();
    void removeVehicleEntry(VehicleEntryWidget *entry);


};


#endif //CARBONFOOTPRINTAPP_VEHICLEPAGE_H
