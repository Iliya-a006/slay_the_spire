#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QPainter>
#include <QFont>

enum Card_Type{
    ATTACK,
    SKILL,
    POWER,
    STATUS,
    CURSE
};

enum Card_Rarity{
    BASIC,
    COMMON,
    UNCOMMON,
    RARE,
    SPECIAL
};
class player;
class enemy;
class Card : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Card(QGraphicsItem *parent = nullptr);
    virtual ~Card()=default;

    int GETER_ID(){return ID;}
    QString GETER_NAME(){return name;}
    int GETER_ENERGY_COST(){return energy_cost;}
    int GETER_DAMAGE(){return damage;}
    int GETER_BLOCK(){return block;}
    Card_Rarity GETER_RARITY(){return rarity;}
    Card_Type GETER_TYPE(){return type;}
    QString& GETER_SETER_DESCRIPTION(){return description;}
    bool& GETER_SETER_Exhaust(){return is_Exhaust;}
    bool& GETER_SETER_Ethereal(){return is_Ethereal;}
    bool& GETER_SETER_RETAIN(){return is_Retain;}
    bool& GETER_SETER_UPGRADE(){return is_Upgrade;}

    virtual int getCurrentCost(const player* player) const;
    virtual bool canPlay(player* player) const;
    virtual void play(player* player, QList<enemy*>& enemies) = 0;
    virtual Card* upgrade() = 0;
    virtual Card* clone() const = 0;

    void Set_Hovered(bool hovered);
    bool Is_Hovered() const { return hovered; }
    void Set_Playable(bool playable) { playable = playable; }
    void Set_Position(qreal x, qreal y) { setPos(x, y); }
    void Load_Card_Image(bool upgraded = false);
signals:
    void Card_Drag_Started(Card* card);
    void Card_Drag_Moved(Card* card);
    void Card_Dropped(Card* card);
    void Card_Dropped_On_Enemy(Card* card, enemy* enemy);
    void Card_Dropped_On_Player(Card* card);
protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int ID;
    QString name;
    QString description;
    int energy_cost;
    int damage;
    int block;
    Card_Type type;
    Card_Rarity rarity;
    bool is_Exhaust;
    bool is_Ethereal;
    bool is_Retain;
    bool is_Upgrade;

    //show DISPLAYSTATUS of card
    bool hovered,playeable;
    bool m_isDragged;
    QPointF m_dragOffset;
};

#endif // CARD_H
