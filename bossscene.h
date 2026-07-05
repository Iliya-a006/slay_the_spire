#ifndef BOSSSCENE_H
#define BOSSSCENE_H

#include <QWidget>

namespace Ui {
class BossScene;
}

class BossScene : public QWidget
{
    Q_OBJECT

public:
    explicit BossScene(QWidget *parent = nullptr);
    ~BossScene();

private:
    Ui::BossScene *ui;
};

#endif // BOSSSCENE_H
