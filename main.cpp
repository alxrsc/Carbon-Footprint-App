#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QObject>

class MainPage : public QWidget {
    // Required for QObject-derived classes using signals/slots

public:
    QPushButton *helloButton;

    MainPage(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        helloButton = new QPushButton("Hello", this);
        layout->addWidget(helloButton);
        setLayout(layout);
        setWindowTitle("Main Page");
        resize(320, 240);
    }
};

class SelectLanguagePage : public QWidget {

public:
    QPushButton *englishButton;
    QPushButton *romanianButton;
    QPushButton *spanishButton;

    SelectLanguagePage(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        englishButton = new QPushButton("English", this);
        romanianButton = new QPushButton("Romanian", this);
        spanishButton = new QPushButton("Spanish", this);
        layout->addWidget(englishButton);
        layout->addWidget(romanianButton);
        layout->addWidget(spanishButton);
        setLayout(layout);
        setWindowTitle("Select Language");
        resize(320, 240);
    }
};

class MainController : public QObject {

public:
    MainPage mainPage;
    SelectLanguagePage languagePage;

    MainController() {
        // Connect buttons to handle navigation between pages
        QObject::connect(mainPage.helloButton, &QPushButton::clicked, this, &MainController::showLanguagePage);
        QObject::connect(languagePage.englishButton, &QPushButton::clicked, this, &MainController::backToMainPage);
        QObject::connect(languagePage.romanianButton, &QPushButton::clicked, this, &MainController::backToMainPage);
        QObject::connect(languagePage.spanishButton, &QPushButton::clicked, this, &MainController::backToMainPage);
    }

    void showMainPage() {
        languagePage.hide();
        mainPage.show();
    }

    void showLanguagePage() {
        mainPage.hide();
        languagePage.show();
    }

    void backToMainPage() {
        languagePage.hide();
        mainPage.show();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainController controller;
    controller.showMainPage();  // Start by showing the main page

    return app.exec();
}