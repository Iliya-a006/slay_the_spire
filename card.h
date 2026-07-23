#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>
#include <QString>
#include <QObject>
#include <QVector>
#include <QPainter>
#include <QFont>
#include <QList>
#include <QPixmap>
#include <QPainterPath>
#include <QLabel>
#include <QCursor>
#include <QGraphicsTextItem>

enum Card_Type {
    ATTACK,
    SKILL,
    POWER,
    STATUS,
    CURSE
};

enum Card_Rarity {
    BASIC,
    COMMON,
    UNCOMMON,
    RARE,
    SPECIAL
};

class player;
class Enemy;

class Card : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    explicit Card(QGraphicsItem *parent = nullptr);
    Card(const Card& other);
    virtual ~Card() = default;

    QRectF boundingRect() const override;

    int GETER_ID() const { return ID; }
    QString GETER_NAME() const { return name; }
    int GETER_ENERGY_COST() const { return energy_cost; }
    int GETER_DAMAGE() const { return damage; }
    int GETER_BLOCK() const { return block; }
    Card_Rarity GETER_RARITY() const { return rarity; }
    Card_Type GETER_TYPE() const { return type; }
    QString GETER_DESCRIPTION() const { return description; }
    bool GETER_IS_UPGRADE() const { return is_Upgrade; }

    QString& GETER_SETER_DESCRIPTION() { return description; }
    bool& GETER_SETER_Exhaust() { return is_Exhaust; }
    bool& GETER_SETER_Ethereal() { return is_Ethereal; }
    bool& GETER_SETER_RETAIN() { return is_Retain; }
    bool& GETER_SETER_UPGRADE() { return is_Upgrade; }

    QString getDisplayName() const;
    QColor getNameColor() const;
    QString getTypeString() const;

    virtual int getCurrentCost(player* player) const;
    virtual bool canPlay(player* player) const;
    virtual void play(player* player, QList<Enemy*>& enemies) = 0;
    virtual Card* upgrade() = 0;
    virtual Card* clone() const = 0;

    void Set_Hovered(bool hovered);
    bool Is_Hovered() const { return hovered; }
    void Set_Playable(bool playable) { this->playable = playable; }
    bool Is_Playable() const { return playable; }
    void Set_Position(qreal x, qreal y) { setPos(x, y); }
    void Set_Original_Position(qreal x, qreal y) { originalPos = QPointF(x, y); }
    void Reset_Position() { setPos(originalPos); }

    virtual void Load_Card_Image(bool upgraded = false);

signals:
    void Card_Drag_Started(Card* card);
    void Card_Drag_Moved(Card* card);
    void Card_Dropped(Card* card);
    void Card_Dropped_On_Enemy(Card* card, Enemy* enemy);
    void Card_Dropped_On_Player(Card* card);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    QString getCardNameFormatted() const;
    QString getCardTypePath() const;
    QString getCardTypeFolder() const;
    QString getRarityString() const;
    QString getColorString() const;

    QGraphicsPixmapItem* m_background;
    QGraphicsPixmapItem* m_banner;
    QGraphicsPixmapItem* m_icon;
    QGraphicsPixmapItem* m_frame;
    QGraphicsPixmapItem* m_nameImage;

    // ===== متن‌های کارت =====
    QGraphicsTextItem* m_nameText;
    QGraphicsTextItem* m_typeText;
    QGraphicsTextItem* m_descriptionText;
    QGraphicsTextItem* m_energyText;
    QGraphicsTextItem* m_valueText;

    void loadBackground();
    void loadBanner();
    void loadIcon();
    void loadFrame();
    void loadNameImage();
    void loadTexts();

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

    bool hovered;
    bool playable;
    bool m_isDragged;

    QPointF originalPos;
    QPointF dragStartPos;

    static constexpr int CARD_WIDTH = 512;
    static constexpr int CARD_HEIGHT = 512;
};

#endif // CARD_H