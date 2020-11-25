#ifndef LISTITEM_H
#define LISTITEM_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include<QIcon>
#include<QLabel>
#include<QPainter>
#include"config.h"
#include<QMouseEvent>
#include<QTcpSocket> //通信套接字
#include<QJsonObject>
#include<QJsonDocument>
#include<QByteArray>
#include<QMessageBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLabel>
#include<QPixmap>
#include<QMap>
#include"manager.h"
extern Manager ma;

//列表表项
class ListItem : public QWidget
{
    Q_OBJECT
public:
    int model;//是哪种模式
    int index;//标致是第几项
    explicit ListItem(QWidget *parent, const QString &icon1, const QString &text1, const QString &text2);
    ListItem(QWidget *parent, int evolved, QString spirit_name, QString grade);//背包小精灵项
    ListItem(QWidget *parent, QString username, int online, QString grade);//用户列表项
    ListItem(QWidget *parent, QString spirit_name, QString grade, int evolved);//用户信息小精灵项
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);//重写鼠标点击事件
    void setIndex(int);//设置index值
    int getIndex();//获取index值
private:
    QLabel la1;
    QLabel la2;
    QLabel la3;

signals:
    void listItemClicked(int);//被点击后发出信号，参数是index值


signals:

};

#endif // LISTITEM_H
