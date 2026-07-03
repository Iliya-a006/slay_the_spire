#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QLabel>
#include <qpushbutton.h>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private:
    Ui::MainMenu *ui;

    QString buttonStyle;
    QLabel* nameLabel;
    QPushButton* startButton;
    QPushButton* leaderBButton;
    QPushButton* settingsButton;
    QPushButton* exitButton;
};

#endif // MAINMENU_H
