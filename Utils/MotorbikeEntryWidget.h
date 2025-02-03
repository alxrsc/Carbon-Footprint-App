
#ifndef MOTORBIKEENTRYWIDGET_H
#define MOTORBIKEENTRYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>

class MotorbikeEntryWidget : public QWidget {
    Q_OBJECT

public:
    explicit MotorbikeEntryWidget(QWidget *parent = nullptr);

    // Public fields for accessing inputs
    QComboBox *sizeInput;
    QComboBox *fuelInput;
    QLineEdit *distanceInput;

    QString getSize() const;
    QString getFuelType() const;
    QString getDistance() const;

    signals:
        void removeRequested(MotorbikeEntryWidget *entry);

private:
    QPushButton *removeButton;
    void setupUi();
};

#endif //CARBONFOOTPRINTAPP_MOTORBIKEENTRYWIDGET_H


