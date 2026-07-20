#ifndef ELITESCENE_H
#define ELITESCENE_H

#include "roomscene.h"
#include <QWidget>

class EliteScene : public RoomScene
{
    Q_OBJECT

public:
    explicit EliteScene(QWidget *parent = nullptr);
    ~EliteScene();

    void resetRoom() override;
};

#endif // ELITESCENE_H
