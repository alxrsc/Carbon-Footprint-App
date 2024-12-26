#ifndef VEHICLEPAGE_H
#define VEHICLEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QList>
#include <QStringList>
#include <QMap>
#include <QLabel>
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
    QStringList makeList;
    QMap<QString, QStringList> modelMap;
    QPushButton *backButton;

    void setupUi();
    void addVehicleEntry();
    void removeVehicleEntry(VehicleEntryWidget *entry);
    void loadMakesAndModelsFromCsv(const QString &filePath);
};

#endif // VEHICLEPAGE_H
