#include "settingspage.h"
#include <QPushButton>
#include <QStyle>

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
{
    QFont nameFont("Papyrus", 35, QFont::Bold);
    settingsLabel = new QLabel("Settings", this);
    settingsLabel->setGeometry(100, 80, 200, 50);
    settingsLabel->setFont(nameFont);
    settingsLabel->setStyleSheet("color: white;");

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

    nameButton = new QPushButton("Change User Name", this);
    nameButton->setGeometry(100, 180, 200, 25);
    nameButton->setStyleSheet(buttonStyle);

    passwordButton = new QPushButton("Change Password", this);
    passwordButton->setGeometry(100, 240, 200, 25);
    passwordButton->setStyleSheet(buttonStyle);

    backButton = new QPushButton("Back", this);
    backButton->setGeometry(100, 360, 200, 25);
    backButton->setStyleSheet(buttonStyle);



    soundLabel = new QLabel(this);
    soundLabel->setText("Sound");
    soundLabel->setGeometry(100, 300, 100, 25);
    soundLabel->setStyleSheet("QLabel {"
                              "   color: white;"
                              "   font-size: 20px;"
                              "   font-family: 'Segoe Print';"
                              "}");

    soundButton = new QPushButton(this);
    soundButton->setCheckable(true);
    soundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    soundButton->setGeometry(200, 300, 50, 25);
    soundButton->setStyleSheet(
        "QPushButton {"
        "   border: 2px solid #888;"
        "   border-radius: 15px;"
        "   background-color: #ccc;"
        "   padding: 6px;"
        "}"
        "QPushButton:checked {"
        "   background-color: #E53935;"
        "   border-color: #B71C1C;"
        "}"
        );
}

SettingsPage::~SettingsPage()
{

}
