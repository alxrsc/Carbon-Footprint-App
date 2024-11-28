//
// Created by Alexandru Roșca on 12.11.2024.
//

#ifndef HOUSEHOLDFOOTPRINTPAGE_H
#define HOUSEHOLDFOOTPRINTPAGE_H

#include <QWidget>

class QFormLayout;
class QPushButton;
class QLabel;
class QLineEdit;
class QComboBox;

class HouseholdFootprintPage : public QWidget {
Q_OBJECT

public:
    explicit HouseholdFootprintPage(QWidget *parent = nullptr);

private:
    void setupUi();
    void applyStyles();

    // UI elements
    QLabel *headerLabel;
    QLabel *instructionLabel;
    QFormLayout *formLayout;
    QLabel *peopleLabel;
    QComboBox *peopleComboBox;
    QPushButton *calculateButton;
    QLabel *resultsLabel;
    QPushButton *offsetButton;
    QPushButton *backButton;
    QPushButton *nextButton;
};

#endif // HOUSEHOLDFOOTPRINTPAGE_H
