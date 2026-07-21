#include "campfireroom.h"
#include "mainwindow.h"
#include "Page.h"
#include "roomscene.h"
#include "map1.h"

CampfireRoom::CampfireRoom(int index, QGraphicsItem *parent) : Room(index, parent){

    setPixmap(QPixmap(":/icons/images/RestMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void CampfireRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    Map1::selectedIndex = this->index;
    QWidget *widget = MainWindow::m_stack->widget((int)Page::Campfire);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Campfire);
}
