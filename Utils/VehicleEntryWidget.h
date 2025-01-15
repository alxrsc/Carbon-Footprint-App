#ifndef VEHICLEENTRYWIDGET_H
#define VEHICLEENTRYWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QStringList>
#include <QFormLayout>
#include <QPushButton>

class VehicleEntryWidget : public QWidget {
    Q_OBJECT

    public:
    explicit VehicleEntryWidget(const QStringList &makeList, const QMap<QString, QStringList> &modelMap, QWidget *parent = nullptr);
    QString getMake() const;
    QString getModel() const;
    QString getMileage() const;

    signals:
        void removeRequested(VehicleEntryWidget *entry);

private:
    QComboBox *makeInput;
    QComboBox *modelInput;
    QLineEdit *mileageInput;
    QComboBox *fuelTypeInput;
    QLineEdit *customCarTypeInput;
    QPushButton *removeButton;

    void setupUi(const QStringList &makeList, const QMap<QString, QStringList> &modelMap);
    void toggleCustomInput(bool enabled);
};

#endif // VEHICLEENTRYWIDGET_H
