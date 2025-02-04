#include "HotelStayEntryWidget.h"
#include <QFormLayout>

HotelStayEntryWidget::HotelStayEntryWidget(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void HotelStayEntryWidget::setupUi() {
    QFormLayout *formLayout = new QFormLayout(this);

    // Country Code Input
    countryCodeInput = new QLineEdit(this);
    countryCodeInput->setPlaceholderText("Enter country code (e.g., US, UK)");
    formLayout->addRow("Country Code:", countryCodeInput);

    // // City Input
    // cityInput = new QLineEdit(this);
    // cityInput->setPlaceholderText("Enter city name (optional)");
    // formLayout->addRow("City (Optional):", cityInput);

    // Hotel Rating Dropdown
    ratingComboBox = new QComboBox(this);
    ratingComboBox->addItem("Select Rating");
    for (int i = 2; i <= 5; ++i) {
        ratingComboBox->addItem(QString::number(i) + " Stars");
    }
    formLayout->addRow("Rating:", ratingComboBox);

    // Nights Input
    nightsInput = new QLineEdit(this);
    nightsInput->setPlaceholderText("Enter number of nights");
    formLayout->addRow("Nights:", nightsInput);

    // Rooms Input
    roomsInput = new QLineEdit(this);
    roomsInput->setPlaceholderText("Enter number of rooms");
    formLayout->addRow("Rooms:", roomsInput);

    // Remove Button
    removeButton = new QPushButton("Remove", this);
    formLayout->addRow("", removeButton);

    connect(removeButton, &QPushButton::clicked, this, [this]() {
        emit removeRequested(this);
    });

    setLayout(formLayout);
}

QString HotelStayEntryWidget::getCountryCode() const {
    return countryCodeInput->text();
}

// QString HotelStayEntryWidget::getCity() const {
//     return cityInput->text();
// }

QString HotelStayEntryWidget::getHotelRating() const {
    return ratingComboBox->currentText();
}

QString HotelStayEntryWidget::getNights() const {
    return nightsInput->text();
}

QString HotelStayEntryWidget::getRooms() const {
    return roomsInput->text();
}
