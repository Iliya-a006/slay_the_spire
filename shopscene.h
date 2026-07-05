#ifndef SHOPSCENE_H
#define SHOPSCENE_H

#include <QWidget>

namespace Ui {
class ShopScene;
}

class ShopScene : public QWidget
{
    Q_OBJECT

public:
    explicit ShopScene(QWidget *parent = nullptr);
    ~ShopScene();

private:
    Ui::ShopScene *ui;
};

#endif // SHOPSCENE_H
