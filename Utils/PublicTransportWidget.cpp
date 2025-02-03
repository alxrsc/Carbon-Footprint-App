//
// Created by leupe on 03.02.2025.
//

#include "PublicTransportWidget.h"
PublicTransportEntryWidget::PublicTransportEntryWidget(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void PublicTransportEntryWidget::setupUi() {
    QFormLayout *formLayout = new QFormLayout(this);

    // Transport Type Input
    transportTypeInput = new QComboBox(this);
    transportTypeInput->addItems({"Bus-LocalAverage", "Bus-Coach", "Train-National","Train-Local", "Train-Tram", "Taxi-Local"});
    formLayout->addRow("Transport Type:", transportTypeInput);

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

QString PublicTransportEntryWidget::getTransportType() const {
    return transportTypeInput->currentText();
}

QString PublicTransportEntryWidget::getDistance() const {
    return distanceInput->text();
}
