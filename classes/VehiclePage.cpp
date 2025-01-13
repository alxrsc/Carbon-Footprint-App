#include "VehiclePage.h"

// Common Styles
const QString GLOBAL_BACKGROUND_STYLE = "background: linear-gradient(to bottom, #e0f7fa, #80deea); font-family: Arial, sans-serif;";
const QString HEADER_STYLE = "font-size: 24px; font-weight: bold; color: #004d40; text-align: center;";
const QString INSTRUCTION_STYLE = "font-size: 16px; color: #004d40; text-align: center; margin: 10px 0;";
const QString BUTTON_STYLE = "QPushButton {"
                             "font-size: 16px; font-weight: bold; color: white; background-color: #00796b; border-radius: 5px; padding: 10px;"
                             "} QPushButton:hover { background-color: #004d40; }";
const QString INPUT_STYLE = "padding: 8px; border: 1px solid #004d40; border-radius: 4px;";

VehiclePage::VehiclePage(QWidget *parent) : QWidget(parent) {
    // Load vehicle makes and models
    loadMakesAndModelsFromCsv("../assets/vehicles.csv");

    // Setup UI
    setupUi();
}

void VehiclePage::setupUi() {
    mainLayout = new QVBoxLayout(this);

    // Title
    QLabel *title = new QLabel("Manage Vehicles", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(HEADER_STYLE);
    mainLayout->addWidget(title);

    // Scroll area for vehicle entries
    scrollArea = new QScrollArea(this);
    auto *scrollWidget = new QWidget(this);
    vehicleListLayout = new QVBoxLayout(scrollWidget);
    scrollWidget->setLayout(vehicleListLayout);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    // Add the first vehicle entry by default
    addVehicleEntry();

    // Add Vehicle Button
    addVehicleButton = new QPushButton("Add Vehicle", this);
    addVehicleButton->setStyleSheet(BUTTON_STYLE);
    connect(addVehicleButton, &QPushButton::clicked, this, &VehiclePage::addVehicleEntry);
    mainLayout->addWidget(addVehicleButton);

    // Back Button
    backButton = new QPushButton("< Flights", this);
    backButton->setStyleSheet(BUTTON_STYLE);

    // Motorbike Button
    motorbikeButton = new QPushButton("Motorbikes >", this);
    motorbikeButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(motorbikeButton);
    navLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(navLayout);

    // Apply global background style and maximize
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();
}

void VehiclePage::addVehicleEntry() {
    // Create a new VehicleEntryWidget
    auto *vehicleEntry = new VehicleEntryWidget(makeList, modelMap, this);

    // Add the widget to the layout and keep track of it
    vehicleListLayout->addWidget(vehicleEntry);
    vehicleEntries.append(vehicleEntry);

    // Connect the remove request signal to handle entry deletion
    connect(vehicleEntry, &VehicleEntryWidget::removeRequested, this, &VehiclePage::removeVehicleEntry);
}

void VehiclePage::removeVehicleEntry(VehicleEntryWidget *entry) {
    // Remove the entry from the list and layout
    vehicleEntries.removeAll(entry);
    vehicleListLayout->removeWidget(entry);
    entry->deleteLater();
}

void VehiclePage::loadMakesAndModelsFromCsv(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not load vehicle data.");
        return;
    }

    QTextStream in(&file);
    QSet<QString> uniqueModels; // To track unique models for each make.

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        // Validate and parse line
        if (parts.size() < 4) continue;
        QString make = parts.at(1).trimmed().remove("\"");  // Remove surrounding quotes
        QString model = parts.at(3).trimmed().remove("\""); // Remove surrounding quotes

        // Add make to list if not already present
        if (!makeList.contains(make)) {
            makeList.append(make);
        }

        // Add unique model for the make
        QString modelKey = make + "|" + model; // Unique key to track models per make
        if (!uniqueModels.contains(modelKey)) {
            modelMap[make].append(model);
            uniqueModels.insert(modelKey);
        }
    }

    file.close();
}
