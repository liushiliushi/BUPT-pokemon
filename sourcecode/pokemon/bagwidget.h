#ifndef BAGWIDGET_H
#define BAGWIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include"config.h"
#include<QTimer>
#include<QPainter>
#include<QListWidget>
#include<QIcon>
#include<QScroller>
#include"mypushbutton.h"
#include"listitem.h"
#include"userlist.h"
#include<QScrollBar>
#include"spiritinfo.h"
#include<QTcpSocket> //通信套接字
#include<QJsonObject>
#include<QJsonDocument>
#include<QByteArray>
#include<QMessageBox>

namespace Ui {
class BagWidget;
}

class Lobby;

//背包界面
class BagWidget : public QWidget
{
    Q_OBJECT

private:
    int money;

public:
    QListWidget *list = NULL;//列表指针
    SpiritInfo *spiritInfo = NULL;//精灵信息窗口指针
    QTcpSocket *tcpSocket;
    BagWidget(QTcpSocket *_tcpSocket, QWidget *parent = nullptr);
    ~BagWidget();
    void paintEvent(QPaintEvent *event);
    void clearList();//清楚列表表项
public slots:
    void switchLobby();//切换到大厅
    void consult();//查询
    void reconnect();//可以接受服务器传来的数据
    virtual void receiveFromHost();//处理服务器传来的数据
    void dealClicked(int);//处理点击列表表项的事件


private:
    Ui::BagWidget *ui;


signals:
    void closed();//关闭窗口信号
};

#endif // BAGWIDGET_H
