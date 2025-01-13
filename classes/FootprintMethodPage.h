#ifndef FOOTPRINTMETHODPAGE_H
#define FOOTPRINTMETHODPAGE_H

#include "CommonStyles.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>

class FootprintMethodPage : public QWidget {
Q_OBJECT

public:
    explicit FootprintMethodPage(QWidget *parent = nullptr);

    QPushButton* getBackButton() const { return backButton; }
    QPushButton* getHouseholdButton() const { return householdButton; }

signals:
    void peopleCountEntered(int count);
    void householdButtonClicked();

private:
    void setupUI();
    void connectUI();

    QPushButton *peopleButton;
    QPushButton *householdButton;
    QPushButton *backButton;
    QPushButton *submitButton;

    QLabel *promptLabel;
    QLineEdit *inputField;

    QFormLayout *formLayout;    // Layout for form inputs
    QWidget *formContainer;     // Container for form layout

    void showPeopleInputForm();
    void submitPeopleCount();
    void onHouseholdButtonClicked();
};

#endif // FOOTPRINTMETHODPAGE_H
