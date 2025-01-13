//
// Created by Alexandru Roșca on 13.01.2025.
//

#ifndef HOTELSTAYPAGE_H
#define HOTELSTAYPAGE_H

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

class HotelStayPage : public QWidget {
Q_OBJECT

public:
    explicit HotelStayPage(QWidget *parent = nullptr);
    QPushButton *getBackButton() const { return backButton; }
    QPushButton *getExpensesPageButton() const { return expensesPageButton; }

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *hotelStayListLayout;
    QScrollArea *scrollArea;
    QPushButton *addHotelStayButton;
    QList<QWidget *> hotelStayEntries;
    QPushButton *backButton;
    QPushButton *expensesPageButton;

    void setupUi();
    void addHotelStayEntry();
    void removeHotelStayEntry(QWidget *entry);
};

#endif // HOTELSTAYPAGE_H

