#include "eventroom.h"
#include "mainwindow.h"
#include "Page.h"
#include "roomscene.h"

EventRoom::EventRoom(QGraphicsItem *parent) :Room(parent) {

    setPixmap(QPixmap(":/icons/images/EventMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void EventRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    QWidget *widget = MainWindow::m_stack->widget((int)Page::Event);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Event);
}
