#include <QApplication>
#include <QWidget>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QPushButton *button = new QPushButton("Hello World", &window);
    window.resize(320, 240);
    window.setWindowTitle("Carbon Footprint App");
//    button->setGeometry(100, 100, 120, 30);
    button->move(100, 100);
    // create a new internal window when the button is pressed with a back button to the main page
    QPushButton *backButton = new QPushButton("Back", &window);
    backButton->move(10,10);
    backButton->hide();

    QObject::connect(button, &QPushButton::clicked, [&]() {
        button->hide();
        backButton->show();
    });

    QObject::connect(backButton, &QPushButton::clicked, [&]() {
        button->show();
        backButton->hide();
    });




    window.show();

// Maria: a mers.
// Petrisor: https://www.youtube.com/watch?v=qf_8dyLdT5s
// Andu: https://www.instagram.com/daniel.cdi/
    return app.exec();
}
