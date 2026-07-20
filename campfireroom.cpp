#include "campfireroom.h"
#include "mainwindow.h"
#include "Page.h"
#include "roomscene.h"

CampfireRoom::CampfireRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/RestMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void CampfireRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    QWidget *widget = MainWindow::m_stack->widget((int)Page::Campfire);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Campfire);
}
