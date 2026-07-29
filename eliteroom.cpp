#include "eliteroom.h"
#include "enemyscene.h"
#include "mainwindow.h"
#include "Page.h"
#include "roomscene.h"
#include "map1.h"

EliteRoom::EliteRoom(int index, QGraphicsItem *parent) : Room(index, parent){

    setPixmap(QPixmap(":/icons/images/EliteMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void EliteRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // if(!this->accessible)
    //     return;

    Map1::selectedIndex = this->index;
    QWidget *widget = MainWindow::m_stack->widget((int)Page::Enemy);
    EnemyScene *room = qobject_cast<EnemyScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Enemy);
}
