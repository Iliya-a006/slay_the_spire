#include "bossroom.h"
#include "Page.h"
#include "mainwindow.h"
#include "roomscene.h"

BossRoom::BossRoom(QGraphicsItem *parent) : Room(parent) {

    setPixmap(QPixmap(":/icons/images/BossMapIcon2.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void BossRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;

    QWidget *widget = MainWindow::m_stack->widget((int)Page::Boss);
    RoomScene *room = qobject_cast<RoomScene*>(widget);
    if (room)
        room->resetRoom();
    MainWindow::changeStack((int)Page::Boss);
}
