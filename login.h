#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcheckbox.h>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void Show_Password(bool checked);
    void Show_Confirm(bool checked);
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
    QCheckBox *Password_CheckBox;
    QCheckBox *Confirm_CheckBox;
    bool checkPassword();

signals:
    void loginSuccess();

};

#endif // LOGIN_H
