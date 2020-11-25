#include "userinfo.h"
#include "ui_userinfo.h"

UserInfo::UserInfo(QTcpSocket *_tcpSocket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfo)
{
    ui->setupUi(this);
    tcpSocket = _tcpSocket;
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    pix.load(USERINFO_PATH);
    this->resize(pix.size());

    //绘制关闭按钮
    MyPushButton *exitBtn = new MyPushButton(EXIT2_PATH);
    exitBtn->setParent(this);
    exitBtn->move( this->width() * 0.92, this->height() * 0.01);

    //设置list格式
    ui->listWidget->setFixedSize(550, 250);
    ui->listWidget->setStyleSheet("background-color:transparent");//设置背景色为透明
    ui->listWidget->setFrameShape(QListWidget::NoFrame);
    ui->listWidget->move(30, 90);
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//屏蔽垂直滑动条

    connect(exitBtn, SIGNAL(clicked()), this, SLOT(closeInfo()));//点击退出按钮

}

void UserInfo::closeInfo()
{
    emit closed();
    bool flag = tcpSocket->disconnect();//与服务器断开连接
    //清空列表
    int counter =ui->listWidget->count();
    for(int index = 0; index < counter; index++)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(0);
        ui->listWidget->removeItemWidget(item);
        delete item;
    }
    if(flag == true)
    {
        qDebug()<<"UserInfo与服务器断开连接"<<endl;
    }
    else
    {
        qDebug()<<"UserInfo未能与服务器断开连接"<<endl;
    }
    this->close();
}

void UserInfo::reconnect()
{

    bool flag = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromHost()));//收到服务器回复
    if(flag == true)
    {
        qDebug()<<"UserInfo连接服务器"<<endl;
    }
    else
    {
        qDebug()<<"UserInfo未能连接服务器"<<endl;
    }
}


void UserInfo::consult(QString username)
{
    //向服务器查询所有用户信息
    QJsonObject json  = {
        {"define", USERINFO},
        {"username", username}
    };
    qDebug()<<"UserInfo发出请求："<<json<<endl;
    tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
}

void UserInfo::receiveFromHost()
{
    QByteArray array = tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    qDebug()<<"userInfo收到服务器:"<<json<<endl;
    if(json["socketID"] != ma.socketID)
    {
        return;
    }
    //处理用户信息
    QString username = json["username"].toString();
    qDebug()<<"username:"<<username<<endl;
    QFont font1("微软雅黑",13);
    QFont font2("微软雅黑",13);
    QFont font3("微软雅黑",13);
    QFont font4("微软雅黑",13);
    QString online;
    if(json["online"] == 1)
    {
        online = "在线";

    }
    else
    {
        online = "离线";

    }
    QString win_rate = "胜率：" + QString::number(json["win_rate"].toDouble()) + "%";
    QString grade = "等级：" + QString::number(json["grade"].toInt());

    //显示用户信息
    ui->label->setText(username);
    ui->label->setFont(font1);
    ui->label_2->setText(online);
    ui->label_2->setFont(font2);
    ui->label_3->setText(win_rate);
    ui->label_3->setFont(font3);
    ui->label_4->setText(grade);
    ui->label_4->setFont(font4);

    //设置对齐方式
    ui->label->setAlignment(Qt::AlignHCenter);
    ui->label_2->setAlignment(Qt::AlignHCenter);
    ui->label_3->setAlignment(Qt::AlignHCenter);
    ui->label_4->setAlignment(Qt::AlignHCenter);

    int spirit_num = json["spirit_num"].toInt();
    int gspirit_num = json["gspirit_num"].toInt();
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
    ui->label_6->setPixmap(star1);
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
    ui->label_8->setPixmap(star2);

    //处理宠物信息
    QJsonArray  spirits(json["spirits"].toArray());
    int num = spirits.size();//宠物个数
    for(int i = 0; i < num; i++)
    {
        QJsonObject tem = spirits[i].toObject();
        QString spirit_name = tem["spirit_name"].toString();

        int evolved = tem["evolved"].toInt();
        QString grade = QString::number(tem["grade"].toInt());
        ListItem *newItem = new ListItem(this, spirit_name, grade, evolved);
        QListWidgetItem *item0 = new QListWidgetItem();
        item0->setSizeHint(QSize(140, 170));
        ui->listWidget->addItem(item0);
        ui->listWidget->setItemWidget(item0, newItem);

    }
}

void UserInfo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}

UserInfo::~UserInfo()
{
    delete ui;
    delete tcpSocket;
}
