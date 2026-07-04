#include "map1.h"
#include "ui_map1.h"
#include <QVBoxLayout>

Map1::Map1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Map1)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
    m_view  = new QGraphicsView(m_scene, this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
    setLayout(layout);
}

Map1::~Map1()
{
    delete ui;
}
