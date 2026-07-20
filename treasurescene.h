#ifndef TREASURESCENE_H
#define TREASURESCENE_H

#include "roomscene.h"
#include <QWidget>

class TreasureScene : public RoomScene
{
    Q_OBJECT

public:
    explicit TreasureScene(QWidget *parent = nullptr);
    ~TreasureScene();

    void resetRoom() override;
};

#endif // TREASURESCENE_H
