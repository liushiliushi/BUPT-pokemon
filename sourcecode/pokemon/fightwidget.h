#ifndef FIGHTWIDGET_H
#define FIGHTWIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <windows.h>
#include"config.h"
#include<QTimer>
#include<QPainter>
#include<QListWidget>
#include<QIcon>
#include<QScroller>
#include"mypushbutton.h"
#include"listitem.h"
#include"userlist.h"
#include<QTcpSocket> //通信套接字
#include<QJsonObject>
#include<QJsonDocument>
#include<QByteArray>
#include<QMessageBox>
#include<QTimer>
#include"pokemon.h"
#include"resultwidget.h"
#include"time.h"

namespace Ui {
class FightWidget;
}

//对战界面
class FightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FightWidget(QTcpSocket *_tcpSocket, QWidget *parent = nullptr);
    ~FightWidget();
    void paintEvent(QPaintEvent *event);
    QPixmap pix;//对战界面背景图
    void fight(Pokemon *mPokemon, Pokemon *sPokemon);//对战函数
    void consult();//向服务器查询相关信息
    void reconnect();//重新向服务器查询相关信息
    //创建精灵对象
    Pokemon * construct(QString spiritName, int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved);


public slots:
    void switchLobby();
    void receiveFromHost();

private:
    Ui::FightWidget *ui;
    QTcpSocket *tcpSocket;
    ResultWidget *result = NULL;//结果界面窗口指针

signals:
    void closed();
};

#endif // FIGHTWIDGET_H
