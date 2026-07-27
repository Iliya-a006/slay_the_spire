#ifndef SHOPSCENE_H
#define SHOPSCENE_H

#include "barricade.h"
#include "berserk.h"
#include "bloodforblood.h"
#include "bludgeon.h"
#include "brutality.h"
#include "card.h"
#include "cardremoval.h"
#include "carnage.h"
#include "darkembrace.h"
#include "defend.h"
#include "demonform.h"
#include "dualwield.h"
#include "entrench.h"
#include "exhume.h"
#include "feed.h"
#include "feelnopain.h"
#include "hemokinesis.h"
#include "immolate.h"
#include "impervious.h"
#include "inflame.h"
#include "limitbreak.h"
#include "metallicize.h"
#include "offering.h"
#include "reaper.h"
#include "roomscene.h"
#include "shrugitoff.h"
#include "strike.h"
#include "truegrit.h"
#include "twinstrike.h"
#include "vendor.h"
#include "warcry.h"
#include "whirlwind.h"
#include <QWidget>

class ShopScene : public RoomScene
{
    Q_OBJECT

public:
    explicit ShopScene(QWidget *parent = nullptr);
    ~ShopScene();

    void resetRoom() override;

private:
    Vendor* vendor;
    bool clicked;
    QGraphicsScene* shopScene;
    QGraphicsView* shopView;
    QVector<Card*> availableCards;
    CardRemoval* removal;
    QVector<QGraphicsTextItem*> cardsCost;
    QGraphicsTextItem* removalText;
    QVector<QGraphicsPixmapItem*> cardsCoinItems;
    QGraphicsPixmapItem* removalCoinItem;
    QGraphicsPixmapItem* removeItem;

    void showItems();
    Card* pickRandomCard();
    int costCalculation(Card* card);

private slots:
    void onVendorClicked();
    void onCardClicked(Card* card);
    void onRemovalClicked();

public:
    static QVector<std::function<Card*()>> cardFactories;
};




#endif // SHOPSCENE_H
