//
// Created by Alexandru Roșca on 12.11.2024.
//

#include "MainPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MainPage::MainPage(QWidget *parent) : QWidget(parent) {
    // Create the button
    helloButton = new QPushButton("Hello", this);
    helloButton->setStyleSheet("QPushButton {"
                          "font-size: 16px;"
                          "font-weight: bold;"
                          "color: lightgreen;"
                          "background-color: gray;"
                          "border-radius: 5px;"
                          "padding: 10px;"
                          "}");
    helloButton->setFixedSize(300, 100);

    // Create horizontal and vertical layouts
    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout = new QHBoxLayout();

    // Add flexible space on either side of the button horizontally
    hLayout->addStretch();            // Adds space before the button
    hLayout->addWidget(helloButton);   // Adds the button to the layout
    hLayout->addStretch();             // Adds space after the button

    // Add flexible space above and below the button vertically
    vLayout->addStretch();             // Adds space above the button
    vLayout->addLayout(hLayout);       // Adds the horizontal layout (containing the button)
    vLayout->addStretch();             // Adds space below the button

    // Set the vertical layout as the main layout for the window
    setLayout(vLayout);

    // Additional window settings
    setWindowTitle("Main Page");
    showMaximized();
    setStyleSheet("background-color: lightgreen;");
}
