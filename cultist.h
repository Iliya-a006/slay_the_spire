#ifndef CULTIST_H
#define CULTIST_H

#include "normalenemy.h"

class Cultist : public NormalEnemy
{
    Q_OBJECT

public:
    explicit Cultist(QGraphicsItem *parent = nullptr);
    Cultist(const Cultist& other);
    virtual ~Cultist() = default;

    Intent getNextIntent() override;
    void executeIntent(player& player) override;
    virtual QString getImagePath() const override { return m_imagePath; }

private:
    int turn = 0;
};

#endif // CULTIST_H