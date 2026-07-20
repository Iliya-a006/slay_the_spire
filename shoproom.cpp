#include "shoproom.h"
#include "mainwindow.h"
#include "Page.h"
#include "roomscene.h"

ShopRoom::ShopRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/ShopMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void ShopRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    QWidget *widget = MainWindow::m_stack->widget((int)Page::Shop);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Shop);
}
