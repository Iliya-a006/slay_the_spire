#include "startmenu.h"
#include <QGuiApplication>
#include <qscreen.h>

startMenu::startMenu(QWidget *parent)
    : QWidget(parent)
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    QString buttonStyle = R"(
    QPushButton {
        background-color: rgba(40, 20, 15, 180);
        border: 2px solid #c97a3d;
        border-radius: 8px;
        color: #f0d78c;
        font-size: 18px;
        font-weight: bold;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: rgba(201, 122, 61, 220);
        color: white;
    }
    QPushButton:pressed {
        background-color: rgba(150, 90, 40, 255);
    }
    )";

    singleButton = new QPushButton("Single Player", this);
    singleButton->setGeometry(screenWidth/2 - 250, screenHeight/2 - 40, 200, 80);
    singleButton->setStyleSheet(buttonStyle);

    multiButton = new QPushButton("Multi Player", this);
    multiButton->setGeometry(screenWidth/2 + 50, screenHeight/2 - 40, 200, 80);
    multiButton->setStyleSheet(buttonStyle);

    backButton = new QPushButton("Back", this);
    backButton->setGeometry(screenWidth/2 - 40, screenHeight/2 + 70, 80, 40);
    backButton->setStyleSheet(buttonStyle);

}

startMenu::~startMenu()
{

}
