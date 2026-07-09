#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <qstatusbar.h>
#include "player.h"
#include "mainwindow.h"
#include "Page.h"
#include "statusbar.h"

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    font.setPointSize(20);

    frame = new QFrame(this);
    frame->setGeometry(450, 30, 450, 520);
    frame->setFrameShape(QFrame::Box);
    frame->setStyleSheet("QFrame { border-image: url(:/prefix1/images/whitepic.png) 0 0 0 0 stretch stretch; }");

    nameLabel = new QLabel(frame);
    nameLabel->setGeometry(50, 50, 300, 25);
    nameLabel->setFont(font);
    nameLabel->setText("Enter Your Username");

    nameEdit = new QLineEdit(frame);
    nameEdit->setGeometry(50, 80, 300, 25);
    nameEdit->setPlaceholderText(" Please Enter Your Username");

    passwordLabel = new QLabel(frame);
    passwordLabel->setGeometry(50, 170, 300, 25);
    passwordLabel->setFont(font);
    passwordLabel->setText("Enter Your Password");

    passwordEdit = new QLineEdit(frame);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setGeometry(50, 200, 300, 25);
    passwordEdit->setPlaceholderText(" Please Enter Your Password");

    Password_CheckBox=new QCheckBox(frame);
    Password_CheckBox->setGeometry(50, 225, 200, 30);
    Password_CheckBox->setText("Show Password");
    Password_CheckBox->setStyleSheet("QCheckBox {font-size:16px;");
    Password_CheckBox->setToolTip("Show/Hide Password");

    Confirm_CheckBox=new QCheckBox(frame);
    Confirm_CheckBox->setGeometry(50, 345, 200, 30);
    Confirm_CheckBox->setText("Show Password");
    Confirm_CheckBox->setStyleSheet("QCheckBox {font-size:16px;");
    Confirm_CheckBox->setToolTip("Show/Hide Password");
    Confirm_CheckBox->hide();

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
    confirmEdit->setEchoMode(QLineEdit::Password);
    confirmEdit->setGeometry(50, 320, 300, 25);
    confirmEdit->setPlaceholderText(" password");
    confirmEdit->hide();

    connect(Confirm_CheckBox,&QCheckBox::toggled,this,&login::Show_Confirm);

    connect(Password_CheckBox,&QCheckBox::toggled,this,&login::Show_Password);

    connect(newButton, &QPushButton::clicked, this, [this](){
        if (m_signin){
            m_signin = false;
            confirmLabel->show();
            confirmEdit->show();
            Confirm_CheckBox->show();
            signInButton->setText("Sign up");
            newButton->setText("Sign in");
        }
        else{
            m_signin = true;
            confirmLabel->hide();
            confirmEdit->hide();
            Confirm_CheckBox->hide();
            signInButton->setText("Sign in");
            newButton->setText("New Account");
        }
    });

    connect(signInButton, &QPushButton::clicked, this, [this, &parent](){
        if (m_signin){
            if (player::findPlayer(nameEdit->text(), passwordEdit->text())){
                emit loginSuccess();
                MainWindow::changeStack((int)Page::MainMenu);
            }
            else{
                StatusBar::instance()->status("user not found", 3000);
            }
        }
        else if (checkPassword() && nameEdit->text().length()){
            if (player::appendPlayer(nameEdit->text(), passwordEdit->text())){
                emit loginSuccess();
                MainWindow::changeStack((int)Page::MainMenu);
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

void login::Show_Password(bool checked){
    if(checked){
        passwordEdit->setEchoMode(QLineEdit::Normal);
        Password_CheckBox->setText("Hide Password");
    }else{
        passwordEdit->setEchoMode(QLineEdit::Password);
        Password_CheckBox->setText("Show Password");
    }
}
void login::Show_Confirm(bool checked){
    if(checked){
        confirmEdit->setEchoMode(QLineEdit::Normal);
        Confirm_CheckBox->setText("Hide Password");
    }else{
        confirmEdit->setEchoMode(QLineEdit::Password);
        Confirm_CheckBox->setText("Show Password");
    }
}

login::~login()
{
    delete ui;
}
