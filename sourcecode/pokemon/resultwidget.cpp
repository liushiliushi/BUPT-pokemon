#include "resultwidget.h"
#include "ui_resultwidget.h"

ResultWidget::ResultWidget(QTcpSocket *_tcpSocket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultWidget)
{
    ui->setupUi(this);
    tcpSocket = _tcpSocket;
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    if(ma.win == true)
    {
        if(ma.vs == true)
        {
            pix.load(WIN_VS_PATH);
        }
        else
        {
            pix.load(WIN_FIGHT_PATH);
        }

    }
    else
    {
        if(ma.vs == true)
        {
            pix.load(FAIL_VS_PATH);
        }
        else
        {
            pix.load(FAIL_FIGHT_PATH);
        }

    }
    this->resize(pix.size());

    //绘制关闭按钮
    MyPushButton *exitBtn = new MyPushButton(EXIT2_PATH);
    exitBtn->setParent(this);
    exitBtn->move( this->width() * 0.92, this->height() * 0.08);

    connect(exitBtn, SIGNAL(clicked()), this, SLOT(switchFight()));//点击退出按钮

    //设置list格式
    ui->listWidget->setFixedSize(420, 200);
    ui->listWidget->setStyleSheet("background-color:transparent");//设置背景色为透明
    ui->listWidget->setFrameShape(QListWidget::NoFrame);
    ui->listWidget->move(100, 400);
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setFlow(QListView::LeftToRight);

}

void ResultWidget::paintEvent(QPaintEvent *event)
{
    qDebug()<<"重新绘图"<<endl;
    QPainter painter(this);
    //绘制“赢”背景图
    if(ma.win == 1)
    {
        if(ma.vs == true)
        {
            pix.load(WIN_VS_PATH);
        }
        else
        {
            pix.load(WIN_FIGHT_PATH);
        }

    }
    //绘制“输”背景图
    else if(ma.win == -1)
    {
        if(ma.vs == true)
        {
            pix.load(FAIL_VS_PATH);
        }
        else
        {
            pix.load(FAIL_FIGHT_PATH);
        }

    }
    //绘制“平局”背景图
    else
    {
        pix.load(PING_PATH);
    }

    this->resize(pix.size());
    painter.drawPixmap(0,0,pix);
}

void ResultWidget::sendInfo()
{
    //向服务器发送信息
    QJsonObject json;
    if(ma.win == -1)//假如输了
    {

        if(ma.vs == true)//竞技模式
        {
            choose = false;
            json  = {
                {"define", RESULT_VS_FAIL},
                {"socketID", ma.socketID},
                {"mID", ma.mID},//传回要送走的小精灵ID
                {"userID", ma.userID}
            };
        }
        else
        {
            //什么都不做
            json  = {
                {"define", RESULT_FIGHT_FAIL},
                {"socketID", ma.socketID},
                {"mID", ma.mID},//传回要送走的小精灵ID
                {"userID", ma.userID}
            };
        }
    }
    else//赢了
    {
        if(ma.vs == 1)//竞技模式
        {
            json  = {
                {"define", RESULT_VS_WIN},
                {"socketID", ma.socketID},
                {"mID", ma.mID},//传回玩家小精灵ID
                {"sID", ma.sID},//传回要得到的小精灵ID
                {"userID", ma.userID}
            };
        }
        else
        {
            json  = {
                {"define", RESULT_FIGHT_WIN},
                {"socketID", ma.socketID},
                {"mID", ma.mID},//传回玩家小精灵ID
                {"userID", ma.userID}
            };
        }
    }

    qDebug()<<"ResultWidget发出请求："<<json<<endl;
    try {
        tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    }
    catch (QException &e)
    {
        qDebug()<<"出现异常"<<endl;
    }


}

void ResultWidget::reconnect()
{
    bool flag = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromHost()));//收到服务器回复
    if(flag == true)
    {
        qDebug()<<"resultWidget连接服务器"<<endl;
    }
    else
    {
        qDebug()<<"resultWidget未能连接服务器"<<endl;
    }
}

void ResultWidget::receiveFromHost()
{
    QByteArray array = tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    qDebug()<<"result收到服务器："<<json<<endl;
    if(json["socketID"] != ma.socketID)
    {
        return;
    }
    if(json["define"] == ADOPT)//丢弃小精灵
    {
        //处理宠物信息
        QJsonArray  spirits(json["spirits"].toArray());
        int num = spirits.size();//宠物个数
        for(int i = 0; i < num; i++)
        {
            QJsonObject tem = spirits[i].toObject();
            QString spirit_name = tem["spirit_name"].toString();
            int id = tem["spirit_ID"].toInt();//小精灵ID

            int evolved = tem["evolved"].toInt();
            QString grade = QString::number(tem["grade"].toInt());
            ListItem *newItem = new ListItem(this, spirit_name, grade, evolved);
            newItem->setIndex(id);//设置标号
            QListWidgetItem *item0 = new QListWidgetItem();
            item0->setSizeHint(QSize(140, 170));
            ui->listWidget->addItem(item0);
            ui->listWidget->setItemWidget(item0, newItem);
            connect(newItem, SIGNAL(listItemClicked(int)), this, SLOT(dealClicked(int)));
        }

    }
}

void ResultWidget::dealClicked(int id)
{
    if(choose == false)
    {
        choose = true;
        QJsonObject json;
        json = {
            {"define", ADOPTONE},
            {"socketID", ma.socketID},
            {"user_ID", ma.userID},
            {"spirit_ID", id}
        };

        tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());

    }
    else
    {
        qDebug()<<"已经丢弃了小精灵"<<endl;
    }

}

void ResultWidget::clearList()
{
    int counter = ui->listWidget->count();
    for(int index = 0; index < counter; index++)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(0);
        ui->listWidget->removeItemWidget(item);
        delete item;
    }
}

void ResultWidget::switchFight()
{
    if(choose == true)
    {
        clearList();//清空列表
        bool flag = tcpSocket->disconnect();
        if(flag == true)
        {
            qDebug()<<"ResultWidget断开与服务器连接"<<endl;
        }
        else
        {
            qDebug()<<"ResultWidget未能断开与服务器连接"<<endl;
        }
        QTimer::singleShot(200, this, [=]{
            this->close();
            emit closed();
        });
    }
    else
    {
        qDebug()<<"请先丢弃一个小精灵"<<endl;
        QMessageBox::critical(this, "提示", "请先丢弃一个小精灵");
    }

}

ResultWidget::~ResultWidget()
{
    delete ui;
    delete tcpSocket;
}
