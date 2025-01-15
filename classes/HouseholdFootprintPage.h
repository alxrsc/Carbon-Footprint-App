#ifndef HOUSEHOLDFOOTPRINTPAGE_H
#define HOUSEHOLDFOOTPRINTPAGE_H

#include "CommonStyles.h"
#include "ExpensesPage.h"

#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class HouseholdFootprintPage : public QWidget {
    Q_OBJECT

public:
    explicit HouseholdFootprintPage(QWidget *parent = nullptr);

    QPushButton* getBackButton() const { return backButton; }
    QPushButton* getFlightsButton() const { return flightsButton; }


private:
    void setupUI();
    void calculateCarbonFootprint();

    // UI elements
    QLabel *headerLabel;
    QLabel *instructionLabel;
    QLabel *resultLabel;
    QFormLayout *formLayout;
    QPushButton *backButton;
    QPushButton *flightsButton;
    QPushButton *calculateButton;
    QLineEdit *electricityInput;
    QLineEdit *petrolInput;
    QLineEdit *naturalGasInput;
};

#endif // HOUSEHOLDFOOTPRINTPAGE_H
