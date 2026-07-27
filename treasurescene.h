#ifndef TREASURESCENE_H
#define TREASURESCENE_H

#include "chest.h"
#include "roomscene.h"
#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>

class TreasureScene : public RoomScene
{
    Q_OBJECT

public:
    explicit TreasureScene(QWidget *parent = nullptr);
    ~TreasureScene();

    void resetRoom() override;

private:
    QGraphicsPixmapItem* coinItem;
    QGraphicsRectItem* dimmer;
    Chest* chest;
    QLabel* topLabel;
    QLabel* countLabel;
    QLabel* nameLabel;
    QPushButton* nextbutton;
    bool is_end;
    bool recieved;
    int NOfGolds;

    void goldGift();
    void relicGift();

private slots:
    void onChestClicked();
};

#endif // TREASURESCENE_H
