#include "fightwidget.h"
#include "ui_fightwidget.h"

FightWidget::FightWidget(QTcpSocket *_tcpSocket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FightWidget)
{
    ui->setupUi(this);
    tcpSocket = _tcpSocket;
    result = new ResultWidget(tcpSocket);

    //配置场景
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowFlags(Qt::FramelessWindowHint);

    //connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));//点击关闭按钮
    //返回按钮
    MyPushButton *retBtn = new MyPushButton(RET_PATH);
    retBtn->setParent(this);
    retBtn->move( 20, 20);

    connect(retBtn, SIGNAL(clicked()), this, SLOT(switchLobby()));//点击返回按钮
    connect(result, SIGNAL(closed()), this, SLOT(reconnect()));
}

void FightWidget::switchLobby()
{
    bool flag = tcpSocket->disconnect();//与服务器断开连接
    if(flag == true)
    {
        qDebug()<<"BagWidget断开与服务器连接"<<endl;
    }
    else
    {
        qDebug()<<"BagWidget未能断开与服务器连接"<<endl;
    }
    //延时进入
    QTimer::singleShot(200, this, [=]{
        this->close();
        emit closed();
    });

}

void FightWidget::consult()
{
    qDebug()<<"ID分别为"<<ma.mID<<"    "<<ma.sID<<endl;
    QJsonObject json  = {
        {"define", FIGHT_USER},
        {"socketID", ma.socketID},
        {"username", ma.username},
        {"mID", ma.mID},
        {"sID", ma.sID},
    };
    tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
}

void FightWidget::paintEvent(QPaintEvent *event)
{
    //绘制背景图
    QPainter painter(this);
    pix.load(FIGHT1);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //绘制左右两边上方的信息栏
    QPixmap hpl;//左边的信息栏
    QPixmap hpr;//右边的信息栏
    hpl.load(HP_LEFT);
    hpr.load(HP_RIGHT);
    painter.drawPixmap(50, 50, hpl);
    painter.drawPixmap(1230 - hpr.width(), 50, hpr);
}

void FightWidget::fight(Pokemon *mPokemon, Pokemon *sPokemon)
{
    int flag = 0;
    int minterval = mPokemon->getInterval();//获取玩家的攻击间隔
    int sinterval = sPokemon->getInterval();//获取服务器的攻击间隔
    int count = 0;//回合
    int turn = 0;//轮次，turn=0轮到玩家，turn=1轮到服务器
    //绘制小精灵名字
    ui->label_3->setText(mPokemon->getName());
    ui->label_4->setText(sPokemon->getName());
    //绘制hp条
    ui->progressBar->setRange(0, mPokemon->getHp());
    ui->progressBar->setRange(0, mPokemon->getHp());
    ui->progressBar->setValue(mPokemon->getHp());
    ui->progressBar->setValue(sPokemon->getHp());

    //清空攻击框
    ui->label_7->setText("");
    ui->label_8->setText("");
    ui->label_9->setText("");
    ui->label_10->setText("");
    srand((unsigned)time(NULL));
    while(flag == 0)
    {    
        //轮到玩家
        if(turn % 2 == 0)
        {
            //进入下一回合
            count++;
            //过了一个玩家的攻击间隔，则玩家攻击
            if(count % minterval == 0)
            {
                Sleep(500);//延时
                qDebug() << "-------第" << count << "回合" << endl;
                qDebug() << "玩家hp:" << mPokemon->getHp() << endl;
                qDebug() << "服务器hp:" << sPokemon->getHp() << endl;
                int i = rand() % 10;//获取一随机数
                //玩家攻击，服务器闪避
                if (i < 2)
                {
                    qDebug() << "*******玩家攻击，服务器闪避" << endl;
                }
                //玩家暴击
                else if (i > 6)
                {
                    qDebug() << "*******玩家暴击" << endl;
                    qDebug() << "对方hp-10" << endl;
                    mPokemon->attack(sPokemon);
                    sPokemon->setHp(sPokemon->getHp() - 10);
                }
                //玩家攻击
                else
                {
                    qDebug() << "*******玩家攻击" << endl;
                    mPokemon->attack(sPokemon);
                }
                    sinterval = sPokemon->getInterval();//重新获取服务器攻击间隔
            }
        }
        else
        {
            //服务器攻击
            if(count % sinterval == 0)
            {
                Sleep(500);//延时
                qDebug() << "-------第" << count << "回合" << endl;
                qDebug() << "玩家hp:" << mPokemon->getHp() << endl;
                qDebug() << "服务器hp:" << sPokemon->getHp() << endl;
                int i = rand() % 10;//获取一随机数
                //服务器攻击，玩家闪避
                if (i < 2)
                {
                    qDebug() << "*******服务器攻击,玩家闪避" << endl;
                }
                //服务器暴击
                else if (i > 6)
                {
                    qDebug() << "*******服务器暴击" << endl;
                    qDebug() << "对方hp-10" << endl;
                    sPokemon->attack(mPokemon);
                    mPokemon->setHp(mPokemon->getHp() - 10);
                }
                //服务器攻击
                else
                {
                    qDebug() << "*******服务器攻击" << endl;
                    sPokemon->attack(mPokemon);
                }
                    minterval = mPokemon->getInterval();//重新获取玩家攻击间隔

            }

        }
        turn++;

        //判断胜负
        if(sPokemon->isDead() == true)//赢
        {
            flag += 1;
            ma.win = true;
            ui->progressBar_2->setValue(0);//设置hp显示为0
        }
        else
        {
            ui->progressBar_2->setValue(sPokemon->getHp());//设置hp显示正常值
        }
        if(mPokemon->isDead() == true)
        {
            ma.win = false;
            flag += 1;
            ui->progressBar->setValue(0);//设置hp显示为0

        }
        else
        {
            ui->progressBar->setValue(mPokemon->getHp());//设置hp显示为
        }
    }

    //弹出框

    if(flag == 1)
    {
        QString define;
        if(sPokemon->isDead() == true)//赢
        {
            ma.win = 1;
            qDebug()<<"赢"<<endl;


        }
        else//输
        {
            qDebug()<<"输"<<endl;
            qDebug()<<"ma.vs"<<ma.vs<<endl;
            ma.win = -1;
            //弹出输框

            //向服务器发送数据,如果是vs模式则丢去小精灵，
            //用户：改变用户总比赛场数，胜利场数

        }
        bool flag = tcpSocket->disconnect();
        if(flag == true)
        {
            qDebug()<<"fightWidget与服务器断开连接"<<endl;
        }
        else
        {
            qDebug()<<"fightWidget未能与服务器断开连接"<<endl;
        }

        result->reconnect();//连接服务器
        result->sendInfo();//发送结果
        result->show();
        result->update();//重新绘制result窗口图像
    }
    else
    {
        ma.win = 0;
        qDebug()<<"平局"<<endl;
        //弹出平局框
        result->show();
        result->update();
    }

}

