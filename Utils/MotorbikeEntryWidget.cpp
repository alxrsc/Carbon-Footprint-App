#ifndef CARBONFOOTPRINTAPP_MOTORBIKEENTRYWIDGET_H
#define CARBONFOOTPRINTAPP_MOTORBIKEENTRYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include "MotorbikeEntryWidget.h"


#endif //CARBONFOOTPRINTAPP_MOTORBIKEENTRYWIDGET_H


MotorbikeEntryWidget::MotorbikeEntryWidget(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void MotorbikeEntryWidget::setupUi() {
    QFormLayout *formLayout = new QFormLayout(this);

    // Motorbike Size Input
    sizeInput = new QComboBox(this);
    sizeInput->addItems({"Small", "Medium", "Large"});
    formLayout->addRow("Motorbike Size:", sizeInput);

    // Fuel Type Input
    fuelInput = new QComboBox(this);
    fuelInput->addItems({"Petrol", "Diesel", "Electric"});
    formLayout->addRow("Fuel Type:", fuelInput);

    // Distance Input
    distanceInput = new QLineEdit(this);
    distanceInput->setPlaceholderText("Enter distance in km");
    formLayout->addRow("Distance (km):", distanceInput);

    // Remove Button
    removeButton = new QPushButton("Remove", this);
    formLayout->addRow("", removeButton);

    connect(removeButton, &QPushButton::clicked, this, [this]() {
        emit removeRequested(this);
    });

    setLayout(formLayout);
}

QString MotorbikeEntryWidget::getSize() const {
    return sizeInput->currentText();
}

QString MotorbikeEntryWidget::getFuelType() const {
    return fuelInput->currentText();
}

QString MotorbikeEntryWidget::getDistance() const {
    return distanceInput->text();
}
