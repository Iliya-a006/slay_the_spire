#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include "player.h"
#include "mainwindow.h"
#include "Page.h"

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    font.setPointSize(20);

    frame = new QFrame(this);
    frame->setGeometry(450, 50, 400, 450);
    frame->setFrameShape(QFrame::Box);
    frame->setStyleSheet("QFrame { border-image: url(:/prefix1/images/whitepic.png) 0 0 0 0 stretch stretch; }");

    nameLabel = new QLabel(frame);
    nameLabel->setGeometry(50, 50, 300, 25);
    nameLabel->setFont(font);
    nameLabel->setText("Enter Your Username");

    nameEdit = new QLineEdit(frame);
    nameEdit->setGeometry(50, 80, 300, 25);
    nameEdit->setPlaceholderText(" username");

    passwordLabel = new QLabel(frame);
    passwordLabel->setGeometry(50, 170, 300, 25);
    passwordLabel->setFont(font);
    passwordLabel->setText("Enter Your Password");

    passwordEdit = new QLineEdit(frame);
    passwordEdit->setGeometry(50, 200, 300, 25);
    passwordEdit->setPlaceholderText(" password");

    signInButton = new QPushButton(frame);
    signInButton->setGeometry(280, 410, 70, 25);
    signInButton->setText("Sign in");

    newButton = new QPushButton(frame);
    newButton->setGeometry(50, 410, 100, 25);
    newButton->setText("New Account");

    confirmLabel = new QLabel(frame);
    confirmLabel->setGeometry(50, 290, 300, 25);
    confirmLabel->setFont(font);
    confirmLabel->setText("Confirm Your Password");
    confirmLabel->hide();

    confirmEdit = new QLineEdit(frame);
    confirmEdit->setGeometry(50, 320, 300, 25);
    confirmEdit->setPlaceholderText(" password");
    confirmEdit->hide();

    connect(newButton, &QPushButton::clicked, this, [this](){
        if (m_signin){
            m_signin = false;
            confirmLabel->show();
            confirmEdit->show();
            signInButton->setText("Sign up");
            newButton->setText("Sign in");
        }
        else{
            m_signin = true;
            confirmLabel->hide();
            confirmEdit->hide();
            signInButton->setText("Sign in");
            newButton->setText("New Account");
        }
    });

    connect(signInButton, &QPushButton::clicked, this, [this](){
        if (m_signin){
            if (player::findPlayer(nameEdit->text(), passwordEdit->text())){
                MainWindow::m_stack->setCurrentIndex((int)Page::MainMenu);
                update();
            }
        }
        else if (checkPassword() && nameEdit->text().length()){
            if (player::appendPlayer(nameEdit->text(), passwordEdit->text())){
                MainWindow::m_stack->setCurrentIndex((int)Page::MainMenu);
                update();
            }
        }
    });
}

bool login::checkPassword(){
    if (passwordEdit->text() == confirmEdit->text())
        return true;
    else{
        qDebug() << "passwords do not match";
        return false;
    }
}


login::~login()
{
    delete ui;
}
