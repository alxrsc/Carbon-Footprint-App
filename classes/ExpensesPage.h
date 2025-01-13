//
// Created by Alexandru Roșca on 14.01.2025.
//

#ifndef EXPENSESPAGE_H
#define EXPENSESPAGE_H

#include "CommonStyles.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QDebug>

class ExpensesPage : public QWidget {
Q_OBJECT

public:
    explicit ExpensesPage(QWidget *parent = nullptr);
    QPushButton *getBackButton() const { return backButton; }
    QPushButton *getNextButton() const { return nextButton; }

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *expenseListLayout;
    QScrollArea *scrollArea;
    QPushButton *addExpenseButton;
    QList<QWidget *> expenseEntries;
    QPushButton *backButton;
    QPushButton *nextButton;

    void setupUi();
    void addExpenseEntry();
    void removeExpenseEntry(QWidget *entry);
};

#endif // EXPENSESPAGE_H

