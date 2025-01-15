#include "VehiclePage.h"

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

    // Emissions Button
    QPushButton *calculateEmissionsButton = new QPushButton("Calculate Emissions", this);
    calculateEmissionsButton->setStyleSheet(BUTTON_STYLE);
    connect(calculateEmissionsButton, &QPushButton::clicked, this, &VehiclePage::calculateEmissions);
    mainLayout->addWidget(calculateEmissionsButton);

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

void VehiclePage::calculateEmissions() {
    for (VehicleEntryWidget *entry : vehicleEntries) {
        QString make = entry->getMake();
        QString model = entry->getModel();
        QString distance = entry->getMileage();
        QString unit = "km"; // Presupunem că distanța este în kilometri

        if (make.isEmpty() || model.isEmpty() || distance.isEmpty()) {
            QMessageBox::warning(this, "Date lipsă", "Completează toate câmpurile pentru fiecare vehicul.");
            continue;
        }

        // Apelăm funcția C++ care apelează scriptul Python
        string emissions = get_emissions_by_vehicle_model(make.toStdString(), model.toStdString(), distance.toStdString(), unit.toStdString());

        // Verificăm dacă răspunsul este valid
        if (emissions == "Error") {
            QMessageBox::warning(this, "Eroare", "Nu s-au putut calcula emisiile pentru vehiculul selectat.");
            continue;
        }

        ExpensesPage::vehicleCost += stod(emissions);

        // Afișăm rezultatul
        QString message = QString("Emisiile pentru %1 %2 pe %3 %4 sunt: %5 kg CO2")
                .arg(make, model, distance, unit, QString::fromStdString(emissions));
        QMessageBox::information(this, "Emisii calculate", message);
    }
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
        if (parts.size() < 2) continue;
        QString make = parts.at(0).trimmed().remove("\"");  // Remove surrounding quotes
        QString model = parts.at(1).trimmed().remove("\""); // Remove surrounding quotes

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
