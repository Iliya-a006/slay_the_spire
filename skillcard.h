#ifndef SKILLCARD_H
#define SKILLCARD_H

#include "card.h"

class SkillCard : public Card
{
public:
    explicit SkillCard(QGraphicsItem *parent = nullptr);
    SkillCard(const SkillCard& other);
    virtual ~SkillCard() = default;

    virtual int calculateBlock(const player* player) const;
    virtual void applyBlock(player* player, int block);
    QString getCardTypeFolder() const override;
};

#endif // SKILLCARD_H