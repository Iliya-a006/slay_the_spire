#ifndef CAMPSCENE_H
#define CAMPSCENE_H

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
    QGraphicsScene* listScene;
    QGraphicsView* listView;

    void restOption();
    void smithOption();
    void recallOption();
    void hideOptions();
    void showLeavePage(QString text);
};

#endif // CAMPSCENE_H
