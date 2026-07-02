#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private:
    Ui::login *ui;

    bool m_signin=true;
    QFont font;
    QFrame* frame;
    QLabel* nameLabel;
    QLabel* passwordLabel;
    QLabel* confirmLabel;
    QLineEdit* nameEdit;
    QLineEdit* passwordEdit;
    QLineEdit* confirmEdit;
    QPushButton* signInButton;
    QPushButton* newButton;

    bool checkPassword();

};

#endif // LOGIN_H
