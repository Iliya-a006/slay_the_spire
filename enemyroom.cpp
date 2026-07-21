#include "enemyroom.h"
#include "mainwindow.h"
#include "Page.h"
#include "roomscene.h"
#include "map1.h"

EnemyRoom::EnemyRoom(int index, QGraphicsItem *parent) : Room(index, parent){

    setPixmap(QPixmap(":/icons/images/MonsterMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void EnemyRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    Map1::selectedIndex = this->index;
    QWidget *widget = MainWindow::m_stack->widget((int)Page::Enemy);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Enemy);
}
