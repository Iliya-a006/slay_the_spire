#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>
#include <QLabel>
#include <qstackedwidget.h>

class TopBar : public QWidget
{
    Q_OBJECT

public:
    static TopBar* instance(QWidget* parent = nullptr);
    static void update(QWidget *p = nullptr);

    void setPlayerName(const QString& name);
    void setHP(int currentHP, int maxHP);
    void setGold(int gold);
    void setFloor(int floor);

private:
    explicit TopBar(QWidget* parent = nullptr);

    static TopBar* m_instance;

    void setupUI();

    QLabel* m_nameLabel;
    QLabel* m_heartIcon;
    QLabel* m_hpLabel;
    QLabel* m_coinIcon;
    QLabel* m_goldLabel;
    QLabel* m_mapIcon;
    QLabel* m_stairsIcon;
    QLabel* m_floorLabel;
};

#endif // TOPBAR_H
