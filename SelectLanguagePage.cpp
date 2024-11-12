#include "SelectLanguagePage.h"

SelectLanguagePage::SelectLanguagePage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    englishButton = new QPushButton("English", this);
    romanianButton = new QPushButton("Romanian", this);
    spanishButton = new QPushButton("Spanish", this);


    layout->addWidget(englishButton);
    layout->addWidget(romanianButton);
    layout->addWidget(spanishButton);

    // Set the background color of buttons
    englishButton->setStyleSheet("QPushButton {"
                                 "font-size: 16px;"
                                 "font-weight: bold;"
                                 "color: lightgreen;"
                                 "background-color: gray;"
                                 "border-radius: 5px;"
                                 "padding: 10px;"
                                 "}");
    romanianButton->setStyleSheet("QPushButton {"
                                  "font-size: 16px;"
                                  "font-weight: bold;"
                                  "color: lightgreen;"
                                  "background-color: gray;"
                                  "border-radius: 5px;"
                                  "padding: 10px;"
                                  "}");
    spanishButton->setStyleSheet("QPushButton {"
                                 "font-size: 16px;"
                                 "font-weight: bold;"
                                 "color: lightgreen;"
                                 "background-color: gray;"
                                 "border-radius: 5px;"
                                 "padding: 10px;"
                                 "}");

    // Set the sizes of the buttons
    englishButton->setFixedSize(200, 50);
    romanianButton->setFixedSize(200, 50);
    spanishButton->setFixedSize(200, 50);

    // Set layout alignment for centering the buttons horizontally
    layout->setAlignment(Qt::AlignHCenter);

    setLayout(layout);

    // Set the window title and maximize the window
    setWindowTitle("Select Language");
    showMaximized();

    // Set background color for the entire widget
    setStyleSheet("background-color: lightgreen;");
}
