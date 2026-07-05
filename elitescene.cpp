#include "elitescene.h"
#include "ui_elitescene.h"

EliteScene::EliteScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EliteScene)
{
    ui->setupUi(this);
}

EliteScene::~EliteScene()
{
    delete ui;
}
