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

    // Calculate button
    calculateButton = new QPushButton("Calculate Carbon Footprint", this);
    calculateButton->setStyleSheet(BUTTON_STYLE);
    connect(calculateButton, &QPushButton::clicked, this, &HotelStayPage::calculateCarbonFootprint);

    // Result display
    resultLabel = new QLabel("", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("font-size: 16px; color: green;");

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
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(resultLabel);
    mainLayout->addLayout(navLayout);

    // Apply a global background color
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();
}

void HotelStayPage::addHotelStayEntry() {
    QWidget *entryWidget = new QWidget(this);
    QHBoxLayout *entryLayout = new QHBoxLayout(entryWidget);

    // Input for country code
    QLineEdit *countryCodeInput = new QLineEdit(entryWidget);
    countryCodeInput->setPlaceholderText("Enter country code (e.g., US, UK)");

    // Input for city name (optional)
    QLineEdit *cityInput = new QLineEdit(entryWidget);
    cityInput->setPlaceholderText("Enter city name (optional)");

    // Dropdown for hotel rating (optional)
    QComboBox *ratingComboBox = new QComboBox(entryWidget);
    ratingComboBox->addItem("Select Rating");
    for (int i = 2; i <= 5; ++i) {
        ratingComboBox->addItem(QString::number(i) + " Stars");
    }

    // Input for number of nights
    QLineEdit *nightsInput = new QLineEdit(entryWidget);
    nightsInput->setPlaceholderText("Enter number of nights");

    // Input for number of rooms
    QLineEdit *roomsInput = new QLineEdit(entryWidget);
    roomsInput->setPlaceholderText("Enter number of rooms");

    // Remove button
    QPushButton *removeButton = new QPushButton("Remove", entryWidget);
    removeButton->setStyleSheet(BUTTON_STYLE);

    connect(removeButton, &QPushButton::clicked, [this, entryWidget]() {
        removeHotelStayEntry(entryWidget);
    });

    entryLayout->addWidget(new QLabel("Country Code:"));
    entryLayout->addWidget(countryCodeInput);
    entryLayout->addWidget(new QLabel("City (Optional):"));
    entryLayout->addWidget(cityInput);
    entryLayout->addWidget(new QLabel("Rating:"));
    entryLayout->addWidget(ratingComboBox);
    entryLayout->addWidget(new QLabel("Nights:"));
    entryLayout->addWidget(nightsInput);
    entryLayout->addWidget(new QLabel("Rooms:"));
    entryLayout->addWidget(roomsInput);
    entryLayout->addWidget(removeButton);

    hotelStayListLayout->addWidget(entryWidget);
    hotelStayEntries.append(entryWidget);

    // Store references to input fields for data collection
    HotelStayEntry entry;
    entry.countryCodeInput = countryCodeInput;
    entry.cityInput = cityInput;
    entry.ratingComboBox = ratingComboBox;
    entry.nightsInput = nightsInput;
    entry.roomsInput = roomsInput;
    hotelStayInputs.append(entry);
}

void HotelStayPage::removeHotelStayEntry(QWidget *entry) {
    hotelStayListLayout->removeWidget(entry);
    hotelStayEntries.removeOne(entry);
    entry->deleteLater();
}

void HotelStayPage::calculateCarbonFootprint() {
    double totalCarbonFootprint = 0.0;
    for (const HotelStayEntry &entry : hotelStayInputs) {
        QString command = "python3";
        QStringList arguments;
        arguments << "../backend-api-scripts/emissions_by_hotelStay.py"
                  << entry.countryCodeInput->text()
                  << entry.cityInput->text()
                  << entry.ratingComboBox->currentText().split(" ").first()
                  << entry.nightsInput->text()
                  << entry.roomsInput->text();

        QProcess process;
        process.start(command, arguments);
        process.waitForFinished();

        QByteArray output = process.readAllStandardOutput();
        QByteArray error = process.readAllStandardError();

        if (!error.isEmpty()) {
            qDebug() << "Error:" << error;
            continue;
        }

        if (output.isEmpty()) {
            qDebug() << "No output received from the script.";
            continue;
        }

        QJsonDocument jsonResponse = QJsonDocument::fromJson(output);
        if (jsonResponse.isObject()) {
            QJsonObject responseObject = jsonResponse.object();
            if (responseObject.contains("co2e_kg")) {
                totalCarbonFootprint += responseObject["co2e_kg"].toDouble();
            }
        }
    }

    resultLabel->setText(QString("Total Carbon Footprint: %1 kg CO₂").arg(totalCarbonFootprint));
}
