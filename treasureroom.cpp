#include "treasureroom.h"

TreasureRoom::TreasureRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/ChestMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void TreasureRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}
