#include "eliteroom.h"

EliteRoom::EliteRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/EliteMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void EliteRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}
