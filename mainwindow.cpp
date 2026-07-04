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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_statusBar = new QStatusBar(this);
    QGraphicsView *view = new QGraphicsView();
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

    m_stack->addWidget(mainmenu);
    m_stack->addWidget(start);
    m_stack->addWidget(leaderB);
    m_stack->addWidget(settings);
    m_stack->addWidget(mapAct1);

    backgrounds.push_back(":/prefix1/images/menupic.png");
    backgrounds.push_back(":/prefix1/images/menupic.png");
    backgrounds.push_back("");
    backgrounds.push_back("");
    backgrounds.push_back("");
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
