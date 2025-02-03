// Updated HotelStayPage.cpp
#include "HotelStayPage.h"
#include <QProcess>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

HotelStayPage::HotelStayPage(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void HotelStayPage::setupUi() {
    mainLayout = new QVBoxLayout(this);

    // Header and Instructions
    QLabel *headerLabel = new QLabel("Hotel Stay Carbon Footprint Calculator", this);
    QLabel *instructionLabel = new QLabel("Add your hotel stay details. Use the Add Stay button to add more.", this);
    headerLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setAlignment(Qt::AlignCenter);

    // Apply styling for the header and instructions
    headerLabel->setStyleSheet(HEADER_STYLE);
    instructionLabel->setStyleSheet(INSTRUCTION_STYLE);

    // Scroll area for hotel stay entries
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget(this);
    hotelStayListLayout = new QVBoxLayout(scrollWidget);

    scrollWidget->setLayout(hotelStayListLayout);
    scrollArea->setWidget(scrollWidget);

    // Add the first hotel stay entry by default
    addHotelStayEntry();

    // Add Stay button
    addHotelStayButton = new QPushButton("Add Stay", this);
    addHotelStayButton->setStyleSheet(BUTTON_STYLE);
    connect(addHotelStayButton, &QPushButton::clicked, this, &HotelStayPage::addHotelStayEntry);

    // Calculate Emissions Button
    QPushButton *calculateEmissionsButton = new QPushButton("Calculate Emissions", this);
    calculateEmissionsButton->setStyleSheet(BUTTON_STYLE);
    connect(calculateEmissionsButton, &QPushButton::clicked, this, &HotelStayPage::calculateCarbonFootprint);

    // Navigation buttons
    backButton = new QPushButton("< Back", this);
    expensesPageButton = new QPushButton("Results >", this);

    backButton->setStyleSheet(BUTTON_STYLE);
    expensesPageButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(expensesPageButton);
    navLayout->setAlignment(Qt::AlignCenter);

    // Add widgets to the main layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(addHotelStayButton);
    mainLayout->addWidget(calculateEmissionsButton);
    mainLayout->addLayout(navLayout);

    // Apply a global background color
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();
}

void HotelStayPage::addHotelStayEntry() {
    HotelStayEntryWidget *hotelEntry = new HotelStayEntryWidget(this);
    hotelStayListLayout->addWidget(hotelEntry);
    hotelStayEntries.append(hotelEntry);

    // Connect remove signal
    connect(hotelEntry, &HotelStayEntryWidget::removeRequested, this, &HotelStayPage::removeHotelStayEntry);
}

void HotelStayPage::removeHotelStayEntry(HotelStayEntryWidget *entry) {
    hotelStayListLayout->removeWidget(entry);
    hotelStayEntries.removeOne(entry);
    entry->deleteLater();
}
void HotelStayPage::calculateCarbonFootprint() {
    // Curățare rezultate anterioare
    QStringList results;
    double totalCarbonFootprint = 0.0;

    for (HotelStayEntryWidget *entry : hotelStayEntries) {
        QString countryCode = entry->countryCodeInput->text();
        QString city = entry->cityInput->text();
        QString rating = entry->ratingComboBox->currentText().split(" ").first();
        QString nights = entry->nightsInput->text();
        QString rooms = entry->roomsInput->text();

        if (countryCode.isEmpty() || city.isEmpty() || rating.isEmpty() || nights.isEmpty() || rooms.isEmpty()) {
            QMessageBox::warning(this, "Date lipsă", "Completează toate câmpurile pentru fiecare rezervare.");
            continue;
        }
        // Apelează funcția și obține emisiile
        string emissions = get_emissions_by_hotelStay(
                countryCode.toStdString(),
                city.toStdString(),
                rating.toStdString(),
                nights.toStdString(),
                rooms.toStdString()
        );
        if (emissions == "Error" || emissions.empty()) {
            QMessageBox::warning(this, "Eroare", "Nu s-au putut calcula emisiile pentru șederea în "
                                                 + city + " (" + countryCode + ").");
            continue;
        }

        try {
            double emissionValue = std::stod(emissions);
            totalCarbonFootprint += emissionValue;

            QString message = QString("Emisiile pentru șederea în %1 (%2) sunt: %3 kg CO2")
                    .arg(city, countryCode, QString::number(emissionValue));
            results.append(message);
        } catch (const std::invalid_argument &e) {
            QMessageBox::warning(this, "Eroare", "Format invalid pentru emisiile calculate: "
                                                 + QString::fromStdString(emissions));
        }
    }

    ExpensesPage::hotelStayCost = totalCarbonFootprint;

    // Afișare rezultate
    if (!results.isEmpty()) {
        QMessageBox::information(this, "Emisii calculate", results.join("\n"));
    }
}

