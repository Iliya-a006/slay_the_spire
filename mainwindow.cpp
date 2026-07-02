#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Page.h"
#include "login.h"

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

    m_stack->addWidget(loginPage);

    m_stack->setCurrentIndex((int)Page::login);
}

MainWindow::~MainWindow()
{
    delete ui;
}
