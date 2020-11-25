#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include<QDebug>
#include<QPushButton>
#pragma execution_character_set("utf-8")
//按钮类
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QPushButton *parent = 0);
    MyPushButton(QString normalImg, QString pressImg="");

    //保存用户传入的默认显示路径和按下后显示的图片路径
    QString normalImgPath;//正常情况显示的图片
    QString pressImgPath;//按下时显示的图片
signals:

};

#endif // MYPUSHBUTTON_H
