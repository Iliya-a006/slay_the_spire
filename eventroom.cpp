#include "eventroom.h"
#include "mainwindow.h"
#include "Page.h"
#include "roomscene.h"
#include "map1.h"

EventRoom::EventRoom(int index, QGraphicsItem *parent) :Room(index, parent) {

    setPixmap(QPixmap(":/icons/images/EventMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void EventRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    Map1::selectedIndex = this->index;
    QWidget *widget = MainWindow::m_stack->widget((int)Page::Event);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Event);
}
