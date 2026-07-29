#include "enemyroom.h"
#include "enemyscene.h"
#include "mainwindow.h"
#include "Page.h"
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
    EnemyScene *room = qobject_cast<EnemyScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Enemy);
}
