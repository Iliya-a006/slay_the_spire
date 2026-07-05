#include "bossscene.h"
#include "ui_bossscene.h"

BossScene::BossScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BossScene)
{
    ui->setupUi(this);
}

BossScene::~BossScene()
{
    delete ui;
}
