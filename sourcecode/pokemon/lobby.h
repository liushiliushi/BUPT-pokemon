#ifndef LOBBY_H
#define LOBBY_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include"config.h"
#include<QTimer>
#include<QPainter>
#include<QTcpSocket> //通信套接字
#include<QJsonObject>
#include<QJsonDocument>
#include<QByteArray>
#include<QMessageBox>
#include<QHostAddress>
#include"mypushbutton.h"
#include"userlist.h"
#include"bagwidget.h"
#include"fightwidget.h"
#include"manager.h"
#include"choose.h"

namespace Ui {
class Lobby;
}
extern Manager ma;

//大厅界面
class Lobby : public QWidget
{
    Q_OBJECT
private:
    int money;//用户金币
    int spirit_num;//用户小精灵个数
    int gspirit_num;//高级精灵个数
    UserList *userList = NULL;//用户列表窗口指针
    BagWidget *bagWidget = NULL;//背包窗口指针
    FightWidget *fightWidget = NULL;//对战界面窗口指针
    Choose *chooseWidget = NULL;//选择小精灵窗口指针
    Ui::Lobby *ui;
    QTcpSocket *tcpSocket;
public:
    explicit Lobby(QTcpSocket *_tcpSocket, QWidget *parent = nullptr);
    ~Lobby();
    void paintEvent(QPaintEvent *event);
public slots:
    void switchBagwidget();//转到背包界面
    void receiveFromServer();//处理来自服务器的信息
    void showUserList();//弹出用户列表
    void reconnect();//重新连接
    void consult();//向服务器查询信息
    void switchChoose();//选择
    void setVs();//设置对战为vs模式
    void setFight();//设置对战为fight模式

signals:
    void closed();//关闭窗口后发出信号
private slots:
    void on_pushButton_clicked();//点击登出按钮触发信号

};

#endif // LOBBY_H
