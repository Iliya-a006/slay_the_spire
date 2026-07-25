#ifndef DEMONFORM_H
#define DEMONFORM_H

#include "powercard.h"

class DemonForm : public PowerCard
{
public:
    explicit DemonForm(QGraphicsItem *parent = nullptr);
    DemonForm(const DemonForm& other);
    virtual ~DemonForm() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    void applyPower(player* player) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // DEMONFORM_H