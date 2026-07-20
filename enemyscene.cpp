#include "enemyscene.h"
#include "ui_enemyscene.h"
#include "screensize.h"
#include <QVBoxLayout>

EnemyScene::EnemyScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EnemyScene)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background: transparent;");

    m_scene = new QGraphicsScene(this);
    m_view = new QGraphicsView(m_scene, this);

    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setStyleSheet("background: transparent; border: none;");
    m_view->setAttribute(Qt::WA_TranslucentBackground);
    m_view->viewport()->setStyleSheet("background: transparent;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_view);
    setLayout(layout);

    m_view->setGeometry(0, 0, width(), height());
    m_scene->setSceneRect(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_scene->setBackgroundBrush(Qt::transparent);

    m_playerAvatar = nullptr;
}

EnemyScene::~EnemyScene()
{
    delete ui;
    if (m_playerAvatar) {
        m_scene->removeItem(m_playerAvatar);
        delete m_playerAvatar;
        m_playerAvatar = nullptr;
    }
}

void EnemyScene::setupCombat()
{
    setupPlayerAvatar();
}

void EnemyScene::setupPlayerAvatar()
{
    player* p = player::instance();
    if (!p) return;

    if (m_playerAvatar) {
        m_scene->removeItem(m_playerAvatar);
        delete m_playerAvatar;
        m_playerAvatar = nullptr;
    }

    m_playerAvatar = new QGraphicsPixmapItem();
    m_playerAvatar->setPixmap(p->pixmap());
    m_playerAvatar->setScale(0.8);
    m_playerAvatar->setPos(50, ScreenSize::getHeigth() - 250);
    m_scene->addItem(m_playerAvatar);
}

void EnemyScene::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    m_view->setGeometry(0, 0, width(), height());
    m_scene->setSceneRect(0, 0, width(), height());
}