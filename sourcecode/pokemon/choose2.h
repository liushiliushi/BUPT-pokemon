#ifndef CHOOSE2_H
#define CHOOSE2_H

#include <QWidget>
#include"bagwidget.h"
#include"fightwidget.h"

namespace Ui {
class Choose2;
}

//选择玩家小精灵界面
class Choose2 : public BagWidget
{
    Q_OBJECT

public:
    explicit Choose2(QTcpSocket *_tcpSocket, QWidget *parent = nullptr);
    FightWidget *fight = NULL;//对战界面窗口
    ~Choose2();
    void paintEvent(QPaintEvent *event) override;


public slots:
    void dealClicked(int id);//处理点击列表表项事件
    void receiveFromHost() override;//处理服务器传来的信息


private:
    Ui::Choose2 *ui;
};

#endif // CHOOSE2_H
