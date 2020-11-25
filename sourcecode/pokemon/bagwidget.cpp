#include "bagwidget.h"
#include "ui_bagwidget.h"
#include"lobby.h"

BagWidget::BagWidget(QTcpSocket *_tcpSocket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BagWidget)
{
    ui->setupUi(this);
    tcpSocket = _tcpSocket;
    spiritInfo = new SpiritInfo(tcpSocket);

    //配置场景
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);//设置游戏界面大小
    setWindowTitle(GAME_TITLE);//设置游戏标题
    setWindowFlags(Qt::FramelessWindowHint);//取消窗口栏

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

    connect(retBtn, SIGNAL(clicked()), this, SLOT(switchLobby()));//点击返回按钮
    connect(spiritInfo, SIGNAL(closed()), this, SLOT(reconnect()));//关闭精灵信息窗口后重新连接服务器
    connect(spiritInfo, SIGNAL(closed()), this, SLOT(consult()));//重新查询信息
}



void BagWidget::switchLobby()
{

    //清空列表
    qDebug()<<"清空背包列表"<<endl;
    int counter = list->count();
    for(int index = 0; index < counter; index++)
    {
        QListWidgetItem *item = list->takeItem(0);
        list->removeItemWidget(item);
        delete item;
    }
    bool flag = tcpSocket->disconnect();//与服务器断开连接
    if(flag == true)
    {
        qDebug()<<"BagWidget断开与服务器连接"<<endl;
    }
    else
    {
        qDebug()<<"BagWidget未能断开与服务器连接"<<endl;
    }

    emit closed();
    //延时进入
    QTimer::singleShot(200, this, [=]{
        this->close();

    });
}

void BagWidget::clearList()
{
    int counter = list->count();
    for(int index = 0; index < counter; index++)
    {
        QListWidgetItem *item = list->takeItem(0);
        list->removeItemWidget(item);
        delete item;
    }
}

void BagWidget::reconnect()
{
    bool flag = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromHost()));//收到服务器回复
    if(flag == true)
    {
        qDebug()<<"BagWidget连接服务器"<<endl;
    }
    else
    {
        qDebug()<<"BagWidget未能连接服务器"<<endl;
    }
}

void BagWidget::receiveFromHost()
{
    //从通信套接字中取出内容
    QByteArray array = tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    qDebug()<<"BagWidget收到服务器："<<json<<endl;
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
        money = json["money"].toInt();
        for(int i = 0; i < num; i++)
        {
            QJsonObject tem = spirits[i].toObject();
            QString spirit_name = tem["spirit_name"].toString();//小精灵名字
            int id = tem["spirit_ID"].toInt();//小精灵ID    
            int evolved = tem["evolved"].toInt();//小精灵是否进化
            QString grade = QString::number(tem["grade"].toInt());//小精灵等级
            ListItem *newItem = new ListItem(this, evolved, spirit_name, grade);
            newItem->setIndex(id);//设置标号
            QListWidgetItem *item0 = new QListWidgetItem();
            item0->setSizeHint(QSize(342, 400));
            list->addItem(item0);
            list->setItemWidget(item0, newItem);//将widget于listwidgetitem绑定
            connect(newItem, SIGNAL(listItemClicked(int)), this, SLOT(dealClicked(int)));//将点击信号与处理点击事件槽连接
        }


    }
    else
    {

    }
    qDebug()<<"money"<<money<<endl;
    update();//重新绘图
}

void BagWidget::dealClicked(int id)
{
    qDebug()<<"选中的小精灵ID:"<<id<<endl;
    bool flag = tcpSocket->disconnect();//bagWidget断开与服务器连接
    if(flag == true)
    {
        qDebug()<<"bagWidget断开与服务器连接"<<endl;
    }
    else
    {
        qDebug()<<"bagWidget未能断开与服务器连接"<<endl;
    }
    spiritInfo->reconnect();//spiritInfo与服务器连接
    spiritInfo->consult(id);//spiritInfo查询信息
    spiritInfo->show();//弹出精灵信息窗口


}

void BagWidget::consult()
{
    clearList();//清理列表
    //向服务器查询所有用户信息
    QJsonObject json  = {
        {"define", BAG},
        {"socketID", ma.socketID},
        {"username", ma.username}
    };
    qDebug()<<"BagWidget发出请求："<<json<<endl;
    tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
}

void BagWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(BAGWIDGET_PATH);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //绘制用户金币数量
    QPixmap frame;
    frame.load(FRAME_PATH);
    painter.drawPixmap(this->width() * 0.8 - frame.width() * 0.5, 35, frame);
    QPixmap coin;
    coin.load(COIN_PATH);
    painter.drawPixmap(this->width() * 0.75 - coin.width() * 0.5, 30, coin);
    //绘制用户金币数字
    QFont font2("宋体",13,QFont::Bold,false);
    painter.setFont(font2);
    painter.setPen(Qt::black);
    QString smoney = QString::number(money);
    painter.drawText(this->width() * 0.8 - frame.width() * 0.5 + coin.width(), 15 + frame.height(), smoney);
    qDebug()<<"money"<<smoney<<endl;
}
BagWidget::~BagWidget()
{
    delete ui;
    delete list;
    delete spiritInfo;
    delete tcpSocket;
}
