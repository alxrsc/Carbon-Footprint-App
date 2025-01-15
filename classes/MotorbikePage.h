// MotorbikePage.h

#ifndef MOTORBIKEPAGE_H
#define MOTORBIKEPAGE_H

#include "CommonStyles.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QDebug>

class MotorbikePage : public QWidget {
    Q_OBJECT

public:
    explicit MotorbikePage(QWidget *parent = nullptr);
    QPushButton *getBackButton() const { return backButton; }
    QPushButton *getPublicTransportButton() const { return publicTransportButton; }

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *motorbikeListLayout;
    QScrollArea *scrollArea;
    QPushButton *addMotorbikeButton;
    QPushButton *calculateButton; // Button to trigger carbon footprint calculation
    QList<QWidget *> motorbikeEntries;
    QPushButton *backButton;
    QPushButton *publicTransportButton;
    QLabel *resultLabel; // For displaying the total carbon footprint

    void setupUi();
    void addMotorbikeEntry();
    void removeMotorbikeEntry(QWidget *entry);
    void calculateCarbonFootprint(); // Method to calculate and display carbon footprint
};

#endif //MOTORBIKEPAGE_H