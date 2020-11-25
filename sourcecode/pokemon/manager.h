#ifndef MANAGER_H
#define MANAGER_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QTextCodec>
#include"config.h"
#include<QDebug>
#include<QMessageBox>
#include<QString>
#include<QTcpSocket> //通信套接字
#include<QJsonObject>
#include<QJsonDocument>
#include<QByteArray>
#include<QMessageBox>
#include<QHostAddress>
#pragma execution_character_set("utf-8")

#include <QObject>
#include<QTimer>

//管理者类
class Manager
{
public:
    explicit Manager();
    bool isOpen;//是否打开
    QString username;//玩家姓名
    int userID;//玩家ID
    QMap<QString, QString> shmap;//小精灵未进化头像
    QMap<QString, QString> bhmap;//小精灵已进化头像
    QMap<QString, QString> sfmap;//小精灵未进化正面图
    QMap<QString, QString> bfmap;//小精灵已进化正面图
    QMap<QString, QString> sbmap;//小精灵未进化背面图
    QMap<QString, QString> bbmap;//小精灵未进化背面图
    QMap<QString, QString> sf_fmap;//小精灵未进化正面图（放大）
    QMap<QString, QString> bf_fmap;//小精灵已进化正面图（放大）
    QMap<QString, QString> sb_fmap;//小精灵未进化背面图（放大）
    QMap<QString, QString> bb_fmap;//小精灵已进化背面图（放大）
    QMap<QString, QString> skill;//小精灵普通技能
    QMap<QString, QString> sskill;//小精灵升级技能

    int mID;//玩家方小精灵
    int sID;//服务器方小精灵

    bool vs = false;//是否是vs模式
    int win = 0;//是否胜利(0:平局 1：赢 -1：输)
    int socketID;

};

#endif // MANAGER_H
