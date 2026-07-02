#include "login.h"
#include "ui_login.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    QFont font;
    font.setPointSize(20);

    QFrame* frame = new QFrame(this);
    frame->setGeometry(450, 50, 400, 450);
    frame->setFrameShape(QFrame::Box);

    QLabel* nameLabel = new QLabel(this);
    nameLabel->setGeometry(500, 100, 300, 25);
    nameLabel->setFont(font);
    nameLabel->setText("Enter Your Username");

    QLineEdit* nameEdit = new QLineEdit(this);
    nameEdit->setGeometry(500, 130, 300, 25);
    nameEdit->setPlaceholderText(" username");

    QLabel* passwordLabel = new QLabel(this);
    passwordLabel->setGeometry(500, 220, 300, 25);
    passwordLabel->setFont(font);
    passwordLabel->setText("Enter Your Password");

    QLineEdit* passwordEdit = new QLineEdit(this);
    passwordEdit->setGeometry(500, 250, 300, 25);
    passwordEdit->setPlaceholderText(" password");

    QPushButton* signInButton = new QPushButton(this);
    signInButton->setGeometry(730, 460, 70, 25);
    signInButton->setText("Sign in");

    QPushButton* newButton = new QPushButton(this);
    newButton->setGeometry(500, 460, 100, 25);
    newButton->setText("New Account");
}

login::~login()
{
    delete ui;
}
