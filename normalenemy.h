#ifndef NORMALENEMY_H
#define NORMALENEMY_H

#include "enemy.h"

class NormalEnemy : public Enemy
{
public:
    explicit NormalEnemy(const QString& name, int hp, QGraphicsItem *parent = nullptr);
    NormalEnemy(const NormalEnemy& other);
    virtual ~NormalEnemy() = default;

    virtual int getGoldReward() const;
    virtual bool hasPotionDrop() const;
    virtual QString getImagePath() const override { return m_imagePath; }
};

#endif // NORMALENEMY_H