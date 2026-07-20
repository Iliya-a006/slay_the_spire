#include "mainmenu.h"
#include "Page.h"
#include "mainwindow.h"
#include "map1.h"
#include "ui_mainmenu.h"
#include <QLabel>
#include <QGuiApplication>
#include <qscreen.h>
#include "player.h"
#include <QFont>
#include <QCloseEvent>
#include <QToolButton>
#include <QEvent>
#include <QHoverEvent>
#include <QUrl>
#include <QTimer>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    player=new QMediaPlayer(this);
    output=new QAudioOutput(this);
    player->setAudioOutput(output);
    output->setVolume(0.5);
    player->setSource(QUrl("qrc:/soundtrack/Track/Menusoundtrsck.mp3"));

    connect(this, &MainMenu::muteRequested, this, &MainMenu::mute_track);

    QFont nameFont("Papyrus", 35, QFont::Bold);
    nameLabel = new QLabel(player::instance()->getName(), this);
    nameLabel->setGeometry(100, 80, 300, 50);
    nameLabel->setFont(nameFont);
    nameLabel->setStyleSheet("color: white;");

    buttonStyle =
        "QPushButton {"
        "   border: none;"
        "   background: transparent;"
        "   color: white;"
        "   font-size: 20px;"
        "   font-family: 'Segoe Print';"
        "}";

    startButton = new QPushButton("Start", this);
    startButton->setGeometry(50, 180, 200, 25);
    startButton->setStyleSheet(buttonStyle);
    startButton->setAttribute(Qt::WA_Hover,true);
    startButton->installEventFilter(this);

    leaderBButton = new QPushButton("Leader Board", this);
    leaderBButton->setGeometry(50, 220, 200, 25);
    leaderBButton->setStyleSheet(buttonStyle);
    leaderBButton->setAttribute(Qt::WA_Hover,true);
    leaderBButton->installEventFilter(this);

    settingsButton = new QPushButton("Settings", this);
    settingsButton->setGeometry(50, 260, 200, 25);
    settingsButton->setStyleSheet(buttonStyle);
    settingsButton->setAttribute(Qt::WA_Hover,true);
    settingsButton->installEventFilter(this);

    exitButton = new QPushButton("Exit", this);
    exitButton->setGeometry(50, 300, 200, 25);
    exitButton->setStyleSheet(buttonStyle);
    exitButton->setAttribute(Qt::WA_Hover,true);
    exitButton->installEventFilter(this);

    connect(startButton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack((int)Page::startMenu);
    });

    connect(leaderBButton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack((int)Page::leaderBoard);
    });

    connect(settingsButton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack((int)Page::settings);
    });
    connect(exitButton, &QPushButton::clicked, this, [](){
        player::saveFile();
        Map1::saveMap();
        QApplication::quit();
    });
}
static QTimer *hovertimer=nullptr;
static bool ishoverplay=false;
bool MainMenu::eventFilter(QObject *obj, QEvent *event){
    QPushButton *btn = nullptr;
    if (obj == startButton) btn = startButton;
    else if (obj == leaderBButton) btn = leaderBButton;
    else if (obj == settingsButton) btn = settingsButton;
    else if (obj == exitButton) btn = exitButton;
    else return QWidget::eventFilter(obj, event);
    if (event->type() == QEvent::HoverEnter) {
        btn->setStyleSheet(
            "QPushButton {"
            "   border: none;"
            "   background: transparent;"
            "   color: gold;"
            "   font-size: 20px;"
            "   font-family: 'Segoe Print';"
            "}"
            );
        if (ishoverplay==false) {
            ishoverplay = true;
            player->stop();
            player->setPosition(0);
            QTimer::singleShot(50,this,[=](){player->play();});
            if (!hovertimer) {
                hovertimer = new QTimer(this);
                hovertimer->setSingleShot(true);
                connect(hovertimer, &QTimer::timeout, this, [=]() {
                    player->stop();
                    ishoverplay = false;
                });
            }
            hovertimer->start(200);
        }
        return true;
    }
    else if (event->type() == QEvent::HoverLeave) {
        btn->setStyleSheet(
            "QPushButton {"
            "   border: none;"
            "   background: transparent;"
            "   color: white;"
            "   font-size: 20px;"
            "   font-family: 'Segoe Print';"
            "}"
            );
        return true;
    }

    return QWidget::eventFilter(obj, event);
}

void MainMenu::mute_track(){
    if(output->isMuted()==true)
        output->setMuted(false);
else
        output->setMuted(true);
}

MainMenu::~MainMenu()
{
    delete ui;
}
