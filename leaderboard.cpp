#include "leaderboard.h"
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVector>
#include <array>
#include <qpushbutton.h>
#include "Page.h"
#include "mainwindow.h"
#include "player.h"


leaderBoard::leaderBoard(QWidget *parent)
    : QWidget(parent)
{
    QVector<player> players = player::allPlayers();
    std::sort(players.begin(), players.end(), [](player p1, player p2){
        return p1.getAct()*11 + p1.getFloor() > p2.getAct()*11 + p2.getFloor();
    });
    QVector<std::array<QString, 4>> items;
    items.resize(players.size());
    for (int i=0; i<players.size(); ++i){
        items[i][0] = QString::number(i+1);
        items[i][1] = players[i].getName();
        items[i][2] = QString::number(players[i].getAct());
        items[i][3] = QString::number(players[i].getFloor()+1);
    }

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(30, 30, 30, 30);

    QWidget *header = new QWidget();
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(4, 4, 4, 4);
    headerLayout->setSpacing(120);
    QLabel *headerLabel1 = new QLabel("Rank");
    QLabel *headerLabel2 = new QLabel("Name");
    QLabel *headerLabel3 = new QLabel("Act");
    QLabel *headerLabel4 = new QLabel("Floor");

    QString headerStyle = "QLabel {"
                          "   background-color: #3a2f1b;"
                          "   color: #f5deb3;"
                          "   border: 2px solid #8a6d3b;"
                          "   border-radius: 8px;"
                          "   padding: 6px 10px;"
                          "   font-size: 15px;"
                          "   font-family: 'Trebuchet MS', 'Verdana', 'Segoe UI';"
                          "   font-weight: bold;"
                          "}";
    headerLabel1->setStyleSheet(headerStyle);
    headerLabel2->setStyleSheet(headerStyle);
    headerLabel3->setStyleSheet(headerStyle);
    headerLabel4->setStyleSheet(headerStyle);
    headerLayout->addWidget(headerLabel1);
    headerLayout->addWidget(headerLabel2);
    headerLayout->addWidget(headerLabel3);
    headerLayout->addWidget(headerLabel4);


    QPushButton* backButton = new QPushButton("Back" ,this);
    backButton->setFixedSize(80, 40);
    backButton->setStyleSheet(R"(
    QPushButton {
        background-color: rgba(40, 20, 15, 180);
        border: 2px solid #c97a3d;
        border-radius: 8px;
        color: #f0d78c;
        font-size: 18px;
        font-weight: bold;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: rgba(201, 122, 61, 220);
        color: white;
    }
    QPushButton:pressed {
        background-color: rgba(150, 90, 40, 255);
    }
    )");
    connect(backButton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack((int)Page::MainMenu);
    });


    outerLayout->addWidget(header, 0, Qt::AlignCenter);
    outerLayout->addSpacing(10);
    QScrollArea *list = createScrollableList(items);
    outerLayout->addWidget(list, 0, Qt::AlignCenter);
    outerLayout->addWidget(backButton, 0, Qt::AlignCenter);
    outerLayout->addStretch();
}


QWidget* leaderBoard::createRow(const QString &text1, const QString &text2, const QString &text3, const QString &text4)
{
    QWidget *rowWidget = new QWidget();
    QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);
    rowLayout->setContentsMargins(4, 4, 4, 4);

    QLabel *label1 = new QLabel(text1);
    QLabel *label2 = new QLabel(text2);
    QLabel *label3 = new QLabel(text3);
    QLabel *label4 = new QLabel(text4);

    QString style = "QLabel {"
                    "   background-color: #3a2f1b;"
                    "   color: #f5deb3;"
                    "   border: 2px solid #8a6d3b;"
                    "   border-radius: 8px;"
                    "   padding: 6px 10px;"
                    "   font-size: 15px;"
                    "   font-family: 'Trebuchet MS', 'Verdana', 'Segoe UI';"
                    "   font-weight: bold;"
                    "}";
    label1->setStyleSheet(style);
    label2->setStyleSheet(style);
    label3->setStyleSheet(style);
    label4->setStyleSheet(style);

    rowLayout->addWidget(label1);
    rowLayout->addWidget(label2);
    rowLayout->addWidget(label3);
    rowLayout->addWidget(label4);
    return rowWidget;
}

QScrollArea* leaderBoard::createScrollableList(const QVector<std::array<QString,4>> &myItems)
{
    QWidget *listWidget = new QWidget();
    QVBoxLayout *listLayout = new QVBoxLayout(listWidget);
    for (const auto &item : myItems){
        QWidget *row = createRow(item[0], item[1], item[2], item[3]);
        listLayout->addWidget(row);
    }
    listLayout->addStretch();
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(listWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(800, 400);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    return scrollArea;
}


leaderBoard::~leaderBoard()
{
}