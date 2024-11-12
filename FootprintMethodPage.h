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
    QPushButton *peopleButton;
    QPushButton *householdButton;
    QPushButton *backButton;

    QLabel *promptLabel;         // Label for the prompt to enter number of people
    QLineEdit *inputField;       // Input field for the number of people
    QPushButton *submitButton;   // Submit button to confirm the number of people

    explicit FootprintMethodPage(QWidget *parent = nullptr);
    virtual ~FootprintMethodPage() = default;

    void updateLanguage(const QString &language);

signals:
    void peopleCountEntered(int count);  // Signal to send the number of people entered

private slots:
    void showPeopleInputForm();          // Slot to display input form
    void submitPeopleCount();            // Slot to handle submission of the people count

private:
    void initializeTranslations();       // Initialize translations for each button text
    QMap<QString, QMap<QString, QString>> translations;
};

#endif // FOOTPRINTMETHODPAGE_H
