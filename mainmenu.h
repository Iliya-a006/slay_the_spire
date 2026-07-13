#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QLabel>
#include <qpushbutton.h>
#include <QMediaPlayer>
#include <QAudioOutput>
namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
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
    QMediaPlayer *player;
    QAudioOutput *output;
public:
    QPushButton* exitButton;
};

#endif // MAINMENU_H
