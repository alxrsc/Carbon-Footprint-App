//
// Created by Alexandru Roșca on 13.01.2025.
//

#ifndef MOTORBIKEPAGE_H
#define MOTORBIKEPAGE_H

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
    QList<QWidget *> motorbikeEntries;
    QPushButton *backButton;
    QPushButton *publicTransportButton;

    void setupUi();
    void addMotorbikeEntry();
    void removeMotorbikeEntry(QWidget *entry);
};

#endif //MOTORBIKEPAGE_H