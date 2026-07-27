#ifndef CAMPSCENE_H
#define CAMPSCENE_H

#include "card.h"
#include "roomscene.h"
#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>

class CampScene : public RoomScene
{
    Q_OBJECT

public:
    explicit CampScene(QWidget *parent = nullptr);
    ~CampScene();

    void resetRoom() override;

private:
    QPushButton* restButton;
    QPushButton* smithButton;
    QPushButton* recallButton;
    QPushButton* leaveButton;
    QPushButton* upgradeButton;
    QPushButton* nextButton;
    QLabel* titleLabel;
    QLabel* restLabel;
    QLabel* smithLabel;
    QLabel* recallLabel;
    QLabel* leaveLabel;
    QLabel* chooseLabel;
    QGraphicsScene* listScene;
    QGraphicsView* listView;


    Card* m_selectedCard = nullptr;

    void restOption();
    void smithOption();
    void recallOption();
    void hideOptions();
    void showLeavePage(QString text);
    void clearListScene();

private slots:
    void onCardClickedForUpgrade(Card* card);

};

#endif // CAMPSCENE_H