void FightWidget::reconnect()
{
    bool flag = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromHost()));//收到服务器回复
    if(flag == true)
    {
        qDebug()<<"FightWidget连接服务器"<<endl;
    }
    else
    {
        qDebug()<<"FightWidget未能连接服务器"<<endl;
    }
}

void FightWidget::receiveFromHost()
{
    QByteArray array = tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    qDebug()<<"FightWidget收到服务器："<<json<<endl;
    if(json["socketID"] != ma.socketID)
    {
        return;
    }
    if(json["define"] == FIGHT_USER)
    {
        QPixmap mpix, spix;
        //创建玩家小精灵和服务器小精灵对象
        QJsonObject tem = json["mjson"].toObject();
        QString mName = tem["spirit_name"].toString();
        //获取玩家小精灵信息
        int grade = tem["grade"].toInt();
        int attack = tem["attack"].toInt();
        int exp = tem["exp"].toInt();
        int hp = tem["hp"].toInt();
        int interval = tem["interval"].toInt();
        int defend = tem["defend"].toInt();
        int evolved = tem["evolved"].toInt();
        int skillEvolved = tem["skillEvolved"].toInt();
        Pokemon *mPokemon = NULL, *sPokemon = NULL;
        ui->label_5->setText(QString::number(grade));
        //创建玩家小精灵对象
        mPokemon = construct(mName, grade, evolved, exp, attack, defend, hp, interval, skillEvolved);
        //加载图片
        if(evolved == 1)
        {
            mpix.load(ma.bb_fmap[mName]);
        }
        else
        {
            mpix.load(ma.sb_fmap[mName]);
        }


        tem = json["sjson"].toObject();
        //获取服务器小精灵信息
        QString sName = tem["spirit_name"].toString();
        spix.load(ma.bfmap[sName]);
        grade = tem["grade"].toInt();
        attack = tem["attack"].toInt();
        exp = tem["exp"].toInt();
        hp = tem["hp"].toInt();
        interval = tem["interval"].toInt();
        defend = tem["defend"].toInt();
        evolved = tem["evolved"].toInt();
        ui->label_6->setText(QString::number(grade));
        //创建服务器小精灵对象
        sPokemon = construct(sName, grade, evolved, exp, attack, defend, hp, interval, skillEvolved);
        if(evolved == 1)
        {
            spix.load(ma.bf_fmap[sName]);
        }
        else
        {
            spix.load(ma.sf_fmap[sName]);
        }
        skillEvolved = tem["skillEvolved"].toInt();

        //绘制小精灵图像
        ui->label->setPixmap(mpix);
        ui->label->setFixedSize(mpix.width(), mpix.height());
        ui->label_2->setPixmap(spix);
        ui->label_2->setFixedSize(spix.width(), spix.height());

        //判断胜负
        fight(mPokemon, sPokemon);


    }
    else
    {

    }

}

Pokemon * FightWidget::construct(QString spiritName, int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved)
{
    Pokemon *tem = NULL;
    if(spiritName == "独角兽")
    {
        tem = new Horse(_grade, _evolved, _exp, _attack, _defend, _hp, _interval, _skillEvolved);
    }
    else if(spiritName == "石锤犀牛")
    {
        tem = new Ox(_grade, _evolved, _exp, _attack, _defend, _hp, _interval, _skillEvolved);
    }
    else if(spiritName == "紫鬃龙")
    {
        tem = new Dragon(_grade, _evolved, _exp, _attack, _defend, _hp, _interval, _skillEvolved);
    }
    else if(spiritName == "派大星")
    {
        tem = new Star(_grade, _evolved, _exp, _attack, _defend, _hp, _interval, _skillEvolved);
    }
    else if(spiritName == "石盾牌")
    {
        tem = new Rock(_grade, _evolved, _exp, _attack, _defend, _hp, _interval, _skillEvolved);
    }
    else if(spiritName == "冰蜗牛")
    {
        tem = new Snail(_grade, _evolved, _exp, _attack, _defend, _hp, _interval, _skillEvolved);
    }
    else if(spiritName == "咕咕鸡")
    {
        tem = new Bird(_grade, _evolved, _exp, _attack, _defend, _hp, _interval, _skillEvolved);
    }
    else if(spiritName == "海马先生")
    {
        tem = new Haima(_grade, _evolved, _exp, _attack, _defend, _hp, _interval, _skillEvolved);
    }
    else
    {

    }
    return tem;
}

FightWidget::~FightWidget()
{
    delete ui;
    delete tcpSocket;
}
