#ifndef EVENTSCENE_H
#define EVENTSCENE_H

#include "roomscene.h"
#include <QWidget>

class EventScene : public RoomScene
{
    Q_OBJECT

public:
    explicit EventScene(QWidget *parent = nullptr);
    ~EventScene();

    void resetRoom() override;
};

#endif // EVENTSCENE_H
