#include "eventroom.h"
#include "mainwindow.h"
#include "Page.h"

EventRoom::EventRoom(QGraphicsItem *parent) :Room(parent) {

    setPixmap(QPixmap(":/icons/images/EventMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void EventRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;
    Q_UNUSED(event);

    MainWindow::changeStack((int)Page::Event);
}
