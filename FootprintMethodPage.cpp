#include "FootprintMethodPage.h"

FootprintMethodPage::FootprintMethodPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Initialize main buttons
    peopleButton = new QPushButton(this);
    householdButton = new QPushButton(this);
    backButton = new QPushButton(this);

    peopleButton->setStyleSheet("QPushButton { font-size: 16px; font-weight: bold; color: lightgreen; background-color: gray; border-radius: 5px; padding: 10px; }");
    householdButton->setStyleSheet("QPushButton { font-size: 16px; font-weight: bold; color: lightgreen; background-color: gray; border-radius: 5px; padding: 10px; }");
    backButton->setStyleSheet("QPushButton { font-size: 16px; font-weight: bold; color: lightgreen; background-color: gray; border-radius: 5px; padding: 10px; }");

    // Add buttons to the layout
    layout->addWidget(peopleButton);
    layout->addWidget(householdButton);
    layout->addWidget(backButton);
    layout->setAlignment(Qt::AlignCenter);

    // Initialize the input form but keep it hidden
    promptLabel = new QLabel(this);
    inputField = new QLineEdit(this);
    submitButton = new QPushButton(this);

    promptLabel->setStyleSheet("font-size: 14px;");
    inputField->setStyleSheet("font-size: 14px; padding: 5px;");
    submitButton->setStyleSheet("QPushButton { font-size: 16px; font-weight: bold; color: lightgreen; background-color: gray; border-radius: 5px; padding: 10px; }");

    // Initially hide the input elements
    promptLabel->hide();
    inputField->hide();
    submitButton->hide();

    // Add input elements to layout
    layout->addWidget(promptLabel);
    layout->addWidget(inputField);
    layout->addWidget(submitButton);

    setLayout(layout);
    setWindowTitle("Footprint Calculation Method");
    setStyleSheet("background-color: lightblue;");
    showMaximized();

    initializeTranslations();

    // Connect buttons to their respective slots
    connect(peopleButton, &QPushButton::clicked, this, &FootprintMethodPage::showPeopleInputForm);
    connect(submitButton, &QPushButton::clicked, this, &FootprintMethodPage::submitPeopleCount);
    connect(householdButton, &QPushButton::clicked, this, &FootprintMethodPage::onHouseholdButtonClicked);  // Connect household button click to slot
}

void FootprintMethodPage::initializeTranslations() {
    // English translations
    translations["English"]["peopleButton"] = "Calculate for a Specific Number of People";
    translations["English"]["householdButton"] = "Calculate for an Entire Household";
    translations["English"]["backButton"] = "Back";
    translations["English"]["promptLabel"] = "Enter the number of people:";
    translations["English"]["submitButton"] = "Submit";
    translations["English"]["enterValidNumber"] = "Please enter a valid number";

    // Romanian translations
    translations["Romanian"]["peopleButton"] = "Calculați pentru un număr specific de persoane";
    translations["Romanian"]["householdButton"] = "Calculați pentru întreaga gospodărie";
    translations["Romanian"]["backButton"] = "Înapoi";
    translations["Romanian"]["promptLabel"] = "Introduceți numărul de persoane:";
    translations["Romanian"]["submitButton"] = "Trimite";
    translations["Romanian"]["enterValidNumber"] = "Vă rugăm să introduceți un număr valid";

    // Spanish translations
    translations["Spanish"]["peopleButton"] = "Calcular para un número específico de personas";
    translations["Spanish"]["householdButton"] = "Calcular para todo el hogar";
    translations["Spanish"]["backButton"] = "Regresar";
    translations["Spanish"]["promptLabel"] = "Ingrese el número de personas:";
    translations["Spanish"]["submitButton"] = "Enviar";
    translations["Spanish"]["enterValidNumber"] = "Por favor, introduzca un número válido";
}

void FootprintMethodPage::updateLanguage(const QString &language) {
    // Set button texts based on the selected language
    if (translations.contains(language)) {
        peopleButton->setText(translations[language]["peopleButton"]);
        householdButton->setText(translations[language]["householdButton"]);
        backButton->setText(translations[language]["backButton"]);
        promptLabel->setText(translations[language]["promptLabel"]);
        submitButton->setText(translations[language]["submitButton"]);
        inputField->setPlaceholderText(translations[language]["enterValidNumber"]);
    }
}

void FootprintMethodPage::showPeopleInputForm() {
    // Hide the main buttons and show the input form elements
    peopleButton->hide();
    householdButton->hide();
    backButton->hide();

    promptLabel->show();
    inputField->show();
    submitButton->show();
}

void FootprintMethodPage::submitPeopleCount() {
    // Get the number of people from the input field
    bool ok;
    int count = inputField->text().toInt(&ok);

    if (ok && count > 0) {
        // Emit the peopleCountEntered signal with the entered count
        emit peopleCountEntered(count);

        // Optionally, clear the input for future entries
        inputField->clear();

        // Hide the input form and show the main buttons again
        promptLabel->hide();
        inputField->hide();
        submitButton->hide();
        peopleButton->show();
        householdButton->show();
        backButton->show();
    } else {
        // If input is invalid, clear the field and show an error
        inputField->clear();
//        inputField->setPlaceholderText(translations[selectedLanguage]["enterValidNumber"]);
    }
}

void FootprintMethodPage::onHouseholdButtonClicked() {
    emit householdButtonClicked();  // Emit the signal when household button is clicked
}
