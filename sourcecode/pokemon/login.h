#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QWidget>
#include"config.h"
#include"lobby.h"
#include<QPainter>
#include<QTimer>
#include<QDebug>
#include<QPalette>
#include<QTcpSocket> //通信套接字
#include<QJsonObject>
#include<QJsonDocument>
#include<QByteArray>
#include<QMessageBox>
#include"manager.h"
#pragma execution_character_set("utf-8")
namespace Ui {
class Login;
}
extern Manager ma;
//登陆界面
class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QTcpSocket *_tcpSocket, QWidget *parent = nullptr);
    ~Login();

    //重写绘图事件
    void paintEvent(QPaintEvent *event);

public slots:

    //连接服务器，发送登陆信息
    void LogIn();//发送登陆信息
    void receiveFromServer();//处理服务器传回的信息
    void reconnect();//可以接受服务器传来的信息


private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;
    QTcpSocket *tcpSocket;
    Lobby *lobby = NULL;//游戏大厅窗口指针
};

#endif // LOGIN_H
