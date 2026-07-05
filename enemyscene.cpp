#include "enemyscene.h"
#include "ui_enemyscene.h"

EnemyScene::EnemyScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EnemyScene)
{
    ui->setupUi(this);
}

EnemyScene::~EnemyScene()
{
    delete ui;
}
