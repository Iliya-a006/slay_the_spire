#include "eventroom.h"

EventRoom::EventRoom(QGraphicsItem *parent) :Room(parent) {

    setPixmap(QPixmap(":/icons/images/EventMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void EventRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}
