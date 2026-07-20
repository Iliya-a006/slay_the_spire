#include "card.h"
#include "player.h"
#include "enemy.h"
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

Card::Card(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
    ID(-1),
    name(""),
    description(""),
    energy_cost(0),
    damage(0),
    block(0),
    type(ATTACK),
    rarity(BASIC),
    is_Exhaust(false),
    is_Ethereal(false),
    is_Retain(false),
    is_Upgrade(false),
    hovered(false),
    playable(false),
    m_isDragged(false),
    originalPos(0, 0),
    dragStartPos(0, 0)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setScale(0.8);
}

Card::Card(const Card& other)
    : QGraphicsPixmapItem(other.parentItem()),
    ID(other.ID),
    name(other.name),
    description(other.description),
    energy_cost(other.energy_cost),
    damage(other.damage),
    block(other.block),
    type(other.type),
    rarity(other.rarity),
    is_Exhaust(other.is_Exhaust),
    is_Ethereal(other.is_Ethereal),
    is_Retain(other.is_Retain),
    is_Upgrade(other.is_Upgrade),
    hovered(false),
    playable(false),
    m_isDragged(false),
    originalPos(other.originalPos),
    dragStartPos(0, 0)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setScale(0.8);
    setPixmap(other.pixmap());
}

int Card::getCurrentCost(player* player) const {
    Q_UNUSED(player);
    return energy_cost;
}

bool Card::canPlay(player* player) const {
    if (type == STATUS || type == CURSE) return false;
    if (!player) return false;

    int cost = getCurrentCost(player);
    return player->GETER_SETER_ENERGY() >= cost;
}

void Card::Set_Hovered(bool hovered) {
    this->hovered = hovered;
    if (hovered) {
        setScale(0.9);
        setZValue(10);
        setPos(x(), y() - 20);
    } else {
        setScale(0.8);
        setZValue(0);
        setPos(originalPos);
    }
}

QString Card::getCardNameFormatted() const {
    QString formatted = name;
    formatted.remove(" ");
    return formatted;
}

QString Card::getCardTypePath() const {
    switch (type) {
    case ATTACK: return "attack";
    case SKILL:  return "skill";
    case POWER:  return "power";
    case STATUS: return "status";
    case CURSE:  return "curse";
    default:     return "attack";
    }
}

QString Card::getCardTypeFolder() const {
    switch (type) {
    case ATTACK: return "ATTACK_CARDS";
    case SKILL:  return "SKILL_CARDS";
    case POWER:  return "POWER_CARDS";
    case STATUS: return "STATUS_CARDS";
    case CURSE:  return "CURSE_CARDS";
    default:     return "ATTACK_CARDS";
    }
}

QString Card::getCardImagePath() const {
    QString cardName = getCardNameFormatted();
    QString typePath = getCardTypePath();
    QString typeFolder = getCardTypeFolder();

    return QString(":/%1/%2/%3.jpg").arg(typePath).arg(typeFolder).arg(cardName);
}

QString Card::getDisplayName() const {
    if (is_Upgrade) {
        return name + "+";
    }
    return name;
}

QColor Card::getNameColor() const {
    if (is_Upgrade) {
        return QColor(0, 255, 100);
    }
    return Qt::white;
}

