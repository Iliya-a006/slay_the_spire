#include "topbar.h"
#include <QHBoxLayout>
#include <qgraphicsitem.h>
#include <qstackedwidget.h>
#include "screensize.h"
#include "player.h"

TopBar* TopBar::m_instance = nullptr;

TopBar* TopBar::instance(QWidget *parent)
{
    if (!m_instance)
        m_instance = new TopBar(parent);
    if (parent){
        delete m_instance;
        m_instance = new TopBar(parent);
    }

    return m_instance;
}

TopBar::TopBar(QWidget* parent)
    : QWidget(parent)
{
    setFixedHeight(40);
    setupUI();
}

void TopBar::setupUI()
{
    QLabel *Bg = new QLabel(this);
    Bg->setGeometry(0, 0, ScreenSize::getWidth(), 40);
    Bg->setScaledContents(true);
    Bg->setPixmap(QPixmap(":/prefix1/images/gray.jfif"));
    Bg->show();


    m_nameLabel  = new QLabel(this);
    m_heartIcon  = new QLabel(this);
    m_hpLabel    = new QLabel(this);
    m_coinIcon   = new QLabel(this);
    m_goldLabel  = new QLabel(this);
    m_mapIcon    = new QLabel(this);
    m_stairsIcon = new QLabel(this);
    m_floorLabel = new QLabel(this);

    m_nameLabel->setStyleSheet("color: white; font-weight: bold; font-size: 16px;");
    m_hpLabel->setStyleSheet("color: #e53030; font-size: 14px; font-weight: bold;");
    m_goldLabel->setStyleSheet("color: #ffd700; font-size: 14px;");
    m_floorLabel->setStyleSheet("color: white; font-size: 14px;");

    m_heartIcon->setPixmap(QPixmap(":/icons/images/heart.png").scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_coinIcon->setPixmap(QPixmap(":/icons/images/coin.png").scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_mapIcon->setPixmap(QPixmap(":/icons/images/map.png").scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_stairsIcon->setPixmap(QPixmap(":/icons/images/stairs.png").scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(15, 5, 15, 5);
    layout->setSpacing(20);

    layout->addWidget(m_nameLabel);
    layout->addStretch();
    layout->addWidget(m_heartIcon);
    layout->addWidget(m_hpLabel);
    layout->addStretch();
    layout->addWidget(m_coinIcon);
    layout->addWidget(m_goldLabel);
    layout->addStretch();
    layout->addStretch();
    layout->addStretch();
    layout->addStretch();
    layout->addStretch();
    layout->addStretch();
    layout->addStretch();
    layout->addStretch();
    layout->addStretch();
    layout->addStretch();
    layout->addWidget(m_stairsIcon);
    layout->addWidget(m_floorLabel);
    layout->addStretch();
    layout->addWidget(m_mapIcon);

    setLayout(layout);
}

void TopBar::setPlayerName(const QString& name)
{
    m_nameLabel->setText(name);
}

void TopBar::setHP(int currentHP, int maxHP)
{
    m_hpLabel->setText(QString("%1/%2").arg(currentHP).arg(maxHP));
    m_hpLabel->setText(QString::number(currentHP) + "/" + QString::number(maxHP));
}

void TopBar::setGold(int gold)
{
    m_goldLabel->setText(QString::number(gold));
}

void TopBar::setFloor(int floor)
{
    m_floorLabel->setText(QString::number(floor+1));
}

