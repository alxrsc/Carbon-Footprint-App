#ifndef VEHICLEPAGE_H
#define VEHICLEPAGE_H

#include "CommonStyles.h"
#include "../Utils/VehicleEntryWidget.h"
#include "../APICalls.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QList>
#include <QStringList>
#include <QMap>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class VehiclePage : public QWidget {
    Q_OBJECT

    public:
    explicit VehiclePage(QWidget *parent = nullptr);
    QPushButton *getBackButton() const { return backButton; }
    QPushButton *getMotorbikeButton() const { return motorbikeButton; }

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *vehicleListLayout;
    QScrollArea *scrollArea;
    QPushButton *addVehicleButton;
    QList<VehicleEntryWidget *> vehicleEntries;
    QStringList makeList;
    QMap<QString, QStringList> modelMap;
    QPushButton *backButton;
    QPushButton *motorbikeButton;

    void setupUi();
    void addVehicleEntry();
    void removeVehicleEntry(VehicleEntryWidget *entry);
    void calculateEmissions();
    void loadMakesAndModelsFromCsv(const QString &filePath);
};

#endif // VEHICLEPAGE_H
