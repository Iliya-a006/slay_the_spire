#include "eliteroom.h"
#include "mainwindow.h"
#include "Page.h"
#include "roomscene.h"

EliteRoom::EliteRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/EliteMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void EliteRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    QWidget *widget = MainWindow::m_stack->widget((int)Page::Elite);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Elite);
}
