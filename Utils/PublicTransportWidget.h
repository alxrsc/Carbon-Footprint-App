
#ifndef CARBONFOOTPRINTAPP_PUBLICTRANSPORTENTRYWIDGET_H
#define CARBONFOOTPRINTAPP_PUBLICTRANSPORTENTRYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>

class PublicTransportEntryWidget : public QWidget {
    Q_OBJECT

public:
    explicit PublicTransportEntryWidget(QWidget *parent = nullptr);

    // Public fields for accessing inputs
    QComboBox *transportTypeInput;
    QLineEdit *distanceInput;

    QString getTransportType() const;
    QString getDistance() const;

    signals:
        void removeRequested(PublicTransportEntryWidget *entry);

private:
    QPushButton *removeButton;
    void setupUi();
};

#endif //CARBONFOOTPRINTAPP_PUBLICTRANSPORTENTRYWIDGET_H