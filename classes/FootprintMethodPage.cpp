#include "FootprintMethodPage.h"
#include "CommonStyles.h"

FootprintMethodPage::FootprintMethodPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    connectUI();
}

void FootprintMethodPage::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Buttons
    peopleButton = new QPushButton("Calculate for a Specific Number of People", this);
    householdButton = new QPushButton("Calculate for an Entire Household", this);
    backButton = new QPushButton("Back", this);

    for (QPushButton *button : {peopleButton, householdButton, backButton}) {
        button->setStyleSheet(BUTTON_STYLE);
        layout->addWidget(button);
    }

    // Input form (hidden initially)
    promptLabel = new QLabel("Enter the number of people:", this);
    inputField = new QLineEdit(this);
    submitButton = new QPushButton("Submit", this);

    promptLabel->setStyleSheet(INSTRUCTION_STYLE);
    inputField->setStyleSheet(INPUT_STYLE);
    submitButton->setStyleSheet(BUTTON_STYLE);

    layout->addWidget(promptLabel);
    layout->addWidget(inputField);
    layout->addWidget(submitButton);

    promptLabel->hide();
    inputField->hide();
    submitButton->hide();

    // Initialize form layout and container
    formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Electricity (kWh):", this), new QLineEdit(this));
    formLayout->addRow(new QLabel("Petrol (litres):", this), new QLineEdit(this));
    formLayout->addRow(new QLabel("Natural Gas (metric tons):", this), new QLineEdit(this));

    formContainer = new QWidget(this); // Initialize form container
    formContainer->setLayout(formLayout);
    formContainer->hide(); // Initially hidden

    layout->addWidget(formContainer);
    setLayout(layout);

    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    showMaximized();
}

void FootprintMethodPage::connectUI() {
    connect(peopleButton, &QPushButton::clicked, this, &FootprintMethodPage::showPeopleInputForm);
    connect(submitButton, &QPushButton::clicked, this, &FootprintMethodPage::submitPeopleCount);
    connect(householdButton, &QPushButton::clicked, this, &FootprintMethodPage::onHouseholdButtonClicked);
}

void FootprintMethodPage::showPeopleInputForm() {
    // Hide main buttons
    peopleButton->hide();
    householdButton->hide();
    backButton->hide();

    // Show input form
    promptLabel->show();
    inputField->show();
    submitButton->show();
}

void FootprintMethodPage::submitPeopleCount() {
    bool ok;
    int count = inputField->text().toInt(&ok);

    if (ok && count > 0) {
        // Emit signal with valid count
        emit peopleCountEntered(count);
        inputField->clear();

        // Show form layout for additional inputs
        promptLabel->hide();
        inputField->hide();
        submitButton->hide();
        formContainer->show();
    } else {
        inputField->clear();
        inputField->setPlaceholderText("Please enter a valid number");
    }
}

void FootprintMethodPage::onHouseholdButtonClicked() {
    emit householdButtonClicked();
}
