#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QLabel>
#include <QGuiApplication>
#include <qscreen.h>
#include "player.h"
#include <QFont>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    QFont nameFont("Papyrus", 35, QFont::Bold);
    nameLabel = new QLabel(player::instance()->getName(), this);
    nameLabel->setGeometry(100, 80, 300, 50);
    nameLabel->setFont(nameFont);
    nameLabel->setStyleSheet("color: white;");

    buttonStyle =
        "QPushButton {"
        "   border: none;"
        "   background: transparent;"
        "   color: white;"
        "   font-size: 20px;"
        "   font-family: 'Segoe Print';"
        "}"
        "QPushButton:hover {"
        "   color: gold;"
        "}"
        "QPushButton:pressed {"
        "   color: darkgoldenrod;"
        "}";

    startButton = new QPushButton("Start", this);
    startButton->setGeometry(50, 180, 200, 25);
    startButton->setStyleSheet(buttonStyle);

    leaderBButton = new QPushButton("Leader Board", this);
    leaderBButton->setGeometry(50, 220, 200, 25);
    leaderBButton->setStyleSheet(buttonStyle);

    settingsButton = new QPushButton("Settings", this);
    settingsButton->setGeometry(50, 260, 200, 25);
    settingsButton->setStyleSheet(buttonStyle);

    exitButton = new QPushButton("Exit", this);
    exitButton->setGeometry(50, 300, 200, 25);
    exitButton->setStyleSheet(buttonStyle);
}

MainMenu::~MainMenu()
{
    delete ui;
}
