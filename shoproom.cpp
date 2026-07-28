#include "shoproom.h"
#include "mainwindow.h"
#include "Page.h"
#include "roomscene.h"
#include "map1.h"

ShopRoom::ShopRoom(int index, QGraphicsItem *parent) : Room(index, parent){

    setPixmap(QPixmap(":/icons/images/ShopMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void ShopRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    Map1::selectedIndex = this->index;
    QWidget *widget = MainWindow::m_stack->widget((int)Page::Shop);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Shop);
}
