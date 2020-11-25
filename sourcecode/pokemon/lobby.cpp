#include "lobby.h"
#include "ui_lobby.h"
Lobby::Lobby(QTcpSocket *_tcpSocket, QWidget *parent ) :
    QWidget(parent),
    ui(new Ui::Lobby)
{
    ui->setupUi(this);
    tcpSocket = _tcpSocket;
    userList = new UserList(tcpSocket);
    bagWidget = new BagWidget(tcpSocket);
    fightWidget = new FightWidget(tcpSocket);
    chooseWidget = new Choose(tcpSocket);


    //配置场景
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowFlags(Qt::FramelessWindowHint);


    //退出按钮
    MyPushButton *exitBtn = new MyPushButton(EXIT_PATH);
    exitBtn->setParent(this);
    exitBtn->move( 1200, 20);

    //右侧四按钮
    //用户列表
    MyPushButton *usersBtn = new MyPushButton(USERS_PATH);
    usersBtn->setParent(this);
    usersBtn->move( this->width() * 0.9, this->height() * 0.3);
    //背包
    MyPushButton *bagBtn = new MyPushButton(BAG_PATH);
    bagBtn->setParent(this);
    bagBtn->move( this->width() * 0.9, this->height() * 0.45);
    //战役
    MyPushButton *fightBtn = new MyPushButton(FIGHT_PATH);
    fightBtn->setParent(this);
    fightBtn->move( this->width() * 0.9, this->height() * 0.6);
    //竞技
    MyPushButton *vsBtn = new MyPushButton(VS_PATH);
    vsBtn->setParent(this);
    vsBtn->move( this->width() * 0.9, this->height() * 0.75);

    //信号和槽
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));//退出按钮
    connect(usersBtn, SIGNAL(clicked()), this, SLOT(showUserList()));//弹出用户列表
    connect(bagBtn, SIGNAL(clicked()), this, SLOT(switchBagwidget()));//背包按钮
    connect(fightBtn, SIGNAL(clicked()), this, SLOT(switchChoose()));//战役按钮
    connect(fightBtn, SIGNAL(clicked()), chooseWidget, SLOT(clearList()));
    connect(fightBtn, SIGNAL(clicked()), this, SLOT(setFight()));//点击升级赛按钮，设置对战为升级赛模式
    connect(vsBtn, SIGNAL(clicked()), this, SLOT(switchChoose()));//竞技按钮
    connect(vsBtn, SIGNAL(clicked()), this, SLOT(setVs()));//点击决斗赛，设置对战为决斗模式
    connect(userList, SIGNAL(closed()), this, SLOT(reconnect()));//关闭用户列表之后重新接收服务器传来的信息
    connect(bagWidget, SIGNAL(closed()), this, SLOT(reconnect()));//关闭背包窗口后重新接收服务器传来的信息
    connect(bagWidget, SIGNAL(closed()), this, SLOT(show()));
    connect(chooseWidget, SIGNAL(closed()), this, SLOT(show()));
    connect(chooseWidget, SIGNAL(closed()), this, SLOT(reconnect()));

}

void Lobby::consult()
{
    //向服务器查询用户信息
    QJsonObject json  = {
        {"define", LOBBY},
        {"socketID", ma.socketID},
        {"username", ma.username},
    };

    tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
}

void Lobby::setVs()
{
    ma.vs = true;
}

void Lobby::setFight()
{
    ma.vs = false;
}

void Lobby::switchChoose()
{
    bool flag = tcpSocket->disconnect();
    //bool flag = disconnect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromHost()));
    if(flag == true)
    {
        qDebug()<<"Lobby断开与服务器的连接"<<endl;
    }
    else
    {
        qDebug()<<"Lobby未能断开与服务器的连接"<<endl;
    }
    //延时进入
    //QTimer::singleShot(200, this, [=]{
        //this->close();
        chooseWidget->reconnect();
        chooseWidget->consult();
        chooseWidget->show();
    //});
}

//打开用户列表
void Lobby::showUserList()
{
    bool flag = tcpSocket->disconnect();
    if(flag == true)
    {
        qDebug()<<"Lobby释放与服务器的连接"<<endl;
    }
    else
    {
        qDebug()<<"Lobby未释放与服务器的连接"<<endl;
    }
    userList->reconnect();//userList与服务器连接
    userList->consult();//userlist向服务器查询信息
    userList->show();//userlist出现


}

