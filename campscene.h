#ifndef CAMPSCENE_H
#define CAMPSCENE_H

#include "roomscene.h"
#include <QWidget>

class CampScene : public RoomScene
{
    Q_OBJECT

public:
    explicit CampScene(QWidget *parent = nullptr);
    ~CampScene();

    void resetRoom() override;
};

#endif // CAMPSCENE_H
