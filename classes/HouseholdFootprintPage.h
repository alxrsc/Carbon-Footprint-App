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
    // Public getter methods for accessing private buttons
    QPushButton* getBackButton() const { return backButton; }
    QPushButton* getFlightsButton() const { return flightsButton; }
private:
    void setupUI();
    void applyStyles();

    // UI elements
    QLabel *headerLabel;
    QLabel *instructionLabel;
    QFormLayout *formLayout;
    QPushButton *backButton;
    QPushButton *flightsButton;


};

#endif // HOUSEHOLDFOOTPRINTPAGE_H
