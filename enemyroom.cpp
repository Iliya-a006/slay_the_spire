#include "enemyroom.h"
#include "enemyscene.h"
#include "mainwindow.h"
#include "Page.h"

EnemyRoom::EnemyRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/MonsterMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void EnemyRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    QWidget *widget = MainWindow::m_stack->widget((int)Page::Enemy);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Enemy);
}
