#ifndef USERLIST_H
#define USERLIST_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include"config.h"
#include<QBitmap>
#include<QPainter>
#include<QPixmap>
#include"mypushbutton.h"
#include"listitem.h"
#include<QTimer>
#include"userinfo.h"
#include<QListWidget>
#include<QTcpSocket> //通信套接字
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>
#include<QListWidgetItem>

namespace Ui {
class UserList;
}

//用户列表类
class UserList : public QWidget
{
    Q_OBJECT

public:
    explicit UserList(QTcpSocket *_tcpSocket, QWidget *parent = nullptr);
    ~UserList();
    void paintEvent(QPaintEvent *event);

private:
    QPixmap pix;//背景图
    QStringList names;//玩家姓名列表
    QListWidget *list = NULL;//列表指针
    UserInfo *userInfo = NULL;//用户信息指针
    Ui::UserList *ui;
    QTcpSocket *tcpSocket;

public slots:
    void switchUserIfo();//转到用户信息窗口
    void receiveFromServer();//接收服务器传来的信息
    void closeList();//关闭列表
    void consult();//向服务器查询信息
    void dealClicked(int index);//处理列表表项事件
    void reconnect();//可以接收服务器穿里啊的信息

signals:
    void closed();//关闭窗口时发出信号
};

#endif // USERLIST_H
