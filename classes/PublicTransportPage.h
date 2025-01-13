//
// Created by Alexandru Roșca on 13.01.2025.
//

#ifndef PUBLICTRANSPORTPAGE_H
#define PUBLICTRANSPORTPAGE_H

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
    QPushButton *getNextButton() const { return nextButton; }

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *transportListLayout;
    QScrollArea *scrollArea;
    QPushButton *addTransportButton;
    QList<QWidget *> transportEntries;
    QPushButton *backButton;
    QPushButton *nextButton;

    void setupUi();
    void addTransportEntry();
    void removeTransportEntry(QWidget *entry);
};

#endif // PUBLICTRANSPORTPAGE_H

