#include "map1.h"
#include "player.h"
#include "ui_map1.h"
#include <QVBoxLayout>
#include "screensize.h"
#include <QRandomGenerator>
#include "RoomEnum.h"
#include <QFile>

Map1::Map1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Map1)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
    m_view  = new QGraphicsView(m_scene, this);
    m_scene->setSceneRect(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_view->setGeometry(0, 0, width(), height());

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
    setLayout(layout);

    QPixmap bg(":/prefix1/images/paperBg3.png");
    QPixmap scaledBg = bg.scaled(ScreenSize::getSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgItem = m_scene->addPixmap(scaledBg);
    bgItem->setZValue(-100);
    bgItem->setPos(0, 0);


    loadMap();


}

void Map1::loadMap()
{
    QVector<QVector<int>> tmp;
    int ID=1, nextID=ID+1;
    QFile file("maps.bin");
    if (!file.open(QIODevice::ReadOnly)){
        if (file.open(QIODevice::WriteOnly)){
            mapCoder();
            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_6_5);
            out << nextID;
            out << ID << floorsCode;
            player::instance()->setMapID(ID);
            file.close();
            return;
        }
        else
            return;
    }
    else{
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_6_5);
        in >> nextID;
        while(!in.atEnd()){
            in >> ID >> tmp;
            if (ID == player::instance()->getMapID()){
                floorsCode = tmp;
                file.close();
                return;
            }
        }
        file.close();
        if (file.open(QIODevice::ReadWrite)){
            mapCoder();
            ID = nextID;
            ++nextID;
            player::instance()->setMapID(ID);
            QDataStream stream(&file);
            stream.setVersion(QDataStream::Qt_6_5);
            file.seek(file.size());
            stream << ID << floorsCode;
            file.seek(0);
            stream << nextID;
            file.close();
        }
        else
            return;
    }
}

void Map1::mapCoder()
{
    floorsCode.resize(11);
    int typeOf_rooms;
    int NOf_rooms;
    int next;
    int previous;
    for (int i=0; i<11; ++i){
        if (i == 5 || i == 10)
            floorsCode[i].resize(1);
        else{
            NOf_rooms = QRandomGenerator::global()->bounded(10);
            if (NOf_rooms <= 1)
                floorsCode[i].resize(1);
            else if (NOf_rooms <= 4)
                floorsCode[i].resize(2);
            else if (NOf_rooms <= 7)
                floorsCode[i].resize(3);
            else
                floorsCode[i].resize(4);
        }

        if (i == 5)
            floorsCode[i][0] = ((int)RoomEnum::treasure);
        else if (i == 10)
            floorsCode[i][0] = ((int)RoomEnum::boss);
        else
            for (int j=0; j<floorsCode[i].size(); ++j){
                if (i == 0){
                    floorsCode[i][j] = ((int)RoomEnum::enemy);
                    continue;
                }
                typeOf_rooms = QRandomGenerator::global()->bounded(100);
                if (typeOf_rooms < 40)
                    floorsCode[i][j] = (int)RoomEnum::enemy;
                else if (typeOf_rooms < 58)
                    floorsCode[i][j] = (int)RoomEnum::elite;
                else if (typeOf_rooms < 80)
                    floorsCode[i][j] = (int)RoomEnum::event;
                else if (typeOf_rooms < 92)
                    floorsCode[i][j] = (int)RoomEnum::campfire;
                else
                    floorsCode[i][j] = (int)RoomEnum::shop;
            }
    }

    int count;
    int tmp;
    for (int i=0; i < 10; ++i){
        for (int j=0; j < floorsCode[i].size(); ++j){
            next = QRandomGenerator::global()->bounded(floorsCode[i+1].size());
            floorsCode[i][j] = floorsCode[i][j]*10 + next;
        }
        for (int k=0; k < floorsCode[i+1].size(); ++k){
            count = 0;
            for(int l=0; l < floorsCode[i].size(); ++l){
                tmp = floorsCode[i][l];
                while(tmp/10){
                    if (tmp%10 == k)
                        ++count;
                    tmp /= 10;
                }
            }
            if (count == 0){
                previous = QRandomGenerator::global()->bounded(floorsCode[i].size());
                floorsCode[i][previous] = floorsCode[i][previous]*10 + k;
            }
        }
    }

}


Map1::~Map1()
{
    delete ui;
}
