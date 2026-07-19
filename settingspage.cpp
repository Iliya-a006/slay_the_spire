#include "settingspage.h"
#include "Page.h"
#include "mainwindow.h"
#include "player.h"
#include <QVector>
#include <QPushButton>
#include <QStyle>
#include <qboxlayout.h>
#include "mainmenu.h"
#include <QMediaPlayer>
#include <QAudioOutput>
SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
{
    font.setPointSize(20);

    QFont titleFont("Papyrus", 35, QFont::Bold);
    settingsLabel = new QLabel("Settings", this);
    settingsLabel->setGeometry(100, 80, 200, 50);
    settingsLabel->setFont(titleFont);
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

    frame = new QFrame(this);
    frame->setFixedSize(450, 400);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch();
    hLayout->addWidget(frame);
    hLayout->addStretch();
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();
    frame->setFrameShape(QFrame::Box);
    frame->setStyleSheet("QFrame { border-image: url(:/prefix1/images/whitepic.png) 0 0 0 0 stretch stretch; }");
    frame->hide();

    nameLabel = new QLabel(frame);
    nameLabel->setGeometry(50, 50, 300, 25);
    nameLabel->setFont(font);
    nameLabel->setText("Enter New Username");
    nameEdit = new QLineEdit(frame);
    nameEdit->setGeometry(50, 80, 300, 25);
    nameEdit->setPlaceholderText(" username");
    nameLabel->hide();
    nameEdit->hide();

    passwordLabel = new QLabel(frame);
    passwordLabel->setGeometry(50, 50, 300, 25);
    passwordLabel->setFont(font);
    passwordLabel->setText("Enter New Password");
    passwordEdit = new QLineEdit(frame);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setGeometry(50, 80, 300, 25);
    passwordEdit->setPlaceholderText(" password");
    passwordEdit->hide();
    passwordLabel->hide();

    confirmLabel = new QLabel(frame);
    confirmLabel->setGeometry(50, 170, 300, 25);
    confirmLabel->setFont(font);
    confirmLabel->setText("Confirm Your Password");
    confirmEdit = new QLineEdit(frame);
    confirmEdit->setEchoMode(QLineEdit::Password);
    confirmEdit->setGeometry(50, 200, 300, 25);
    confirmEdit->setPlaceholderText(" password");
    confirmEdit->hide();
    confirmLabel->hide();


    saveButtton = new QPushButton(frame);
    saveButtton->setGeometry(280, 290, 70, 25);
    saveButtton->setText("Save");
    cancelButton = new QPushButton(frame);
    cancelButton->setGeometry(50, 290, 70, 25);
    cancelButton->setText("Cancel");

    connect(soundButton,&QPushButton::clicked,this,&SettingsPage::mute);

    connect(backButton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack((int)Page::MainMenu);
    });

    connect(nameButton, &QPushButton::clicked, this, [this](){
        changeName();
    });

    connect(passwordButton, &QPushButton::clicked, this, [this](){
        changePassword();
    });

    connect(saveButtton, &QPushButton::clicked, this, [this](){
        saving();
    });

    connect(cancelButton, &QPushButton::clicked, this, [this](){
        canceling();
    });
}

void SettingsPage::changeName()
{
    namePage = true;
    nameButton->hide();
    passwordButton->hide();
    soundLabel->hide();
    soundButton->hide();
    backButton->hide();

    frame->show();
    nameLabel->show();
    nameEdit->show();
    nameEdit->clear();
}
void SettingsPage::changePassword()
{
    namePage = false;
    nameButton->hide();
    passwordButton->hide();
    soundLabel->hide();
    soundButton->hide();
    backButton->hide();

    frame->show();
    passwordLabel->show();
    passwordEdit->show();
    confirmLabel->show();
    confirmEdit->show();
    passwordEdit->clear();
    confirmEdit->clear();
}

void SettingsPage::saving()
{
    player::instance()->setOldName(player::instance()->getName());
    player::instance()->setOldPassword(player::instance()->getPassword());
    if (namePage){
        QString newName = nameEdit->text();
        QVector<player> players = player::allPlayers();
        for (auto p : players)
            if (p.getName() == newName)
                return;
        player::instance()->setName(newName);
        player::instance()->saveFile();
        canceling();
    }
    else{
        QString newPassword = passwordEdit->text();
        QString newConfirm = confirmEdit->text();
        if(!newPassword.size())
            return;
        if (newPassword != newConfirm)
            return;
        else{
            player::instance()->setPassword(newPassword);
            player::instance()->saveFile();
            canceling();
        }
    }
}

void SettingsPage::canceling()
{
    nameLabel->hide();
    nameEdit->hide();
    passwordLabel->hide();
    passwordEdit->hide();
    confirmLabel->hide();
    confirmEdit->hide();
    frame->hide();

    nameButton->show();
    passwordButton->show();
    soundLabel->show();
    soundButton->show();
    backButton->show();
}
void SettingsPage::mute(){
    if (mainMenu) {
        emit mainMenu->muteRequested();
    }
}
void SettingsPage::setMainMenu(MainMenu *menu)
{
    mainMenu = menu;
}
SettingsPage::~SettingsPage()
{

}
