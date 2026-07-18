#include "treasureroom.h"
#include "mainwindow.h"
#include "Page.h"

TreasureRoom::TreasureRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/ChestMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void TreasureRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;
    Q_UNUSED(event);

    MainWindow::changeStack((int)Page::Treasure);
}
