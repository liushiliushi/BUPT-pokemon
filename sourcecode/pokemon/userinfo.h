#ifndef USERINFO_H
#define USERINFO_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include"config.h"
#include<QPainter>
#include<QPixmap>
#include"mypushbutton.h"
#include"listitem.h"
#include<QTimer>
#include<QTcpSocket> //通信套接字
#include<QJsonObject>
#include<QJsonDocument>
#include<QGridLayout>
#include<QJsonArray>
#include<QListWidgetItem>

namespace Ui {
class UserInfo;
}

//用户信息类
class UserInfo : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfo(QTcpSocket *_tcpSocket, QWidget *parent = nullptr);   
    void paintEvent(QPaintEvent *event);
    ~UserInfo();

private:
    Ui::UserInfo *ui;
    QTcpSocket *tcpSocket;
    QPixmap pix;//背景图
public slots:

    void consult(QString username);//查询用户信息
    void receiveFromHost();//收到服务器传来的信息
    void reconnect();//与服务器连接
    void closeInfo();//关闭

signals:
    void closed();
};

#endif // USERINFO_H
