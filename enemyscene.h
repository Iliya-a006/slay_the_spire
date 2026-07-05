#ifndef ENEMYSCENE_H
#define ENEMYSCENE_H

#include <QWidget>

namespace Ui {
class EnemyScene;
}

class EnemyScene : public QWidget
{
    Q_OBJECT

public:
    explicit EnemyScene(QWidget *parent = nullptr);
    ~EnemyScene();

private:
    Ui::EnemyScene *ui;
};

#endif // ENEMYSCENE_H
