#include "VehicleEntryWidget.h"

VehicleEntryWidget::VehicleEntryWidget(const QStringList &makeList, const QMap<QString, QStringList> &modelMap, QWidget *parent)
        : QWidget(parent) {
    setupUi(makeList, modelMap);
}

void VehicleEntryWidget::setupUi(const QStringList &makeList, const QMap<QString, QStringList> &modelMap) {
    auto *formLayout = new QFormLayout(this);

    makeInput = new QComboBox(this);
    makeInput->addItems(makeList);
    formLayout->addRow("Vehicle Make:", makeInput);

    modelInput = new QComboBox(this);
    formLayout->addRow("Vehicle Model:", modelInput);

    connect(makeInput, &QComboBox::currentTextChanged, this, [this, &modelMap](const QString &make) {
        modelInput->clear();
        modelInput->addItems(modelMap.value(make));
    });

    // fuelTypeInput = new QComboBox(this);
    // fuelTypeInput->addItems({"Diesel", "Petrol", "Electric", "Hybrid"});
    // formLayout->addRow("Fuel Type:", fuelTypeInput);

    mileageInput = new QLineEdit(this);
    formLayout->addRow("Mileage (km):", mileageInput);

    removeButton = new QPushButton("Remove", this);
    formLayout->addRow("", removeButton);

    connect(removeButton, &QPushButton::clicked, this, [this]() {
        emit removeRequested(this);
    });

    setLayout(formLayout);
}

QString VehicleEntryWidget::getMake() const {
    return makeInput->currentText();
}

QString VehicleEntryWidget::getModel() const {
    return modelInput->currentText();
}

QString VehicleEntryWidget::getMileage() const {
    return mileageInput->text();
}
