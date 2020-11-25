#include "widget.h"
#include"config.h"
#include "ui_widget.h"
#include"mypushbutton.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    qDebug()<<"创建开始界面"<<endl;
    ui->setupUi(this);
    tcpSocket = NULL;
    tcpSocket = new QTcpSocket(this);
    //获取服务器ip和端口
    QString ip = "127.0.0.1";
    qint16 port = 8888;
    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip), port);

    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(":/ziyuan/button/1st.png"));
    setWindowFlags(Qt::FramelessWindowHint);

    //开始按钮
    MyPushButton *startBtn = new MyPushButton(STARTBTN0);
    startBtn->setParent(this);
    startBtn->move( this->width() * 0.5 - startBtn->width()*0.5, this->height() * 0.7);

    //退出按钮
    MyPushButton *exitBtn = new MyPushButton(EXIT_PATH);
    exitBtn->setParent(this);
    exitBtn->move( 1200, 20);

    login = new Login(tcpSocket);//实例化登陆场景
    connect(startBtn, SIGNAL(clicked()), this, SLOT(switchLogin()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));
    //收到服务器回复
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromServer()));

}
//切换到登陆界面
void Widget::switchLogin()
{
    //延时进入
    QTimer::singleShot(200, this, [=]{
        this->hide();
        login->show();
    });

}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(BACKGROUND_PATH);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

void Widget::receiveFromServer()
{
    //从通信套接字中取出内容
    QByteArray array = tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    ma.socketID = json["socketID"].toInt();
    qDebug()<<"socketID:"<<ma.socketID<<endl;
}

Widget::~Widget()
{
    delete ui;
    delete tcpSocket;
    delete login;
}

