#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include<QTcpServer> //监听套接字
#include<QTcpSocket> //通信套接字
#include<QByteArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QException>
#include<QSqlRecord>
#include<QVector>
#include<QList>
#include"manager.h"
#include"config.h"
#include"time.h"
#include"pokemon.h"

extern Manager ma;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void LogIn(QJsonObject);//登陆
    void SignIn(QJsonObject);//注册
    void SignOut(QJsonObject);//登出
    void Lobby(QJsonObject);//大厅查询
    void UserList(QJsonObject);//用户列表信息查询
    void UserInfo(QJsonObject);//用户信息信息查询
    void Bag(QJsonObject);//背包信息查询
    void SpiritInfo(QJsonObject);//小精灵信息查询
    void Choose(QJsonObject);//查询服务器小精灵
    void FightUser(QJsonObject);//查询用户信息
    void SpiritUpgrade(QJsonObject);//小精灵升级
    void SpiritUp(QJsonObject);//小精灵进化
    void SkillUp(QJsonObject);//技能进化
    void ResultVsFail(QJsonObject);
    void ResultFightFail(QJsonObject);
    void ResultVsWin(QJsonObject);
    void ResultFightWin(QJsonObject);
    void AdoptOne(QJsonObject);//丢弃一个小精灵
    void SendMessage(QJsonObject);//群发信息

    //Pokemon * construct(QString spiritName, int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved);
private:
    Ui::MainWindow *ui;

    QTcpServer *tcpServer;//监听套接字
    //QTcpSocket *tcpSocket;//通信套接字
    QList<QTcpSocket *> socketList;//存放所有客户端socket
    int socketID = 0;
};
#endif // MAINWINDOW_H
