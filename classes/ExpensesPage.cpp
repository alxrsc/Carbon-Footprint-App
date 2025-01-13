//
// Created by Alexandru Roșca on 14.01.2025.
//

#include "ExpensesPage.h"

ExpensesPage::ExpensesPage(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void ExpensesPage::setupUi() {
    mainLayout = new QVBoxLayout(this);

    // Header and Instructions
    QLabel *headerLabel = new QLabel("Expense Fund Carbon Footprint Calculator", this);
    QLabel *instructionLabel = new QLabel("Add your expense estimations for food, clothing, and services.", this);
    headerLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setAlignment(Qt::AlignCenter);

    // Apply styling for the header and instructions
    headerLabel->setStyleSheet(HEADER_STYLE);
    instructionLabel->setStyleSheet(INSTRUCTION_STYLE);

    // Scroll area for expense entries
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget(this);
    expenseListLayout = new QVBoxLayout(scrollWidget);

    scrollWidget->setLayout(expenseListLayout);
    scrollArea->setWidget(scrollWidget);

    // Add the first expense entry by default
    addExpenseEntry();

    // Add Expense button
    addExpenseButton = new QPushButton("Add Expense", this);
    addExpenseButton->setStyleSheet(BUTTON_STYLE);
    connect(addExpenseButton, &QPushButton::clicked, this, &ExpensesPage::addExpenseEntry);

    // Navigation buttons
    backButton = new QPushButton("< Back", this);
    nextButton = new QPushButton("Next >", this);

    backButton->setStyleSheet(BUTTON_STYLE);
    nextButton->setStyleSheet(BUTTON_STYLE);

    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->addWidget(backButton);
    navLayout->addWidget(nextButton);
    navLayout->setAlignment(Qt::AlignCenter);

    // Add widgets to the main layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(addExpenseButton);
    mainLayout->addLayout(navLayout);

    // Apply a global background color
    setStyleSheet(GLOBAL_BACKGROUND_STYLE);
    setLayout(mainLayout);
    showMaximized();
}

void ExpensesPage::addExpenseEntry() {
    QWidget *entryWidget = new QWidget(this);
    QHBoxLayout *entryLayout = new QHBoxLayout(entryWidget);

    // Input for money amount
    QLineEdit *moneyInput = new QLineEdit(entryWidget);
    moneyInput->setPlaceholderText("Enter amount (e.g., 100.50)");

    // Input for money unit (ISO code)
    QLineEdit *moneyUnitInput = new QLineEdit(entryWidget);
    moneyUnitInput->setPlaceholderText("Enter currency code (e.g., USD)");

    // Remove button
    QPushButton *removeButton = new QPushButton("Remove", entryWidget);
    removeButton->setStyleSheet(BUTTON_STYLE);

    connect(removeButton, &QPushButton::clicked, [=]() {
        removeExpenseEntry(entryWidget);
    });

    entryLayout->addWidget(new QLabel("Amount:"));
    entryLayout->addWidget(moneyInput);
    entryLayout->addWidget(new QLabel("Currency Code:"));
    entryLayout->addWidget(moneyUnitInput);
    entryLayout->addWidget(removeButton);

    expenseListLayout->addWidget(entryWidget);
    expenseEntries.append(entryWidget);
}

void ExpensesPage::removeExpenseEntry(QWidget *entry) {
    expenseListLayout->removeWidget(entry);
    expenseEntries.removeOne(entry);
    entry->deleteLater();
}