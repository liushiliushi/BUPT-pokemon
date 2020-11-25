#ifndef CHOOSE_H
#define CHOOSE_H
#include"bagwidget.h"
#include"choose2.h"



namespace Ui {
class Choose;
}

//选择服务器小精灵界面
class Choose : public BagWidget
{
    Q_OBJECT

public:
    explicit Choose(QTcpSocket *_tcpSocket, QWidget *parent = nullptr);
    ~Choose();
    void paintEvent(QPaintEvent *event);
    void receiveFromHost();
    Choose2 *choose2 = NULL;//玩家选择精灵窗口指针


public slots:
    void consult();//向服务器查询信息
    void dealClicked(int id);//处理点击表项事件


private:
    Ui::Choose *ui;
};

#endif // CHOOSE_H
