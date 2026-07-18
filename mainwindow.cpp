#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Page.h"
#include "login.h"
#include "mainmenu.h"
#include <QPainter>
#include <QCloseEvent>
#include "player.h"
#include "settingspage.h"
#include "startmenu.h"
#include "leaderboard.h"
#include "statusbar.h"
#include "map1.h"
#include "enemyscene.h"
#include "elitescene.h"
#include "eventscene.h"
#include "treasurescene.h"
#include "campscene.h"
#include "shopscene.h"
#include "bossscene.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_statusBar = new QStatusBar(this);
    setWindowTitle("Slay The Spire");

    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    login* loginPage = new login(m_stack);
    m_stack->addWidget(loginPage);
    m_stack->setCurrentIndex((int)Page::login);
    backgrounds.push_back(":/prefix1/images/loginpic.png");

    connect(loginPage, &login::loginSuccess, this, &MainWindow::onLoginSuccess);
    connect(StatusBar::instance(), &StatusBar::statusSignal, this, &MainWindow::statusRecieve);
}

QStackedWidget* MainWindow::m_stack;
void MainWindow::changeStack(int page)
{
    MainWindow::m_stack->setCurrentIndex(page);
    m_stack->update();
}

void MainWindow::onLoginSuccess()
{
    MainMenu* mainmenu = new MainMenu(m_stack);
    startMenu* start = new startMenu(m_stack);
    leaderBoard* leaderB = new leaderBoard(m_stack);
    SettingsPage* settings = new SettingsPage(m_stack);
    Map1* mapAct1 = new Map1(m_stack);
    EnemyScene* enemySc = new EnemyScene(m_stack);
    EliteScene* eliteSc = new EliteScene(m_stack);
    EventScene* eventSc = new EventScene(m_stack);
    TreasureScene* treasureSc = new TreasureScene(m_stack);
    CampScene* campSc = new CampScene(m_stack);
    ShopScene* shopSc = new ShopScene(m_stack);
    BossScene * bossSc = new BossScene(m_stack);

    m_stack->addWidget(mainmenu);
    m_stack->addWidget(start);
    m_stack->addWidget(leaderB);
    m_stack->addWidget(settings);
    m_stack->addWidget(mapAct1);
    m_stack->addWidget(enemySc);
    m_stack->addWidget(eliteSc);
    m_stack->addWidget(eventSc);
    m_stack->addWidget(treasureSc);
    m_stack->addWidget(campSc);
    m_stack->addWidget(shopSc);
    m_stack->addWidget(bossSc);

    backgrounds.push_back(":/prefix1/images/menupic.png");
    backgrounds.push_back(":/prefix1/images/menupic.png");
    backgrounds.push_back(":/prefix1/images/menupic.png");
    backgrounds.push_back("");
    backgrounds.push_back(":/prefix1/images/blackpic.png");
    backgrounds.push_back(":/prefix1/images/fightpic.png");
    backgrounds.push_back(":/prefix1/images/fightpic.png");
    backgrounds.push_back("");
    backgrounds.push_back("");
    backgrounds.push_back("");
    backgrounds.push_back("");
    backgrounds.push_back(":/prefix1/images/fightpic.png");
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap bg(backgrounds[m_stack->currentIndex()]);
    painter.drawPixmap(rect(), bg.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QWidget::paintEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    player::saveFile();
    event->accept();
}

void MainWindow::statusRecieve(QString text, int mSeconds)
{
    m_statusBar->showMessage(text, mSeconds);
}

MainWindow::~MainWindow()
{
    delete ui;
}
