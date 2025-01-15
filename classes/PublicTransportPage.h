// Created by Alexandru Roșca on 13.01.2025.

#ifndef PUBLICTRANSPORTPAGE_H
#define PUBLICTRANSPORTPAGE_H

#include "CommonStyles.h"
#include "../APICalls.h"
#include "ExpensesPage.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QDebug>

class PublicTransportPage : public QWidget {
    Q_OBJECT

    public:
    explicit PublicTransportPage(QWidget *parent = nullptr);
    QPushButton *getBackButton() const { return backButton; }
    QPushButton *getHotelStayButton() const { return hotelStayButton; }

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *transportListLayout;
    QScrollArea *scrollArea;
    QPushButton *addTransportButton;
    QPushButton *calculateButton; // Button to trigger carbon footprint calculation
    QLabel *resultLabel;         // Label to display the total carbon footprint
    QList<QWidget *> transportEntries;
    QPushButton *backButton;
    QPushButton *hotelStayButton;

    void setupUi();
    void addTransportEntry();
    void removeTransportEntry(QWidget *entry);
    void calculateCarbonFootprint(); // Method to calculate carbon footprint
};

#endif // PUBLICTRANSPORTPAGE_H
