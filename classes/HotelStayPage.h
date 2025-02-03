// HotelStayPage.h

#ifndef HOTELSTAYPAGE_H
#define HOTELSTAYPAGE_H

#include "CommonStyles.h"
#include "ExpensesPage.h"
#include "../APICalls.h"
#include "../Utils/HotelStayEntryWidget.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QDebug>
#include <QList>

struct HotelStayEntry {
    QLineEdit *countryCodeInput;
    QLineEdit *cityInput;
    QComboBox *ratingComboBox;
    QLineEdit *nightsInput;
    QLineEdit *roomsInput;
};

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
    QList<HotelStayEntryWidget *> hotelStayEntries;
    QList<HotelStayEntry> hotelStayInputs;
    QPushButton *backButton;
    QPushButton *expensesPageButton;
    QPushButton *calculateButton;
    QLabel *resultLabel; // For displaying the total carbon footprint

    void setupUi();
    void addHotelStayEntry();
    void removeHotelStayEntry(HotelStayEntryWidget *entry);
    void calculateCarbonFootprint();
};

#endif // HOTELSTAYPAGE_H
