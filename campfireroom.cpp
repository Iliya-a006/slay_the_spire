#include "campfireroom.h"
#include "mainwindow.h"
#include "Page.h"

CampfireRoom::CampfireRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/RestMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void CampfireRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;
    Q_UNUSED(event);

    MainWindow::changeStack((int)Page::Campfire);
}
