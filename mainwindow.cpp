#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Page.h"
#include "login.h"
#include "mainmenu.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsView *view = new QGraphicsView();
    setWindowTitle("Slay The Spire");

    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    login* loginPage = new login(this);
    MainMenu* mainmenu = new MainMenu(this);

    m_stack->addWidget(loginPage);
    m_stack->addWidget(mainmenu);

    m_stack->setCurrentIndex((int)Page::login);

    backgrounds.push_back(":/prefix1/images/loginpic.png");
    backgrounds.push_back(":/prefix1/images/menupic.png");
}

QStackedWidget* MainWindow::m_stack;

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap bg(backgrounds[m_stack->currentIndex()]);
    painter.drawPixmap(rect(), bg.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QWidget::paintEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}
