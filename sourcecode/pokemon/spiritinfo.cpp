#include "spiritinfo.h"
#include "ui_spiritinfo.h"

SpiritInfo::SpiritInfo(QTcpSocket *_tcpSocket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpiritInfo)
{
    ui->setupUi(this);
    tcpSocket = _tcpSocket;
    pix.load(SPIRITINFO_PATH);
    this->resize(pix.size());
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }");
    //绘制关闭按钮
    MyPushButton *exitBtn = new MyPushButton(EXIT2_PATH);
    exitBtn->setParent(this);
    exitBtn->move( this->width() * 0.95, this->height() * 0.01);
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(closeInfo()));//点击退出按钮


}

SpiritInfo::~SpiritInfo()
{
    delete ui;
    delete tcpSocket;
}

void SpiritInfo::closeInfo()
{
    bool flag = tcpSocket->disconnect();
    if(flag == true)
    {
        qDebug()<<"spiritInfo断开与服务器连接"<<endl;
    }
    else
    {
        qDebug()<<"spiritInfo未能断开与服务器连接"<<endl;
    }
    emit closed();
    this->close();
}

void SpiritInfo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}

void SpiritInfo::consult(int id)
{
    spirit_ID = id;
    //向服务器查询所有精灵信息
    QJsonObject json  = {
        {"define", SPIRINTINFO},
        {"socketID", ma.socketID},
        {"spirit_ID", id}
    };
    qDebug()<<"spiritInfo发出请求："<<json<<endl;
    tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
}

void SpiritInfo::receiveFromHost()
{
    QByteArray array = tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    qDebug()<<"spiritInfo收到服务器:"<<json<<endl;
    if(json["socketID"] != ma.socketID)
    {
        return;
    }
    if(json["define"] == SPIRINTINFO)
    {
        //获取小精灵信息
        money = json["money"].toInt();//金钱
        qDebug()<<"%%%money"<<money<<endl;
        spirit_name = json["spirit_name"].toString();
        spirit_type = json["spirit_type"].toInt();
        grade = json["grade"].toInt();
        evolved = json["evolved"].toInt();
        exp = json["exp"].toInt();
        attack = json["attack"].toInt();
        defend = json["defend"].toInt();
        hp = json["hp"].toInt();
        interval = json["interval"].toInt();
        skillEvolved = json["skillEvolved"].toInt();

        //在界面上显示小精灵信息
        ui->label->setText(spirit_name);
        ui->label_2->setText("Level:"+QString::number(grade));
        ui->label_4->setText(QString::number(exp));
        ui->label_6->setText(QString::number(attack));
        ui->label_8->setText(QString::number(defend));
        ui->label_12->setText(QString::number(hp));
        ui->label_14->setText(QString::number(interval));
        //技能框
        ui->label_19->setText("一级技能："+ma.skill[spirit_name]);
        ui->label_20->setText("二级技能："+ma.sskill[spirit_name]);

        QPixmap pix, pix2, pix3;
        if(evolved == 1)
        {
            qDebug()<<"已进化"<<endl;
            pix.load(ma.bfmap[spirit_name]);
        }
        else
        {
            qDebug()<<"未进化"<<endl;
            pix.load(ma.sfmap[spirit_name]);
        }
        ui->label_18->setPixmap(pix);
        ui->label_18->setFixedSize(pix.size());
        pix2.load(ma.sfmap[spirit_name]);
        pix3.load(ma.bfmap[spirit_name]);
        ui->label_9->setPixmap(pix2);
        ui->label_9->setFixedSize(pix.size());
        ui->label_10->setPixmap(pix3);
        ui->label_10->setFixedSize(pix.size());
    }
    else if(json["define"] == SPIRIT_UP)
    {

        QPixmap pix;
        pix.load(ma.bfmap[spirit_name]);
        //更新图像
        ui->label_18->setPixmap(pix);
        ui->label_18->setFixedSize(pix.size());

    }
    else if(json["define"] == SKILL_UP)
    {

    }
    else
    {

    }

}

void SpiritInfo::reconnect()
{
    bool flag = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromHost()));//收到服务器回复
    if(flag == true)
    {
        qDebug()<<"spiritInfo连接服务器"<<endl;
    }
    else
    {
        qDebug()<<"spiritInfo未能连接服务器"<<endl;
    }
}

//点击小精灵进化按钮
void SpiritInfo::on_pushButton_clicked()
{
    if(money >= 500 && evolved == false)
    {
        money -= 500;//更新钱
        //qDebug()<<"%%%money"<<money<<endl;
        evolved = true;//更新进化
        QJsonObject json  = {
            {"define", SPIRIT_UP},
            {"socketID", ma.socketID},
            {"spirit_ID", spirit_ID},
            {"user_ID", ma.userID},
            {"money", money}
        };
        qDebug()<<"spiritInfo发出请求："<<json<<endl;
        tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    }
    //如果用户钱不够
    else if(money < 500)
    {
        qDebug()<<"钱不够，请努力赚钱"<<endl;
        QMessageBox::critical(this, "提示", "金币不够，请努力赚金币！");
    }
    //如果小精灵已进化
    else
    {
        qDebug()<<"已进化"<<endl;
        QMessageBox::critical(this, "提示", "小精灵已进化");
    }
}

void SpiritInfo::on_pushButton_2_clicked()
{
    if(money >= 400 && skillEvolved == false)
    {
        money -= 400;//更新钱
        qDebug()<<"%%%money"<<money<<endl;
        skillEvolved = true;//更新进化
        QJsonObject json  = {
            {"define", SKILL_UP},
            {"socketID", ma.socketID},
            {"spirit_ID", spirit_ID},
            {"user_ID", ma.userID},
            {"money", money}
        };
        qDebug()<<"技能升级："<<json<<endl;
        tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    }
    else if(money < 400)
    {
        qDebug()<<"钱不够，请努力赚钱"<<endl;
        QMessageBox::critical(this, "提示", "金币不够，请努力赚金币！");
    }
    else
    {
        qDebug()<<"已升级"<<endl;
        QMessageBox::critical(this, "提示", "小精灵技能已升级");
    }
}
