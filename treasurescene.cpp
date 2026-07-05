#include "treasurescene.h"
#include "ui_treasurescene.h"

TreasureScene::TreasureScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TreasureScene)
{
    ui->setupUi(this);
}

TreasureScene::~TreasureScene()
{
    delete ui;
}
