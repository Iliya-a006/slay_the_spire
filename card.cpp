#include "card.h"
#include "player.h"
#include "enemy.h"
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>

Card::Card(QGraphicsItem *parent)
    : QGraphicsItemGroup(parent),
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
    dragStartPos(0, 0),
    m_background(nullptr),
    m_banner(nullptr),
    m_icon(nullptr),
    m_frame(nullptr),
    m_nameImage(nullptr),
    m_nameText(nullptr),
    m_typeText(nullptr),
    m_descriptionText(nullptr),
    m_energyText(nullptr),
    m_valueText(nullptr)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setScale(0.5);
}

Card::Card(const Card& other)
    : QGraphicsItemGroup(other.parentItem()),
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
    dragStartPos(0, 0),
    m_background(nullptr),
    m_banner(nullptr),
    m_icon(nullptr),
    m_frame(nullptr),
    m_nameImage(nullptr),
    m_nameText(nullptr),
    m_typeText(nullptr),
    m_descriptionText(nullptr),
    m_energyText(nullptr),
    m_valueText(nullptr)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setScale(0.5);
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
        setZValue(10);
        setPos(x(), y() - 20);
    } else {
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

QString Card::getRarityString() const {
    switch (rarity) {
    case BASIC:   return "basic";
    case COMMON:  return "common";
    case UNCOMMON:return "uncommon";
    case RARE:    return "rare";
    case SPECIAL: return "special";
    default:      return "common";
    }
}

QString Card::getColorString() const {
    switch (type) {
    case ATTACK: return "red";
    case SKILL:  return "blue";
    case POWER:  return "gold";
    case STATUS: return "gray";
    case CURSE:  return "purple";
    default:     return "red";
    }
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

QString Card::getTypeString() const {
    switch (type) {
    case ATTACK: return "Attack";
    case SKILL:  return "Skill";
    case POWER:  return "Power";
    case STATUS: return "Status";
    case CURSE:  return "Curse";
    default:     return "Unknown";
    }
}

void Card::loadBackground()
{
    if (m_background) {
        removeFromGroup(m_background);
        delete m_background;
        m_background = nullptr;
    }

    QString cardName = getCardNameFormatted();
    QString typeFolder = getCardTypeFolder();
    QString typePath = getCardTypePath();
    QString color = getColorString();

    QString bgPath = QString(":/form/%1/form/512_bg_%2_%3.png")
                         .arg(typeFolder)
                         .arg(typePath)
                         .arg(color);

    QPixmap pixmap(bgPath);
    if (!pixmap.isNull()) {
        m_background = new QGraphicsPixmapItem(pixmap, this);
        m_background->setPos(0, 0);
        addToGroup(m_background);
    }
}

void Card::loadBanner()
{
    if (m_banner) {
        removeFromGroup(m_banner);
        delete m_banner;
        m_banner = nullptr;
    }

    QString cardName = getCardNameFormatted();
    QString typeFolder = getCardTypeFolder();
    QString rarityStr = getRarityString();

    QString bannerPath = QString(":/form/%1/form/512_banner_%2.png")
                             .arg(typeFolder)
                             .arg(rarityStr);

    QPixmap pixmap(bannerPath);
    if (!pixmap.isNull()) {
        m_banner = new QGraphicsPixmapItem(pixmap, this);
        m_banner->setPos(0, 0);
        addToGroup(m_banner);
    }
}

void Card::loadIcon()
{
    if (m_icon) {
        removeFromGroup(m_icon);
        delete m_icon;
        m_icon = nullptr;
    }

    QString cardName = getCardNameFormatted();
    QString typeFolder = getCardTypeFolder();
    QString color = getColorString();

    QString iconPath = QString(":/form/%1/form/512_card_%2_orb.png")
                           .arg(typeFolder)
                           .arg(color);

    QPixmap pixmap(iconPath);
    if (!pixmap.isNull()) {
        QPixmap scaledPixmap = pixmap.scaled(pixmap.width() * 1.3, pixmap.height() * 1.3, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_icon = new QGraphicsPixmapItem(scaledPixmap, this);
        m_icon->setPos(25, 10);
        addToGroup(m_icon);
    }
}

void Card::loadFrame()
{
    if (m_frame) {
        removeFromGroup(m_frame);
        delete m_frame;
        m_frame = nullptr;
    }

    QString cardName = getCardNameFormatted();
    QString typeFolder = getCardTypeFolder();
    QString typePath = getCardTypePath();
    QString rarityStr = getRarityString();

    QString framePath = QString(":/form/%1/form/512_frame_%2_%3.png")
                            .arg(typeFolder)
                            .arg(typePath)
                            .arg(rarityStr);

    QPixmap pixmap(framePath);
    if (!pixmap.isNull()) {
        m_frame = new QGraphicsPixmapItem(pixmap, this);
        m_frame->setPos(0, 0);
        addToGroup(m_frame);
    }
}

void Card::loadNameImage()
{
    if (m_nameImage) {
        removeFromGroup(m_nameImage);
        delete m_nameImage;
        m_nameImage = nullptr;
    }

    QString cardName = getCardNameFormatted();
    QString typeFolder = getCardTypeFolder();

    QString namePath = QString(":/attackcard/%1/%2/%3.png")
                           .arg(typeFolder)
                           .arg(cardName)
                           .arg(cardName.toLower());

    QPixmap pixmap(namePath);
    if (!pixmap.isNull()) {
        m_nameImage = new QGraphicsPixmapItem(pixmap, this);
        int x = (CARD_WIDTH - pixmap.width()) / 2;
        int y = (CARD_HEIGHT - pixmap.height()) / 2 - 80;
        m_nameImage->setPos(x, y);
        addToGroup(m_nameImage);
    }
}

void Card::loadTexts()
{
    if (m_nameText) { removeFromGroup(m_nameText); delete m_nameText; m_nameText = nullptr; }
    if (m_typeText) { removeFromGroup(m_typeText); delete m_typeText; m_typeText = nullptr; }
    // if (m_descriptionText) { removeFromGroup(m_descriptionText); delete m_descriptionText; m_descriptionText = nullptr; }
    if (m_energyText) { removeFromGroup(m_energyText); delete m_energyText; m_energyText = nullptr; }
    if (m_valueText) { removeFromGroup(m_valueText); delete m_valueText; m_valueText = nullptr; }

    QFont nameFont("Vazirmatn", 20, QFont::Bold);
    QFont typeFont("Vazirmatn", 11, QFont::Bold);  // Bold اضافه شد
    QFont descFont("Vazirmatn", 14);
    QFont valueFont("Vazirmatn", 18, QFont::Bold);

    // ===== اسم کارت (وسط نسبت به banner) =====
    QFontMetrics fm(nameFont);
    int nameWidth = fm.horizontalAdvance(getDisplayName());
    int nameX = (CARD_WIDTH - nameWidth) / 2;
    m_nameText = new QGraphicsTextItem(getDisplayName(), this);
    m_nameText->setFont(nameFont);
    m_nameText->setDefaultTextColor(getNameColor());
    m_nameText->setPos(nameX, 55);
    addToGroup(m_nameText);

    // ===== نوع کارت (دقیقا وسط Background) =====
    QFontMetrics fmType(typeFont);
    int typeWidth = fmType.horizontalAdvance(getTypeString());
    int typeX = (CARD_WIDTH - typeWidth) / 2;
    int typeY = (CARD_HEIGHT - fmType.height()) / 2 +17;  // وسط کارت
    m_typeText = new QGraphicsTextItem(getTypeString(), this);
    m_typeText->setFont(typeFont);
    m_typeText->setDefaultTextColor(Qt::black);  // طلایی
    m_typeText->setPos(typeX, typeY);
    addToGroup(m_typeText);

    // ===== توضیحات (پایین کارت، وسط) =====
    // QStringList words = description.split(" ");
    // QStringList lines;
    // QString currentLine;
    // int maxCharsPerLine = 14;

    // for (const QString& word : words) {
    //     if (currentLine.isEmpty()) {
    //         currentLine = word;
    //     } else if (currentLine.length() + word.length() + 1 <= maxCharsPerLine) {
    //         currentLine += " " + word;
    //     } else {
    //         lines.append(currentLine);
    //         currentLine = word;
    //     }
    // }
    // if (!currentLine.isEmpty()) {
    //     lines.append(currentLine);
    // }

    // QString formattedDesc = lines.join("\n");

    // QFontMetrics fmDesc(descFont);
    // int descWidth = fmDesc.horizontalAdvance(formattedDesc);
    // int descX = (CARD_WIDTH - descWidth) / 2 + 30;  // +30 به راست
    // if (descX < 0) descX = 10;
    // int descY = typeY + fmType.height() + 20;
    // m_descriptionText = new QGraphicsTextItem(formattedDesc, this);
    // m_descriptionText->setFont(descFont);
    // m_descriptionText->setDefaultTextColor(Qt::white);
    // m_descriptionText->setPos(descX, descY);
    // addToGroup(m_descriptionText);

    // // ===== هزینه انرژی (روی icon - گوشه بالا چپ) =====
    m_energyText = new QGraphicsTextItem(QString::number(energy_cost), this);
    m_energyText->setFont(valueFont);
    m_energyText->setDefaultTextColor(Qt::black);
    m_energyText->setPos(120, 48);
    addToGroup(m_energyText);

    // ===== damage/block (گوشه بالا راست) =====
    // if (damage > 0) {
    //     m_valueText = new QGraphicsTextItem(QString::number(damage), this);
    //     m_valueText->setFont(valueFont);
    //     m_valueText->setDefaultTextColor(Qt::white);
    //     m_valueText->setPos(CARD_WIDTH - 75, 70);
    //     addToGroup(m_valueText);
    // } else if (block > 0) {
    //     m_valueText = new QGraphicsTextItem(QString::number(block), this);
    //     m_valueText->setFont(valueFont);
    //     m_valueText->setDefaultTextColor(Qt::white);
    //     m_valueText->setPos(CARD_WIDTH - 75, 70);
    //     addToGroup(m_valueText);
    // }
}

void Card::Load_Card_Image(bool upgraded) {
    if (upgraded) {
        is_Upgrade = true;
    }

    if (m_background) { removeFromGroup(m_background); delete m_background; m_background = nullptr; }
    if (m_banner) { removeFromGroup(m_banner); delete m_banner; m_banner = nullptr; }
    if (m_icon) { removeFromGroup(m_icon); delete m_icon; m_icon = nullptr; }
    if (m_frame) { removeFromGroup(m_frame); delete m_frame; m_frame = nullptr; }
    if (m_nameImage) { removeFromGroup(m_nameImage); delete m_nameImage; m_nameImage = nullptr; }

    loadBackground();
    loadNameImage();
    loadFrame();
    loadBanner();
    loadIcon();
    loadTexts();

    if (!m_background && !m_banner && !m_frame && !m_icon && !m_nameImage) {
        return;
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
    QGraphicsItemGroup::mousePressEvent(event);
}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (m_isDragged) {
        setPos(mapToParent(event->pos() - dragStartPos));
        emit Card_Drag_Moved(this);
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    }
    QGraphicsItemGroup::mouseMoveEvent(event);
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
                QGraphicsItemGroup::mouseReleaseEvent(event);
                return;
            }

            player* targetPlayer = dynamic_cast<player*>(droppedOn);
            if (targetPlayer) {
                emit Card_Dropped_On_Player(this);
                event->accept();
                QGraphicsItemGroup::mouseReleaseEvent(event);
                return;
            }
        }

        emit Card_Dropped(this);
        Reset_Position();
        event->accept();
    }
    QGraphicsItemGroup::mouseReleaseEvent(event);
}

void Card::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    Set_Hovered(true);
    setCursor(Qt::OpenHandCursor);
    event->accept();
    QGraphicsItemGroup::hoverEnterEvent(event);
}

void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    Set_Hovered(false);
    if (!m_isDragged) {
        setCursor(Qt::ArrowCursor);
    }
    event->accept();
    QGraphicsItemGroup::hoverLeaveEvent(event);
}