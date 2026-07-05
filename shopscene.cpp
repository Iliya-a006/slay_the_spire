#include "shopscene.h"
#include "ui_shopscene.h"

ShopScene::ShopScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShopScene)
{
    ui->setupUi(this);
}

ShopScene::~ShopScene()
{
    delete ui;
}
