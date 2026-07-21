#include "treasureroom.h"
#include "mainwindow.h"
#include "Page.h"
#include "roomscene.h"
#include "map1.h"

TreasureRoom::TreasureRoom(int index, QGraphicsItem *parent) : Room(index, parent){

    setPixmap(QPixmap(":/icons/images/ChestMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void TreasureRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    Map1::selectedIndex = this->index;
    QWidget *widget = MainWindow::m_stack->widget((int)Page::Treasure);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Treasure);
}
