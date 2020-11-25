#include "choose2.h"
#include "ui_choose2.h"

Choose2::Choose2(QTcpSocket *_tcpSocket, QWidget *parent) :
    BagWidget(tcpSocket, parent),
    ui(new Ui::Choose2)
{
    ui->setupUi(this);

    tcpSocket = _tcpSocket;
    fight = new FightWidget(tcpSocket);

    //配置场景
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowFlags(Qt::FramelessWindowHint);

    //退出按钮
    MyPushButton *exitBtn = new MyPushButton(EXIT_PATH);
    exitBtn->setParent(this);
    exitBtn->move( 1200, 20);
    //返回按钮
    MyPushButton *retBtn = new MyPushButton(RET_PATH);
    retBtn->setParent(this);
    retBtn->move( 20, 20);

    //绘制精灵列表
    list = new QListWidget(this);

    list->setViewMode(QListView::ListMode);
    list->setFlow(QListView::LeftToRight);//横向排列
    //设置list格式
    list->setFixedSize(1200, 400);
    list->setStyleSheet("background-color:transparent");//设置背景色为透明
    list->setFrameShape(QListWidget::NoFrame);
    list->move(30, 200);
    list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));//点击关闭按钮
    connect(retBtn, SIGNAL(clicked()), this, SLOT(switchLobby()));//点击返回按钮
    //connect(retBtn, SIGNAL(clicked()), this, SIGNAL(closed()));
    connect(fight, SIGNAL(closed()), this, SLOT(swithcLobby()));//返回大厅
}

void Choose2::receiveFromHost()
{
    //从通信套接字中取出内容
    QByteArray array = tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    qDebug()<<"chooseWidget收到服务器："<<json<<endl;
    if(json["socketID"] != ma.socketID)
    {
        return;
    }
    if(json["define"] == BAG)
    {

        /* 设置为像素滚动 */
        list->setHorizontalScrollMode(QListWidget::ScrollPerPixel);

        /* 设置鼠标左键拖动 */
        QScroller::grabGesture(list, QScroller::LeftMouseButtonGesture);

        QJsonArray spirits(json["spirits"].toArray());
        int num = spirits.size();
        //money = json["money"].toInt();
        for(int i = 0; i < num; i++)
        {
            QJsonObject tem = spirits[i].toObject();
            QString spirit_name = tem["spirit_name"].toString();//小精灵名字
            int id = tem["spirit_ID"].toInt();//小精灵ID
            int evolved = tem["evolved"].toInt();
            QString grade = QString::number(tem["grade"].toInt());
            ListItem *newItem = new ListItem(this, evolved, spirit_name, grade);
            newItem->setIndex(id);//设置标号
            QListWidgetItem *item0 = new QListWidgetItem();
            //item0->setSizeHint(QSize(140, 170));
            item0->setSizeHint(QSize(342, 400));
            list->addItem(item0);
            list->setItemWidget(item0, newItem);
            //记录选中小精灵的ID
            connect(newItem, SIGNAL(listItemClicked(int)), this, SLOT(dealClicked(int)));
        }


    }
    else
    {

    }

}

void Choose2::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(BAGWIDGET_PATH);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //绘制文字
    QFont font1("华文琥珀",30,QFont::Bold,false);
    painter.setFont(font1);
    painter.setPen(Qt::black);
    painter.drawText(480, 120, "选择我的对战精灵");
}

void Choose2::dealClicked(int id)
{
    qDebug()<<"选中的小精灵ID:"<<id<<endl;
    ma.mID = id;
    bool flag = tcpSocket->disconnect();//bagWidget断开与服务器连接
    if(flag == true)
    {
        qDebug()<<"choose2Widget断开与服务器连接"<<endl;
    }
    else
    {
        qDebug()<<"choose2Widget未能断开与服务器连接"<<endl;
    }

    fight->consult();//查询信息
    fight->reconnect();//fight连接服务器
    this->clearList();//清空列表
    this->close();
    fight->show();//弹出精灵信息窗口

}


Choose2::~Choose2()
{
    delete ui;
    delete fight;
    delete tcpSocket;
}
