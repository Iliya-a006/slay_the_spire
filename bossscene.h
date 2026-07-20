#ifndef BOSSSCENE_H
#define BOSSSCENE_H

#include "roomscene.h"
#include <QWidget>


class BossScene : public RoomScene
{
    Q_OBJECT

public:
    explicit BossScene(QWidget *parent = nullptr);
    ~BossScene();

    void resetRoom() override;
};

#endif // BOSSSCENE_H