void Lobby::reconnect()
{
    bool flag = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromServer()));
    if(flag == true)
    {
        qDebug()<<"Lobby与服务器连接"<<endl;
    }
    else
    {
        qDebug()<<"***Lobby未能与服务器连接"<<endl;
    }
    consult();//查询信息
    update();
}

void Lobby::receiveFromServer()
{
    //从通信套接字中取出内容
    QByteArray array = tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    qDebug()<<"lobby收到服务器："<<json<<endl;
    if(json["socketID"] != ma.socketID)
    {
        return;
    }
    if(json["define"] == LOBBY_SUCCEED)
    {
        //获取用户信息
        money = json["money"].toInt();
        spirit_num = json["spirit_num"].toInt();
        gspirit_num = json["gspirit_num"].toInt();
        qDebug()<<money<<spirit_num<<gspirit_num<<endl;
    }
    else
    {

    }
    update();
}

void Lobby::switchBagwidget()
{
    bool flag = tcpSocket->disconnect();
    if(flag == true)
    {
        qDebug()<<"Lobby断开与服务器的连接"<<endl;
    }
    else
    {
        qDebug()<<"Lobby未能断开与服务器的连接"<<endl;
    }
    //延时进入
    //QTimer::singleShot(200, this, [=]{
        //this->close();
        bagWidget->reconnect();
        bagWidget->consult();
        bagWidget->show();
    //});
}
void Lobby::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(LOBBY_PATH);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    QPixmap zhi;
    zhi.load(ZHI_PATH);
    painter.drawPixmap(this->width() * 0.5 - zhi.width() * 0.5, this->height() * 0.2, zhi);

    ui->label->setText(ma.username);

//    //绘制用户金币数量
//    QPixmap frame;
//    frame.load(FRAME_PATH);
//    painter.drawPixmap(this->width() * 0.8 - frame.width() * 0.5, 35, frame);
//    QPixmap coin;
//    coin.load(COIN_PATH);
//    painter.drawPixmap(this->width() * 0.75 - coin.width() * 0.5, 30, coin);

//    //绘制用户金币数字
//    QFont font2("宋体",13,QFont::Bold,false);
//    painter.setFont(font2);
//    painter.setPen(Qt::black);
//    QString smoney = QString::number(money);
//    painter.drawText(this->width() * 0.8 - frame.width() * 0.5 + coin.width(), 15 + frame.height(), smoney);



    //绘制用户星级
    QPixmap num;
    num.load(NUM_PATH);
    painter.drawPixmap(this->width() * 0.1 - num.width() * 0.5, this->height() * 0.8, num);
    QPixmap good;
    good.load(GOOD_PATH);
    painter.drawPixmap(this->width() * 0.1 - good.width() * 0.5, this->height() * 0.9, good);
    //绘制宠物个数勋章
    QPixmap star1;
    if(spirit_num >= 15)
    {
        star1.load(ST_PATH);
    }
    else if(spirit_num < 15 && spirit_num >= 8)
    {
        star1.load(ND_PATH);
    }
    else
    {
        star1.load(RD_PATH);
    }
    painter.drawPixmap(this->width() * 0.2 - star1.width() * 0.5, this->height() * 0.8, star1);
    //绘制高级宠物勋章
    QPixmap star2;
    if(gspirit_num >= 15)
    {
        star2.load(ST_PATH);
    }
    else if(gspirit_num < 15 && gspirit_num >= 8)
    {
        star2.load(ND_PATH);
    }
    else
    {
        star2.load(RD_PATH);
    }
    painter.drawPixmap(this->width() * 0.2 - star2.width() * 0.5, this->height() * 0.9, star2);
}
Lobby::~Lobby()
{
    delete ui;
    delete userList;
    delete bagWidget;
    delete fightWidget;
    delete chooseWidget;
    delete tcpSocket;
}

//点击登出按钮
void Lobby::on_pushButton_clicked()
{

    //向服务器发通知，下线
    QJsonObject json={
        {"define", SIGNOUT},
        {"user_ID", ma.userID}
    };
    tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());

    bool flag = tcpSocket->disconnect();
    if(flag == true)
    {
        qDebug()<<"Lobby->Login"<<endl;
    }
    else
    {
        qDebug()<<"Lobby->Lobin failed"<<endl;
    }
    emit closed();
    this->close();

}
