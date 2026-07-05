#include "map1.h"
#include "bossroom.h"
#include "eliteroom.h"
#include "enemyroom.h"
#include "eventroom.h"
#include "campfireroom.h"
#include "player.h"
#include "shoproom.h"
#include "treasureroom.h"
#include "ui_map1.h"
#include <QVBoxLayout>
#include "screensize.h"
#include <QRandomGenerator>
#include "RoomEnum.h"
#include <QFile>
#include "screensize.h"

Map1::Map1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Map1)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
    m_view  = new QGraphicsView(m_scene, this);
    m_scene->setSceneRect(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth()*2);
    m_view->setGeometry(0, 0, width(), height());

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
    setLayout(layout);

    QSize s = ScreenSize::getSize();
    s.setHeight(ScreenSize::getHeigth() * 2);
    QPixmap bg(":/prefix1/images/paperBg3.png");
    QPixmap scaledBg = bg.scaled(s, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgItem = m_scene->addPixmap(scaledBg);
    bgItem->setZValue(-100);
    bgItem->setPos(0, 0);


    loadMap();
    printMap();
    roadCreator();


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
            floors.resize(11);
            for (int i=0; i<11; ++i)
                floors[i].resize(floorsCode[i].size());
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
                floors.resize(11);
                for (int i=0; i<11; ++i)
                    floors[i].resize(floorsCode[i].size());
                file.close();
                return;
            }
        }
        file.close();
        if (file.open(QIODevice::ReadWrite)){
            mapCoder();
            floors.resize(11);
            for (int i=0; i<11; ++i)
                floors[i].resize(floorsCode[i].size());
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

void Map1::printMap()
{
    for (int i=0; i < 11; ++i){
        for (int j=0; j < floorsCode[i].size(); ++j){
            int roomType = floorsCode[i][j];
            while(roomType/10)
                roomType /= 10;
            floors[i][j] = roomCreator(roomType);
            if (!floors[i][j]){continue;}

            floors[i][j]->x = roomWidth(floorsCode[i].size()*10 + j);
            floors[i][j]->y = roomHeigth(i);
            floors[i][j]->setPos(floors[i][j]->x, floors[i][j]->y);
            m_scene->addItem(floors[i][j]);
        }
    }
}

Room* Map1::roomCreator(int roomType)
{
    switch (roomType) {
    case (int)RoomEnum::enemy:
        return new EnemyRoom();
        break;
    case (int)RoomEnum::elite:
        return new EliteRoom();
        break;
    case (int)RoomEnum::event:
        return new EventRoom();
        break;
    case (int)RoomEnum::treasure:
        return new TreasureRoom();
        break;
    case (int)RoomEnum::campfire:
        return new CampfireRoom();
        break;
    case (int)RoomEnum::shop:
        return new ShopRoom();
        break;
    case (int)RoomEnum::boss:
        return new BossRoom();
        break;
    default:
        return nullptr;
        break;
    }
}

int Map1::roomHeigth(int floor)
{
    ++floor;
    return (ScreenSize::getHeigth()*2 * ((12-floor)) / 12);
}
int Map1::roomWidth(int type)
{
    int centeral = ScreenSize::getWidth() / 2;
    int iconWidth = 60;
    switch (type) {
    case 10:
    case 31:
        return centeral;
        break;
    case 20:
    case 41:
        return centeral - 50 - iconWidth;
        break;
    case 21:
    case 42:
        return centeral + 50 + iconWidth;
        break;
    case 30:
        return centeral - 2*50 - 2*iconWidth;
        break;
    case 32:
        return centeral + 2*50 + 2*iconWidth;
        break;
    case 40:
        return centeral - 3*50 - 3*iconWidth;
        break;
    case 43:
        return centeral + 3*50 + 3*iconWidth;
        break;
    default:
        return 0;
        break;
    }
}

void Map1::roadCreator()
{
    int tmp;
    for (int i=0; i < 10; ++i){
        for (int j=0; j < floorsCode[i].size(); ++j){
            tmp = floorsCode[i][j];
            while(tmp / 10){
                floors[i][j]->nextRooms.push_back(floors[i+1][tmp%10]);
                tmp /= 10;
            }
        }
    }
    for (int i=1; i < 11; ++i){
        for (int j=0; j < floorsCode[i].size(); ++j){
            Room* pre = floors[i][j];
            for (int k=0; k < floorsCode[i-1].size(); ++k){
                for (int l=0; l < floors[i-1][k]->nextRooms.size(); ++l){
                    if (floors[i-1][k]->nextRooms[l] == pre)
                        floors[i][j]->previouseRooms.push_back(floors[i-1][k]);
                }
            }
        }
    }

    for (int i=0; i < 10; ++i){
        for (int j=0; j < floorsCode[i].size(); ++j){
            for (int k=0; k < floors[i][j]->nextRooms.size(); ++k){
                floors[i][j]->roads.push_back(m_scene->addLine(
                    floors[i][j]->x+30, floors[i][j]->y+30, floors[i][j]->nextRooms[k]->x+30, floors[i][j]->nextRooms[k]->y+30, QPen(Qt::black, 2)));
                floors[i][j]->roads[k]->setZValue(-1);
            }
        }
    }
}



Map1::~Map1()
{
    delete ui;
}
