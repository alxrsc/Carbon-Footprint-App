#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.resize(320, 240);
    window.setWindowTitle("Carbon Footprint App");
    window.show();
// Maria: a mers.
    return app.exec();
}
