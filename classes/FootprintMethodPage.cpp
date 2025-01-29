#include "FootprintMethodPage.h"

FootprintMethodPage::FootprintMethodPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    connectUI();
}

void FootprintMethodPage::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Buttons
    householdButton = new QPushButton("Calculate for an Entire Household", this);
    backButton = new QPushButton("Back", this);

    for (QPushButton *button : {householdButton, backButton}) {
        button->setStyleSheet(BUTTON_STYLE);
        layout->addWidget(button);
    }

//    // Input form (hidden initially)
//    promptLabel = new QLabel("Enter the number of people:", this);
//    inputField = new QLineEdit(this);
//    submitButton = new QPushButton("Submit", this);
//
//    promptLabel->setStyleSheet(INSTRUCTION_STYLE);
//    inputField->setStyleSheet(INPUT_STYLE);
//    submitButton->setStyleSheet(BUTTON_STYLE);
//
//    layout->addWidget(promptLabel);
//    layout->addWidget(inputField);
//    layout->addWidget(submitButton);
//
//    promptLabel->hide();
//    inputField->hide();
//    submitButton->hide();
//
//    // Initialize form layout and container
//    formLayout = new QFormLayout;
//    formLayout->addRow(new QLabel("Electricity (kWh):", this), new QLineEdit(this));
//    formLayout->addRow(new QLabel("Petrol (litres):", this), new QLineEdit(this));
//    formLayout->addRow(new QLabel("Natural Gas (metric tons):", this), new QLineEdit(this));
//
//    formContainer = new QWidget(this); // Initialize form container
//    formContainer->setLayout(formLayout);
//    formContainer->hide(); // Initially hidden
//
//    layout->addWidget(formContainer);
    setLayout(layout);

    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    showMaximized();
}

void FootprintMethodPage::connectUI() {
    connect(householdButton, &QPushButton::clicked, this, &FootprintMethodPage::onHouseholdButtonClicked);
}

void FootprintMethodPage::onHouseholdButtonClicked() {
    emit householdButtonClicked();
}