void Card::Load_Card_Image(bool upgraded) {
    if (upgraded) {
        is_Upgrade = true;
    }

    QString path = getCardImagePath();
    QPixmap pixmap(path);

    if (!pixmap.isNull()) {
        setPixmap(pixmap);
        setScale(0.8);
    } else {
        QPixmap fallback(CARD_WIDTH, CARD_HEIGHT);
        fallback.fill(QColor(60, 60, 60));

        QPainter painter(&fallback);
        painter.setRenderHint(QPainter::Antialiasing);

        QColor borderColor;
        if (is_Upgrade) {
            borderColor = QColor(255, 215, 0);
        } else {
            switch (type) {
            case ATTACK: borderColor = QColor(200, 50, 50); break;
            case SKILL:  borderColor = QColor(50, 150, 200); break;
            case POWER:  borderColor = QColor(200, 150, 50); break;
            case STATUS: borderColor = QColor(100, 100, 100); break;
            case CURSE:  borderColor = QColor(150, 50, 150); break;
            default:     borderColor = QColor(100, 100, 100); break;
            }
        }

        painter.setPen(QPen(borderColor, 3));
        painter.setBrush(QColor(40, 40, 40));
        painter.drawRoundedRect(3, 3, CARD_WIDTH - 6, CARD_HEIGHT - 6, 8, 8);

        painter.setPen(getNameColor());
        QFont font("Vazirmatn", 10, QFont::Bold);
        painter.setFont(font);
        painter.drawText(QRect(0, 10, CARD_WIDTH, 30), Qt::AlignCenter, getDisplayName());

        painter.setPen(Qt::white);
        painter.setBrush(QColor(50, 50, 200));
        painter.drawEllipse(15, 50, 25, 25);
        painter.setPen(Qt::white);
        painter.drawText(QRect(15, 45, 25, 25), Qt::AlignCenter, QString::number(energy_cost));

        if (damage > 0) {
            painter.setPen(Qt::white);
            painter.setBrush(QColor(200, 50, 50));
            painter.drawEllipse(CARD_WIDTH - 40, 50, 25, 25);
            painter.setPen(Qt::white);
            painter.drawText(QRect(CARD_WIDTH - 40, 45, 25, 25), Qt::AlignCenter, QString::number(damage));
        } else if (block > 0) {
            painter.setPen(Qt::white);
            painter.setBrush(QColor(50, 150, 200));
            painter.drawEllipse(CARD_WIDTH - 40, 50, 25, 25);
            painter.setPen(Qt::white);
            painter.drawText(QRect(CARD_WIDTH - 40, 45, 25, 25), Qt::AlignCenter, QString::number(block));
        }

        painter.setPen(Qt::lightGray);
        QFont descFont("Vazirmatn", 7);
        painter.setFont(descFont);

        QStringList lines;
        QString currentLine;
        for (int i = 0; i < description.length(); ++i) {
            currentLine += description[i];
            if (currentLine.length() > 20 && description[i] == ' ') {
                lines.append(currentLine.trimmed());
                currentLine.clear();
            }
        }
        if (!currentLine.isEmpty()) {
            lines.append(currentLine.trimmed());
        }

        int yPos = CARD_HEIGHT - 20 * lines.size() - 10;
        for (const QString& line : lines) {
            painter.drawText(QRect(10, yPos, CARD_WIDTH - 20, 20), Qt::AlignCenter, line);
            yPos += 20;
        }

        if (is_Upgrade) {
            painter.setPen(QColor(255, 215, 0));
            painter.setFont(QFont("Vazirmatn", 8, QFont::Bold));
            painter.drawText(QRect(0, CARD_HEIGHT - 20, CARD_WIDTH, 18), Qt::AlignCenter, "★ UPGRADED");
        }

        setPixmap(fallback);
        setScale(0.8);
    }
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        dragStartPos = event->pos();
        m_isDragged = true;
        setCursor(Qt::ClosedHandCursor);
        emit Card_Drag_Started(this);
        event->accept();
    }
    QGraphicsPixmapItem::mousePressEvent(event);
}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (m_isDragged) {
        setPos(mapToParent(event->pos() - dragStartPos));
        emit Card_Drag_Moved(this);
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    }
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton && m_isDragged) {
        m_isDragged = false;
        setCursor(Qt::ArrowCursor);

        QGraphicsItem* droppedOn = scene()->itemAt(event->scenePos(), QTransform());

        if (droppedOn) {
            Enemy* targetEnemy = dynamic_cast<Enemy*>(droppedOn);
            if (targetEnemy) {
                emit Card_Dropped_On_Enemy(this, targetEnemy);
                event->accept();
                QGraphicsPixmapItem::mouseReleaseEvent(event);
                return;
            }

            player* targetPlayer = dynamic_cast<player*>(droppedOn);
            if (targetPlayer) {
                emit Card_Dropped_On_Player(this);
                event->accept();
                QGraphicsPixmapItem::mouseReleaseEvent(event);
                return;
            }
        }

        emit Card_Dropped(this);
        Reset_Position();
        event->accept();
    }
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void Card::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    Set_Hovered(true);
    setCursor(Qt::OpenHandCursor);
    event->accept();
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    Set_Hovered(false);
    if (!m_isDragged) {
        setCursor(Qt::ArrowCursor);
    }
    event->accept();
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}