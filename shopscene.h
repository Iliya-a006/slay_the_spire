#ifndef SHOPSCENE_H
#define SHOPSCENE_H

#include "roomscene.h"
#include <QWidget>

class ShopScene : public RoomScene
{
    Q_OBJECT

public:
    explicit ShopScene(QWidget *parent = nullptr);
    ~ShopScene();

    void resetRoom() override;
};

#endif // SHOPSCENE_H
