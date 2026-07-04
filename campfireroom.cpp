#include "campfireroom.h"

CampfireRoom::CampfireRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/RestMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void CampfireRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}
