#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>


class SettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();

private:
    QFont font;
    QString buttonStyle;
    QLabel* settingsLabel;
    QPushButton* nameButton;
    QPushButton* passwordButton;
    QLabel* soundLabel;
    QPushButton *soundButton;
    QPushButton* backButton;
    QFrame* frame;
    QLabel* nameLabel;
    QLabel* passwordLabel;
    QLabel* confirmLabel;
    QLineEdit* nameEdit;
    QLineEdit* passwordEdit;
    QLineEdit* confirmEdit;
    QPushButton* saveButtton;
    QPushButton* cancelButton;

    void changeName();
    void changePassword();
    bool namePage;
    void saving();
    void canceling();

};

#endif // SETTINGSPAGE_H
