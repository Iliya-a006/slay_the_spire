#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Page.h"
#include "login.h"
#include "mainmenu.h"

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
}

QStackedWidget* MainWindow::m_stack;

MainWindow::~MainWindow()
{
    delete ui;
}
