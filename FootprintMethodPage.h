#ifndef FOOTPRINTMETHODPAGE_H
#define FOOTPRINTMETHODPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMap>

class FootprintMethodPage : public QWidget {
Q_OBJECT

public:
    explicit FootprintMethodPage(QWidget *parent = nullptr);
    virtual ~FootprintMethodPage() = default;

    void updateLanguage(const QString &language);

    // Public getter methods for accessing private buttons
    QPushButton* getBackButton() const { return backButton; }
    QPushButton* getHouseholdButton() const { return householdButton; }
    QPushButton* getPeopleButton() const { return peopleButton; }

signals:
    void peopleCountEntered(int count);  // Signal to send the number of people entered
    void householdButtonClicked();       // Signal to emit when household button is clicked

private slots:
    void showPeopleInputForm();                // Slot to display input form
    void submitPeopleCount();                  // Slot to handle submission of the people count
    void onHouseholdButtonClicked();           // Slot to handle household button click

private:
    void initializeTranslations();             // Initialize translations for each button text

    // Main buttons
    QPushButton *peopleButton;
    QPushButton *householdButton;
    QPushButton *backButton;

    // Input form elements
    QLabel *promptLabel;
    QLineEdit *inputField;
    QPushButton *submitButton;

    // Translation mapping
    QMap<QString, QMap<QString, QString>> translations;
};

#endif // FOOTPRINTMETHODPAGE_H
