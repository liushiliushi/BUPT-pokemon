#include "login.h"
#include "ui_login.h"

Login::Login(QTcpSocket *_tcpSocket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    qDebug()<<"创建登陆窗口"<<endl;
    ui->setupUi(this);
    tcpSocket = _tcpSocket;
    lobby = new Lobby(tcpSocket);
    //配置场景
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowFlags(Qt::FramelessWindowHint);

    //登录框配置

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);//设置密码不显示

    //退出按钮
    MyPushButton *exitBtn = new MyPushButton(EXIT_PATH);
    exitBtn->setParent(this);
    exitBtn->move( 1200, 20);

    //点击登陆
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(LogIn()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));
    //收到服务器回复
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromServer()));

    //登出时
    connect(lobby, SIGNAL(closed()), this, SLOT(reconnect()));//lobby重新接收服务器传来的信息
    connect(lobby, SIGNAL(closed()), this, SLOT(show()));//显示lobby
}

void Login::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(LOG_PATH);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

void Login::reconnect()
{
    bool flag = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromServer()));

    if(flag == true)
    {
        qDebug()<<"Login与服务器连接"<<endl;
    }
    else
    {
        qDebug()<<"Login未能与服务器连接"<<endl;
    }

}

void Login::receiveFromServer()
{
    //从通信套接字中取出内容
    QByteArray array = tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    //QJsonObject json = ma.receiveFromServer();
    qDebug()<<"login收到服务器："<<json<<endl;
    if(json["socketID"] != ma.socketID)
    {
        return;
    }
    //密码正确
    if(json["define"] == LOGIN_SUCCEED)
    {
        qDebug() << "进入游戏大厅" << endl;
        ma.username = json["username"].toString();
        ma.userID = json["userID"].toInt();
        qDebug()<<"ma.username:"<<ma.username<<endl;
        //延时进入
        QTimer::singleShot(200, this, [=]{
            //this->close();
            //this->hide();
            qDebug()<<"Login释放与服务器连接"<<endl;
            disconnect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromServer()));//解除连接
//            lobby = new Lobby(tcpSocket);
            lobby->reconnect();//lobby连接服务器
            lobby->show();
            lobby->update();
        });

    }
    //密码错误
    else if(json["define"] == LOGIN_FAILED)
    {
        QMessageBox::critical(this, "错误", "密码错误，请重新输入");
    }
    //用户名重复
    else if(json["define"] == SIGNIN_FAILED)
    {
        QMessageBox::critical(this, "错误", "用户名已存在");

    }
    //注册成功
    else if(json["define"] == SIGNIN_SUCCEED)
    {
        QMessageBox::information(this, "提示", "注册成功");
    }


}

void Login::LogIn()
{
    QString name = ui->lineEdit->text().toUtf8().data();//获取用户名
    QString passWord = ui->lineEdit_2->text();//获取密码
    if(name == "")
    {
        QMessageBox::critical(this, "错误", "请输入用户名");
        return;
    }
    //如果未输入密码，
    if(passWord == "")
    {
        QMessageBox::critical(this, "错误", "请输入密码");
        return;
    }
    QJsonObject json  = {
        {"define", LOGIN},
        {"socketID", ma.socketID},
        {"username", name},
        {"password", passWord}
    };
    //向服务器发送信息
    tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
}

Login::~Login()
{
    delete ui;
    delete tcpSocket;
    delete lobby;
}



void Login::on_pushButton_2_clicked()
{
    QString name = ui->lineEdit->text().toUtf8().data();//获取用户名
    QString passWord = ui->lineEdit_2->text();//获取密码
    //如果未输入用户名
    if(name == "")
    {
        QMessageBox::critical(this, "错误", "请输入用户名");
        return;
    }
    //如果未输入密码，
    if(passWord == "")
    {
        QMessageBox::critical(this, "错误", "请输入密码");
        return;
    }
    QJsonObject json  = {
        {"define", SIGNIN},
        {"socketID", ma.socketID},
        {"username", name},
        {"password", passWord}
    };

    tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());


}
