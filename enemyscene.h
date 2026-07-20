#ifndef ENEMYSCENE_H
#define ENEMYSCENE_H

#include <QWidget>
#include "roomscene.h"


class EnemyScene : public RoomScene
{
    Q_OBJECT

public:
    explicit EnemyScene(QWidget *parent = nullptr);
    ~EnemyScene();

    void resetRoom() override;
};

#endif // ENEMYSCENE_H
