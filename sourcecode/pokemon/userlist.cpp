#include "userlist.h"
#include "ui_userlist.h"

UserList::UserList(QTcpSocket *_tcpSocket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserList)
{
    ui->setupUi(this);
    tcpSocket = _tcpSocket;
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    pix.load(USERLIST_PATH);
    this->resize(pix.size());

    //建立用户信息窗口
    userInfo = new UserInfo(tcpSocket);


    //绘制关闭按钮
    MyPushButton *exitBtn = new MyPushButton(EXIT2_PATH);
    exitBtn->setParent(this);
    exitBtn->move( this->width() * 0.92, this->height() * 0.08);

    connect(exitBtn, SIGNAL(clicked()), this, SLOT(closeList()));//点击退出按钮
    //connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromServer()));//收到服务器回复
    connect(userInfo, SIGNAL(closed()), this, SLOT(reconnect()));//关闭userInfo后重新连接tcp

    //绘制列表
    list = new QListWidget(this);

    //设置list格式
    list->setFixedSize(590, 400);
    list->setSpacing(10);
    list->setStyleSheet("background-color:transparent");//设置背景色为透明
    list->setFrameShape(QListWidget::NoFrame);
    list->move(30, 90);
    list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//屏蔽垂直滑动条
}

void UserList::reconnect()
{
    bool flag = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromServer()));
    if(flag == true)
    {
        qDebug()<<"UserList与服务器连接"<<endl;
    }
    else
    {
        qDebug()<<"UserList未能与服务器连接"<<endl;
    }
}

void UserList::consult()
{
    //向服务器查询所有用户信息
    QJsonObject json  = {
        {"define", USERLIST},
        {"socketID", ma.socketID},
    };
    qDebug()<<"UserList发出请求："<<json<<endl;
    tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
}

void UserList::closeList()
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
    disconnect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromServer()));//断开tcp连接
    emit closed();//发出关闭信号
    this->close();
}

void UserList::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}

void UserList::receiveFromServer()
{
    //从通信套接字中取出内容
    QByteArray array = tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    qDebug()<<"UserList收到服务器："<<json<<endl;
    if(json["socketID"] != ma.socketID)
    {
        return;
    }
    if(json["define"] == USERLIST)
    {
        int num = json["number"].toInt();
        QJsonArray array = json["array"].toArray();
        qDebug()<<"用户总数"<<num<<endl;
        names.clear();//先清空列表
        for(int i = 0; i < num; i++)
        {
            //创建用户列表表项
            QJsonObject tem = array[i].toObject();
            QString username = tem["username"].toString();
            names.append(username);
            int online = tem["online"].toInt();
            QString grade = QString::number(tem["grade"].toInt());
            ListItem *newItem = new ListItem(this, username, online, grade);
            newItem->setIndex(i);//设置标号
            QListWidgetItem *item0 = new QListWidgetItem();
            item0->setSizeHint(QSize(550, 60));
            list->addItem(item0);
            list->setItemWidget(item0, newItem);
            connect(newItem, SIGNAL(listItemClicked(int)), this, SLOT(dealClicked(int)));
        }
    }
    else
    {

    }

}
//处理点击用户列表表项事件
void UserList::dealClicked(int index)
{
    QString username = names[index];
    qDebug()<<"选中了"<<username<<endl;
    //断开tcp连接

    bool flag = disconnect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromServer()));
    if(flag == true)
    {
        qDebug()<<"UserList释放与服务器的连接"<<endl;
    }
    else
    {
        qDebug()<<"UserList未能释放与服务器的连接"<<endl;
    }
    userInfo->show();
    userInfo->reconnect();//userinfo连接服务器
    userInfo->consult(username);//查询用户信息

}


void UserList::switchUserIfo()
{
    //延时进入
    QTimer::singleShot(200, this, [=]{
        this->hide();
        userInfo->show();
    });

}

UserList::~UserList()
{
    delete ui;
    delete list;
    delete userInfo;
}
