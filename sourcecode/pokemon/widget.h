#ifndef WIDGET_H
#define WIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QIcon>
#include"login.h"
#include<QTimer>
#include<QTcpSocket> //通信套接字
#include<QHostAddress>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

//开始界面类
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //重写paintevent事件，画背景图
    void paintEvent(QPaintEvent *event);


private:
    Ui::Widget *ui;
    QTcpSocket *tcpSocket;
    Login *login = NULL;//登陆窗口指针

private slots:
    void switchLogin();//切换到登陆界面
    void receiveFromServer();//接收到服务器回复


};
#endif // WIDGET_H
