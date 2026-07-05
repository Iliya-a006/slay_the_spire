#include "eventscene.h"
#include "ui_eventscene.h"

EventScene::EventScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EventScene)
{
    ui->setupUi(this);
}

EventScene::~EventScene()
{
    delete ui;
}
