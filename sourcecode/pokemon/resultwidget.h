#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QWidget>
#include"config.h"
#include<QBitmap>
#include<QPainter>
#include<QPixmap>
#include<QTimer>
#include<QTcpSocket> //通信套接字
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>
#include<QListWidgetItem>
#include<QException>
#include"mypushbutton.h"
#include"manager.h"
#include"listitem.h"
extern Manager ma;


namespace Ui {
class ResultWidget;
}

//对战结果界面类
class ResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResultWidget(QTcpSocket *_tcpSocket, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    ~ResultWidget();

private:
    bool choose = true;//是否已经选择要丢掉的小精灵
    QPixmap pix;//背景图

public slots:
    void switchFight();//返回战斗界面
    void receiveFromHost();//处理服务器传来的信息
    void sendInfo();//给服务器传送信息
    void reconnect();//可以接受服务器传来的信息
    void dealClicked(int);//点击列表某个小精灵，参数是小精灵ID
    void clearList();//清空列表

signals:
    void closed();//关闭窗口时发出信号

private:
    QTcpSocket *tcpSocket;
    Ui::ResultWidget *ui;
};

#endif // RESULTWIDGET_H
