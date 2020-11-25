#ifndef SPIRITINFO_H
#define SPIRITINFO_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include<QTcpSocket> //通信套接字
#include<QJsonObject>
#include<QJsonDocument>
#include<QMessageBox>
#include<QByteArray>
#include<QMessageBox>
#include<QPainter>
#include"config.h"
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonObject>
#include"mypushbutton.h"
#include"manager.h"
extern Manager ma;

namespace Ui {
class SpiritInfo;
}

//小精灵信息类
class SpiritInfo : public QWidget
{
    Q_OBJECT

public:
    explicit SpiritInfo(QTcpSocket *_tcpSocket, QWidget *parent = nullptr);
    ~SpiritInfo();
    void paintEvent(QPaintEvent *event);

private:
    QPixmap pix;//背景图
    int money;//钱
    QString spirit_name;//小精灵姓名
    int spirit_type;//小精灵类型
    int grade;//小精灵等级
    int evolved;//是否进化
    int exp;//经验值
    int attack;//攻击值
    int defend;//防御值
    int hp;//hp值
    int interval;//攻击间隔
    int spirit_ID;//小精灵id
    int skillEvolved;//技能是否进化

public slots:
    void consult(int id);//查询小精灵信息
    void receiveFromHost();//收到服务器传来的信息
    void reconnect();//与服务器连接
    void closeInfo();//点击关闭按钮

private:
    Ui::SpiritInfo *ui;
    QTcpSocket *tcpSocket;

signals:
    void closed();
private slots:
    void on_pushButton_clicked();//点击进化按钮
    void on_pushButton_2_clicked();//点击技能进化按钮
};

#endif // SPIRITINFO_H
