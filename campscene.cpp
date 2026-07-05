#include "campscene.h"
#include "ui_campscene.h"

CampScene::CampScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CampScene)
{
    ui->setupUi(this);
}

CampScene::~CampScene()
{
    delete ui;
}
