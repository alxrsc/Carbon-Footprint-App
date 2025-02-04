// HotelStayEntryWidget.h
#ifndef HOTELSTAYENTRYWIDGET_H
#define HOTELSTAYENTRYWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

class HotelStayEntryWidget : public QWidget {
    Q_OBJECT

public:
    explicit HotelStayEntryWidget(QWidget *parent = nullptr);
    QString getCountryCode() const;
    QString getHotelRating() const;
    QString getNights() const;
    QString getRooms() const;

    signals:
        void removeRequested(HotelStayEntryWidget *entry);

public:
    QLineEdit *countryCodeInput;
    QComboBox *ratingComboBox;
    QLineEdit *nightsInput;
    QLineEdit *roomsInput;
    QPushButton *removeButton;

    void setupUi();
};

#endif // HOTELSTAYENTRYWIDGET_H