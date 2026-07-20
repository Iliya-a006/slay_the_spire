#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class MainMenu;
class SettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();
    void mute();
    void setMainMenu(MainMenu *menu);
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

    MainMenu *mainMenu = nullptr;

    void changeName();
    void changePassword();
    bool namePage;
    void saving();
    void canceling();

};

#endif // SETTINGSPAGE_H
