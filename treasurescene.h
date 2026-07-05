#ifndef TREASURESCENE_H
#define TREASURESCENE_H

#include <QWidget>

namespace Ui {
class TreasureScene;
}

class TreasureScene : public QWidget
{
    Q_OBJECT

public:
    explicit TreasureScene(QWidget *parent = nullptr);
    ~TreasureScene();

private:
    Ui::TreasureScene *ui;
};

#endif // TREASURESCENE_H
