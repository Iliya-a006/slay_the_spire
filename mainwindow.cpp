#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Page.h"
#include "login.h"
#include "mainmenu.h"
#include <QPainter>
#include <QCloseEvent>
#include "player.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsView *view = new QGraphicsView();
    setWindowTitle("Slay The Spire");

    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    login* loginPage = new login(m_stack);
    m_stack->addWidget(loginPage);
    m_stack->setCurrentIndex((int)Page::login);
    backgrounds.push_back(":/prefix1/images/loginpic.png");

    connect(loginPage, &login::loginSuccess, this, &MainWindow::onLoginSuccess);
    //connect(this, &MainWindow::closeSignal, player::instance, player::saveFile);
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

    m_stack->addWidget(mainmenu);

    backgrounds.push_back(":/prefix1/images/menupic.png");
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

MainWindow::~MainWindow()
{
    delete ui;
}
