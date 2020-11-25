#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //监听套接字，指定父对象，让他自动回收空间
    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress::Any, 8888);

    setWindowTitle("服务器端口：8888");

    connect(tcpServer, &QTcpServer::newConnection, [=](){

        //取出建立好连接的套接字
        QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
        QJsonObject json = {
            {"socketID", socketID}
        };
        socketID++;
        tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());//将socketID传给客户端
        socketList.append(tcpSocket);//将新的通信套接字加入列表中

        //获取对方的IP和端口
        QString ip = tcpSocket->peerAddress().toString();
        qint16 port = tcpSocket->peerPort();

        //QString temp = QString("[%1:%2]:成功连接").arg(ip).arg(port);

        //ui->textEdit->setText(temp);

        connect(tcpSocket, &QTcpSocket::readyRead,
                [=](){
            //从通信套接字中取出内容
            QByteArray array = tcpSocket->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
            QJsonObject json = jsonDocument.object();

            qDebug()<<"请求为"<<json["define"]<<"操作"<<endl;
            //登陆请求
            if(json["define"] == LOGIN)
            {
                qDebug()<<"登陆请求"<<endl;
                LogIn(json);
            }
            //注册请求
            else if(json["define"] == SIGNIN)
            {
                qDebug()<<"注册请求"<<endl;
                SignIn(json);
            }
            //登出请求
            else if(json["define"] == SIGNOUT)
            {
                SignOut(json);
            }
            //大厅查询信息请求
            else if(json["define"] == LOBBY)
            {
                qDebug()<<"大厅请求"<<endl;
                Lobby(json);
            }
            //用户列表查询信息请求
            else if(json["define"] == USERLIST)
            {
                qDebug()<<"用户列表请求"<<endl;
                UserList(json);
            }
            else if(json["define"] == USERINFO)
            {
                qDebug()<<"用户信息请求"<<endl;
                UserInfo(json);
            }
            else if(json["define"] == BAG)
            {
                qDebug()<<"背包请求"<<endl;
                Bag(json);
            }
            else if(json["define"] == SPIRINTINFO)
            {
                qDebug()<<"精灵信息请求"<<endl;
                SpiritInfo(json);
            }
            else if(json["define"] == SPIRIT_UP)
            {
                qDebug()<<"*精灵进化"<<endl;
                SpiritUp(json);
            }
            else if(json["define"] == SKILL_UP)
            {
                SkillUp(json);
            }
            else if(json["define"] == SPIRIT_UPGRADE)
            {

            }
            else if(json["define"] == CHOOSE)
            {
                Choose(json);
            }
            else if(json["define"] == FIGHT_USER)
            {
                FightUser(json);
            }
            else if(json["define"] == RESULT_VS_FAIL)
            {
                ResultVsFail(json);
            }
            else if(json["define"] == RESULT_FIGHT_FAIL)
            {
                ResultFightFail(json);
            }
            else if(json["define"] == RESULT_VS_WIN)
            {
                ResultVsWin(json);
            }
            else if(json["define"] == RESULT_FIGHT_WIN)
            {
                ResultFightWin(json);
            }
            else if(json["define"] == ADOPTONE)
            {
                AdoptOne(json);
            }
            else
            {
                qDebug()<<"无法识别"<<endl;
            }


        });
    });

};

void MainWindow::SignOut(QJsonObject json)
{
    qDebug()<<"登出"<<endl;
    int user_ID = json["user_ID"].toInt();
    int _socketID = json["socketID"].toInt();
    QSqlQuery query;
    QString sql;
    sql = QString("UPDATE user SET online = 0 WHERE user_ID = %1;").arg(user_ID);
    query.exec(sql);
}

void MainWindow::SpiritUpgrade(QJsonObject json)
{
    qDebug()<<"小精灵升级"<<json<<endl;
    int spirit_ID = json["spirit_ID"].toInt();
    int grade = json["grade"].toInt();
    int attack = json["grade"].toInt();
    int defend = json["defend"].toInt();
    int hp = json["hp"].toInt();
    int interval = json["interval"].toInt();
    int _socketID = json["socketID"].toInt();

    QSqlQuery query;
    QString sql;

    //给小精灵升级
    sql = QString("UPDATE spirit SET grade = %1, attack = %2, defend = %3, hp = %4, interval = %5"
                  "WHERE spirit_ID = %6;")
            .arg(grade).arg(attack).arg(defend).arg(hp).arg(interval).arg(spirit_ID);
    query.exec(sql);

}

void MainWindow::SpiritUp(QJsonObject json)
{
    qDebug()<<"小精灵进化"<<json<<endl;
    int spirit_ID = json["spirit_ID"].toInt();
    int money = json["money"].toInt();
    int user_ID = json["user_ID"].toInt();
    int _socketID = json["socketID"].toInt();

    QSqlQuery query;
    QString sql;

    //给小精灵升级
    sql = QString("UPDATE spirit SET evolved = %1 WHERE spirit_ID = %2;")
            .arg(1).arg(spirit_ID);
    query.exec(sql);
    //用户金钱--
    sql = QString("UPDATE user SET money = %1 WHERE user_ID = %2;")
            .arg(money).arg(user_ID);
    query.exec(sql);

    json  = {
        {"define", SPIRIT_UP},
        {"socketID", _socketID},
    };
    qDebug()<<"spiritInfo发出请求："<<json<<endl;
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);
}

void MainWindow::SkillUp(QJsonObject json)
{
    qDebug()<<"技能升级"<<json<<endl;
    int spirit_ID = json["spirit_ID"].toInt();
    int money = json["money"].toInt();
    int user_ID = json["user_ID"].toInt();
    int _socketID = json["socketID"].toInt();

    QSqlQuery query;
    QString sql;

    //给小精灵升级
    sql = QString("UPDATE spirit SET skillEvolved = %1 WHERE spirit_ID = %2;")
            .arg(1).arg(spirit_ID);
    query.exec(sql);
    //用户金钱--
    sql = QString("UPDATE user SET money = %1 WHERE user_ID = %2;")
            .arg(money).arg(user_ID);
    query.exec(sql);

    json  = {
        {"define", SKILL_UP},
        {"socketID", _socketID},
    };
    qDebug()<<"spiritInfo发出请求："<<json<<endl;
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);
}

void MainWindow::AdoptOne(QJsonObject json)
{
    qDebug()<<"丢弃小精灵"<<json<<endl;
    QSqlQuery query;
    int spirit_ID = json["spirit_ID"].toInt();
    int user_ID = json["user_ID"].toInt();
    int _socketID = json["socketID"].toInt();
    QString sql = QString("DELETE FROM spirit WHERE spirit_ID = %1;").arg(spirit_ID);
    query.exec(sql);

    //查询小精灵个数
    sql = QString("SELECT spirit_num FROM user WHERE user_ID = %1;").arg(user_ID);
    query.exec(sql);
    query.first();
    int spirit_num = query.value(0).toInt();
    if(spirit_num == 1)
    {

    }
    else
    {
        spirit_num--;
    }
    sql = QString("UPDATE user SET spirit_num = %1 WHERE user_ID = %2;").arg(spirit_num).arg(user_ID);
    query.exec(sql);

    //看用户是否没有小精灵了
    sql = QString("SELECT * FROM spirit WHERE user_ID = %1;").arg(user_ID);
    query.exec(sql);
    query.first();
    if(query.value(0).toInt() == NULL)
    {
        qDebug()<<"重新发一个小精灵"<<endl;
        //假如没有小精灵了，则随机发一个
        QJsonArray spirits;

        sql = QString("SELECT * FROM spirit WHERE user_ID = %1 ;").arg(0);
        query.exec(sql);
        query.first();
        int size = query.size();
        qDebug()<<"size:"<<size<<endl;
        QVector<QSqlRecord> array;
        for(int i = 0; i < size; i++)
        {

            array.append(query.record());
            query.next();
        }
        //随机分配一个小精灵
        srand((unsigned)time(NULL));
        int j = rand() % size;

        qDebug()<<"选中小精灵"<<j<<endl;
        sql = QString("INSERT INTO spirit (spirit_name,user_ID) VALUES ('%1', %2);")
                .arg(array[j].value(1).toString()).arg(user_ID);
        query.exec(sql);

    }

}

void MainWindow::ResultVsFail(QJsonObject json)
{
    qDebug()<<"result vs输"<<json<<endl;
    QSqlQuery query;
    int userID = json["userID"].toInt();
    int _socketID = json["socketID"].toInt();
    //更新用户的比赛场次、胜利场次
    QString sql = QString("SELECT all_num, win_num FROM user WHERE user_ID = %1;").arg(userID);
    query.exec(sql);
    query.first();
    int all_num = query.value(0).toInt();
    int win_num = query.value(1).toInt();
    all_num++;
    qDebug()<<"win_num"<<win_num<<endl;
    qDebug()<<"all_num"<<all_num<<endl;
    float win_rate = (float)win_num * 100 / all_num;
    qDebug()<<"胜率"<<win_rate<<endl;
    sql = QString("UPDATE user SET all_num = %1, win_num = %2, win_rate = %3 WHERE user_ID = %4;").arg(all_num).arg(win_num).arg(win_rate).arg(userID);
    query.exec(sql);

    //随机选择三个小精灵
    QJsonArray spirits;
    sql = QString("SELECT spirit_name, grade, evolved, spirit_ID FROM spirit WHERE user_ID = %1;").arg(userID);
    query.exec(sql);
    query.first();
    qDebug()<<"记录数"<<query.size()<<endl;
    if(query.size() <= 3)//用户小精灵个数小于等于3
    {
        QString spirit_name;
        int grade;
        int evolved;
        int spirit_ID;
        spirit_name = query.value(0).toString();
        grade = query.value(1).toInt();
        evolved = query.value(2).toInt();
        spirit_ID = query.value(3).toInt();
        QJsonObject spirit = {
            {"spirit_name", spirit_name},
            {"grade", grade},
            {"evolved", evolved},
            {"spirit_ID", spirit_ID}
        };
        spirits.append(spirit);
        while(query.next())
        {
            spirit_name = query.value(0).toString();
            grade = query.value(1).toInt();
            evolved = query.value(2).toInt();
            spirit_ID = query.value(3).toInt();
            QJsonObject spirit = {
                {"spirit_name", spirit_name},
                {"grade", grade},
                {"evolved", evolved},
                {"spirit_ID", spirit_ID}
            };
            spirits.append(spirit);
        }
    }
    else//用户小精灵个数大于3,随机选3个
    {
        int size = query.size();
        QVector<QSqlRecord> array;
        for(int i = 0; i < size; i++)
        {
            array.append(query.record());
            query.next();        
        }

        QString spirit_name;
        int grade;
        int evolved;
        int spirit_ID;
        srand((unsigned)time(NULL));
        for(int k = query.size(), i = 0; i < 3; i++)
        {
            int j = rand() % k;
            k--;
            qDebug()<<"选中小精灵"<<j<<endl;
            spirit_name = array[j].value(0).toString();
            grade = array[j].value(1).toInt();
            evolved = array[j].value(2).toInt();
            spirit_ID = array[j].value(3).toInt();
            QJsonObject spirit = {
                {"spirit_name", spirit_name},
                {"grade", grade},
                {"evolved", evolved},
                {"spirit_ID", spirit_ID}
            };
            spirits.append(spirit);
            array[j] = array[k];//将最后面的复制到前面
        }

    }
    json = {
        {"define", ADOPT},
        {"socketID", _socketID},
        {"spirits", spirits}
    };
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);
}

void MainWindow::ResultFightFail(QJsonObject json)
{
    qDebug()<<"result fight输"<<json<<endl;
    QSqlQuery query;
    int userID = json["userID"].toInt();
    int _socketID = json["socketID"].toInt();
    //更新用户的比赛场次、胜利场次
    QString sql = QString("SELECT all_num, win_num FROM user WHERE user_ID = %1;").arg(userID);
    query.exec(sql);
    query.first();
    int all_num = query.value(0).toInt();
    int win_num = query.value(1).toInt();
    all_num++;
    qDebug()<<"win_num"<<win_num<<endl;
    qDebug()<<"all_num"<<all_num<<endl;
    float win_rate = (float)win_num * 100 / all_num;
    qDebug()<<"胜率"<<win_rate<<endl;
    sql = QString("UPDATE user SET all_num = %1, win_num = %2, win_rate = %3 WHERE user_ID = %4;").arg(all_num).arg(win_num).arg(win_rate).arg(userID);
    query.exec(sql);


}

void MainWindow::ResultVsWin(QJsonObject json)
{
    qDebug()<<"result vs赢"<<json<<endl;
    QSqlQuery query;
    QString sql;
    int user_ID = json["userID"].toInt();
    int _socketID = json["socketID"].toInt();

    //将服务器小精灵复制一份送给用户
    int sID = json["sID"].toInt();
    sql = QString("SELECT * FROM spirit WHERE spirit_ID = %1;").arg(sID);
    query.exec(sql);
    query.first();
    sql = QString("INSERT INTO spirit (`spirit_name`, `user_ID`, `grade`, `evolved`, `exp`, `attack`, `defend`, `hp`, `interval`, `skillEvolved`) VALUES ('%1', %2, %3, %4, %5, %6, %7, %8, %9, %10);")
            .arg(query.value(1).toString()).arg(user_ID).arg(query.value(4).toInt())
            .arg(query.value(5).toInt()).arg(query.value(6).toInt()).arg(query.value(7).toInt()).arg(query.value(8).toInt())
            .arg(query.value(9).toInt()).arg(query.value(10).toInt()).arg(query.value(11).toInt());
    query.exec(sql);

    //查询小精灵个数
    sql = QString("SELECT spirit_num FROM user WHERE user_ID = %1;").arg(user_ID);
    query.exec(sql);
    query.first();
    int spirit_num = query.value(0).toInt();
    qDebug()<<user_ID<<"小精灵个数原来是"<<spirit_num<<endl;
    spirit_num++;
    sql = QString("UPDATE user SET spirit_num = %1 WHERE user_ID = %2;").arg(spirit_num).arg(user_ID);
    query.exec(sql);

    //玩家小精灵经验+
    int mID = json["mID"].toInt();
    sql = QString("SELECT exp FROM spirit WHERE spirit_ID = %1;").arg(mID);
    query.exec(sql);
    query.first();
    int exp = query.value(0).toInt();
    exp += SEXP;
    sql = QString("UPDATE spirit SET exp = %1 WHERE spirit_ID = %2;").arg(exp).arg(mID);
    query.exec(sql);

    //升级
    if(exp % 200 == 0)
    {
        qDebug()<<"升级~~~"<<endl;
        sql = QString("SELECT * FROM spirit WHERE spirit_ID = %1;").arg(mID);
        query.exec(sql);
        query.first();
        int grade = query.value(4).toInt();
        int attack = query.value(7).toInt();
        int defend = query.value(8).toInt();
        int hp = query.value(9).toInt();
        int interval = query.value(10).toInt();
        qDebug()<<"grade"<<grade<<"attack"<<attack<<"defend"<<defend<<"hp"<<hp<<"interval"<<interval<<endl;
        QString spirit_name = query.value(1).toString();
        if(grade == 14)//假如马上要升级,则用户多了一个高级精灵
        {
            sql = QString("SELECT gspirit_num FROM user WHERE user_ID = %1;").arg(user_ID);
            query.exec(sql);
            query.first();
            int gspirit_num = query.value(0).toInt();
            gspirit_num++;
            sql = QString("UPDATE user SET gspirit_num = %1 WHERE user_ID = %2;").arg(gspirit_num).arg(user_ID);
            query.exec(sql);
        }
        if (grade < 15)
        {
            grade += 1;
            attack += INC;
            defend += 1;
            hp += INC;
            //判断类别，额外增加属性值
            if(spirit_name == "独角兽" || spirit_name == "石锤犀牛")
            {
                attack += INC;
            }
            else if(spirit_name == "石盾牌" || spirit_name == "冰蜗牛")
            {
                defend += 1;
            }
            else if(spirit_name == "紫鬃龙" || spirit_name == "派大星")
            {
                hp += INC;
            }
            else
            {
                //无操作
            }
            //间隔--
            if(spirit_name == "咕咕鸡" || spirit_name == "海马先生")
            {
                if (grade <= 5)
                {
                    interval = 6 - grade;
                }
            }
            else
            {
                if (grade < 15)
                {
                    interval = 5 - grade / 3;
                }
            }
            qDebug()<<"grade"<<grade<<"attack"<<attack<<"defend"<<defend<<"hp"<<hp<<"interval"<<interval<<endl;
            sql = QString("UPDATE spirit SET grade=%1, attack=%3, defend=%4, hp=%5, `interval`=%6 WHERE spirit_ID = %7;")
                    .arg(grade).arg(attack).arg(defend).arg(hp).arg(interval).arg(mID);
            query.exec(sql);
        }  
    }

    //用户经验值+，金币+, 总场数+， 赢场数+， 胜率变
    sql = QString("SELECT exp, money, all_num, win_num, grade FROM user WHERE user_ID = %1;").arg(user_ID);
    query.exec(sql);
    query.first();
    exp = query.value(0).toInt();
    exp += UEXP;
    int money = query.value(1).toInt();
    money += MONEYINC;

    int all_num = query.value(2).toInt();
    all_num++;
    int win_num = query.value(3).toInt();
    win_num++;
    float win_rate = (float)win_num * 100 / all_num;

    //用户升级
    int grade = query.value(4).toInt();
    if(exp % 300 == 0)
    {
        grade += 1;
    }

    sql = QString("UPDATE user SET money = %1, exp = %2, all_num = %3, win_num = %4, win_rate = %5, grade = %6 WHERE user_ID = %7;")
            .arg(money).arg(exp).arg(all_num).arg(win_num).arg(win_rate).arg(grade).arg(user_ID);
    query.exec(sql);
}

void MainWindow::ResultFightWin(QJsonObject json)
{
    qDebug()<<"result fight赢"<<json<<endl;
    QSqlQuery query;
    QString sql;
    int user_ID = json["userID"].toInt();
    int _socketID = json["socketID"].toInt();

    //玩家小精灵经验+
    int mID = json["mID"].toInt();
    sql = QString("SELECT exp FROM spirit WHERE spirit_ID = %1;").arg(mID);
    query.exec(sql);
    query.first();
    int exp = query.value(0).toInt();
    exp += SEXP;
    sql = QString("UPDATE spirit SET exp = %1 WHERE spirit_ID = %2;").arg(exp).arg(mID);
    query.exec(sql);
    //升级
    if(exp % 200 == 0)
    {
        qDebug()<<"升级~~~"<<endl;
        sql = QString("SELECT * FROM spirit WHERE spirit_ID = %1;").arg(mID);
        query.exec(sql);
        query.first();
        int grade = query.value(4).toInt();
        int attack = query.value(7).toInt();
        int defend = query.value(8).toInt();
        int hp = query.value(9).toInt();
        int interval = query.value(10).toInt();
        qDebug()<<"grade"<<grade<<"attack"<<attack<<"defend"<<defend<<"hp"<<hp<<"interval"<<interval<<endl;
        QString spirit_name = query.value(1).toString();
        if(grade == 14)//假如马上要升级,则用户多了一个高级精灵
        {
            sql = QString("SELECT gspirit_num FROM user WHERE user_ID = %1;").arg(user_ID);
            query.exec(sql);
            query.first();
            int gspirit_num = query.value(0).toInt();
            gspirit_num++;
            sql = QString("UPDATE user SET gspirit_num = %1 WHERE user_ID = %2;").arg(gspirit_num).arg(user_ID);
            query.exec(sql);
        }
        if (grade < 15)
        {
            grade += 1;
            attack += INC;
            defend += 1;
            hp += INC;
            //判断类别，额外增加属性值
            if(spirit_name == "独角兽" || spirit_name == "石锤犀牛")
            {
                attack += INC;
            }
            else if(spirit_name == "石盾牌" || spirit_name == "冰蜗牛")
            {
                defend += 1;
            }
            else if(spirit_name == "紫鬃龙" || spirit_name == "派大星")
            {
                hp += INC;
            }
            else
            {
                //无操作
            }
            //间隔--
            if(spirit_name == "咕咕鸡" || spirit_name == "海马先生")
            {
                if (grade <= 5)
                {
                    interval = 6 - grade;
                }
            }
            else
            {
                if (grade < 15)
                {
                    interval = 5 - grade / 3;
                }
            }
            qDebug()<<"grade"<<grade<<"attack"<<attack<<"defend"<<defend<<"hp"<<hp<<"interval"<<interval<<endl;
            sql = QString("UPDATE spirit SET grade=%1, attack=%3, defend=%4, hp=%5, `interval`=%6 WHERE spirit_ID = %7;")
                    .arg(grade).arg(attack).arg(defend).arg(hp).arg(interval).arg(mID);
            query.exec(sql);
        }

    }

    //用户经验值+，金币+, 总场数+， 赢场数+， 胜率变
    sql = QString("SELECT exp, money, all_num, win_num, grade FROM user WHERE user_ID = %1;").arg(user_ID);
    query.exec(sql);
    query.first();
    exp = query.value(0).toInt();
    exp += UEXP;
    int money = query.value(1).toInt();
    money += MONEYINC;

    int all_num = query.value(2).toInt();
    all_num++;
    int win_num = query.value(3).toInt();
    win_num++;
    float win_rate = (float)win_num * 100 / all_num;

    //用户升级
    int grade = query.value(4).toInt();
    if(exp % 300 == 0)
    {
        grade += 1;
    }

    sql = QString("UPDATE user SET money = %1, exp = %2, all_num = %3, win_num = %4, win_rate = %5, grade = %6 WHERE user_ID = %7;")
            .arg(money).arg(exp).arg(all_num).arg(win_num).arg(win_rate).arg(grade).arg(user_ID);
    query.exec(sql);


}

void MainWindow::FightUser(QJsonObject json)
{
    qDebug()<<"FightWidget传来"<<json<<endl;
    QSqlQuery query;
    QJsonArray spirits;
    QString user_name = json["username"].toString();
    int mID = json["mID"].toInt();
    int sID = json["sID"].toInt();
    int _socketID = json["socketID"].toInt();
    qDebug()<<user_name<<" "<<mID<<" "<<sID<<endl;
    QString sql = QString("SELECT all_num, win_num, spirit_num, exp, user_ID FROM user WHERE user_name = '%1';").arg(user_name);
    int all_num;
    int win_num;
    int spirit_num;
    int exp;
    int user_ID;
    query.exec(sql);
    query.first();
    //while(query.next())
    {
        all_num = query.value(0).toInt();
        win_num = query.value(1).toInt();
        spirit_num = query.value(2).toInt();
        exp = query.value(3).toInt();
        user_ID = query.value(4).toInt();
    }
    QJsonObject ujson = {
        {"all_num", all_num},
        {"win_num", win_num},
        {"spirit_num", spirit_num},
        {"exp", exp}
    };
    sql = QString("SELECT * FROM spirit WHERE spirit_ID = %1;").arg(mID);
    query.exec(sql);
    query.first();
    QString spirit_name = query.value(1).toString();
    int spirit_type = query.value(2).toInt();
    int grade = query.value(4).toInt();
    int evolved = query.value(5).toInt();
    exp = query.value(6).toInt();
    int attack = query.value(7).toInt();
    int defend = query.value(8).toInt();
    int hp = query.value(9).toInt();
    int interval = query.value(10).toInt();
    int skillEvolved = query.value(11).toInt();
    QJsonObject mjson = {
        {"spirit_name", spirit_name},
        {"spirit_type", spirit_type},
        {"grade", grade},
        {"evolved", evolved},
        {"exp", exp},
        {"attack", attack},
        {"defend", defend},
        {"hp", hp},
        {"interval", interval},
        {"skillEvolved", skillEvolved}
    };
    sql = QString("SELECT * FROM spirit WHERE spirit_ID = %1;").arg(sID);
    query.exec(sql);
    query.first();
    spirit_name = query.value(1).toString();
    spirit_type = query.value(2).toInt();
    grade = query.value(4).toInt();
    evolved = query.value(5).toInt();
    exp = query.value(6).toInt();
    attack = query.value(7).toInt();
    defend = query.value(8).toInt();
    hp = query.value(9).toInt();
    interval = query.value(10).toInt();
    skillEvolved = query.value(11).toInt();
    QJsonObject sjson = {
        {"spirit_name", spirit_name},
        {"spirit_type", spirit_type},
        {"grade", grade},
        {"evolved", evolved},
        {"exp", exp},
        {"attack", attack},
        {"defend", defend},
        {"hp", hp},
        {"interval", interval},
        {"skillEvolved", skillEvolved}
    };

    json = {
        {"define", FIGHT_USER},
        {"socketID", _socketID},
        {"ujson", ujson},
        {"mjson", mjson},
        {"sjson", sjson}

    };
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);
}

void MainWindow::Choose(QJsonObject json)
{
    qDebug()<<"Choose传来"<<json<<endl;
    QJsonArray array;
    QSqlQuery query;
    int user_ID;
    int _socketID = json["socketID"].toInt();
    user_ID = -1;

    QString sql = QString("SELECT spirit_name, grade, evolved, spirit_ID FROM spirit WHERE user_ID = %1;").arg(user_ID);
    query.exec(sql);
    while(query.next())
    {
        QString spirit_name = query.value(0).toString();
        int grade = query.value(1).toInt();
        int evolved = query.value(2).toInt();
        int spirit_ID = query.value(3).toInt();
        QJsonObject spirit = {
            {"spirit_name", spirit_name},
            {"grade", grade},
            {"evolved", evolved},
            {"spirit_ID", spirit_ID}
        };
        qDebug()<<"精灵："<<spirit<<endl;
        array.append(spirit);
    }
    json = {
        {"define", CHOOSE},
        {"socketID", _socketID},
        {"spirits", array}
    };
    qDebug()<<"传给Choose："<<json<<endl;
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);

}

void MainWindow::LogIn(QJsonObject json)
{
    QSqlQuery query;
    QString username = json["username"].toString();
    QString password = json["password"].toString();
    QString result;
    int userID;
    int _socketID = json["socketID"].toInt();
    qDebug()<<"username:"<<username<<endl;
    QString sql = QString("SELECT password, user_ID FROM user WHERE user_name = '%1';").arg(username);
    qDebug()<<"sql:"<<sql<<endl;
    query.exec(sql);
    while (query.next())
    {
        result = query.value(0).toString();
        userID = query.value(1).toInt();
    }
    qDebug()<<"密码是"<<result<<endl;
    //假如密码正确
    if(result == password)
    {
        qDebug()<<"密码正确"<<endl;
        json  = {
            {"define", LOGIN_SUCCEED},
            {"socketID", _socketID},
            {"username", username},
            {"userID", userID}
        };
        qDebug()<<QString(QJsonDocument(json).toJson())<<endl;
        //更新数据库，设置用户登录状态为登录
        sql = QString("UPDATE user SET online = 1 WHERE user_name = '%1';").arg(username);
        query.exec(sql);

    }
    //密码错误
    else
    {
        json  = {
            {"define", LOGIN_FAILED}
        };
    }
    qDebug()<<"服务器传回："<<json<<endl;
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);
}

void MainWindow::SignIn(QJsonObject json)
{
    QSqlQuery query;
    QString username = json["username"].toString();
    QString password = json["password"].toString();
    int _socketID = json["socketID"].toInt();
    QString sql;
    //try

        //判断用户名是否存在
        sql = QString("SELECT user_name FROM user WHERE user_name = '%1';").arg(username);
        query.exec(sql);
        query.next();
        //用户名不存在
        if(query.value(0).toString() == NULL)
        {
            //在数据库中更新新用户信息
            qDebug()<<"插入新用户信息"<<endl;
            sql = QString("INSERT INTO user (user_name, password, online, win_rate, all_num, win_num, spirit_num, gspirit_num, money, exp, grade) VALUES ('%1', %2, %3, %4, %5, %6, %7, %8, %9, %10, %11);")
                    .arg(username).arg(password).arg(0).arg(0).arg(0).arg(0).arg(3).arg(0).arg(0).arg(0).arg(1);
            query.exec(sql);

            //查找用户ID
            sql = QString("SELECT user_ID FROM user WHERE user_name = '%1' ;").arg(username);
            query.exec(sql);
            query.first();
            int ID = query.value(0).toInt();
            qDebug()<<"ID:"<<ID<<endl;
            sql = QString("SELECT * FROM spirit WHERE user_ID = %1 ;").arg(0);
            query.exec(sql);
            query.first();
            int size = query.size();
            qDebug()<<"size:"<<size<<endl;
            QVector<QSqlRecord> array;
            for(int i = 0; i < size; i++)
            {
                array.append(query.record());
                query.next();
            }
            //随机分配三个小精灵
            srand((unsigned)time(NULL));
            for(int k = size, i = 0; i < 3; i++)
            {
                int j = rand() % k;
                k--;
                qDebug() << "选中小精灵" << j << array[j].value(1).toString() << endl;
                sql = QString("INSERT INTO spirit (spirit_name,user_ID) VALUES ('%1', %2);")
                        .arg(array[j].value(1).toString()).arg(ID);
                query.exec(sql);
                array[j] = array[k];//将最后面的复制到前面
            }
            json  = {
                {"define", SIGNIN_SUCCEED},
                {"socketID", _socketID},
            };
        }
        //用户名已存在
        else
        {
            json  = {
                {"define", SIGNIN_FAILED},
                {"socketID", _socketID},
            };
        }


//    catch (QException &e)
//    {
//        qDebug()<<"error"<<endl;
//        //QMessageBox::information(this, "Error", QString::fromLocal8Bit("与服务器断开连接"));
//    }
        //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
        SendMessage(json);
}

void MainWindow::Lobby(QJsonObject json)
{
    qDebug()<<"Lobby传来："<<json<<endl;
    QString username = json["username"].toString();
    int _socketID = json["socketID"].toInt();
    QString sql = QString("SELECT spirit_num, gspirit_num, money FROM user WHERE user_name = '%1';").arg(username);
    QSqlQuery query;
    query.exec(sql);
    query.next();
    int money = query.value(2).toInt();//用户金钱
    int spirit_num = query.value(0).toInt();//小精灵个数
    int gspirit_num = query.value(1).toInt();//高级精灵个数
    json  = {
        {"define", LOBBY_SUCCEED},
        {"socketID", _socketID},
        {"money", money},
        {"spirit_num", spirit_num},
        {"gspirit_num", gspirit_num}
    };
    qDebug()<<"传给Lobby："<<json<<endl;
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);
}

void MainWindow::UserList(QJsonObject json)
{
    int _socketID = json["socketID"].toInt();
    qDebug()<<"UserList传来："<<json<<endl;
    QString sql = QString("SELECT user_name, online, grade FROM user;");
    QSqlQuery query;
    query.exec(sql);
    QJsonArray array;
    int num = 0;
    while(query.next())
    {
        num++;
        QString username = query.value(0).toString();
        int online = query.value(1).toInt();
        int grade = query.value(2).toInt();
        QJsonObject user = {
            {"username", username},
            {"online", online},
            {"grade", grade}
        };
        array.append(user);
    }
    qDebug()<<"用户信息:"<<array<<endl;
    json  = {
        {"define", USERLIST},
        {"socketID", _socketID},
        {"number", num},
        {"array", array}
    };
    qDebug()<<"传给UserList："<<json<<endl;
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);
}

void MainWindow::UserInfo(QJsonObject json)
{
    qDebug()<<"UserInfo传来："<<json<<endl;
    QString username = json["username"].toString();
    int _socketID = json["socketID"].toInt();
    int online;//是否在线
    int grade;//用户等级
    int spirit_num;//小精灵个数
    int gspirit_num;//高级小精灵个数
    int user_ID;//用户ID
    double win_rate;//胜率
    QString sql = QString("SELECT user_ID, online, grade, win_rate, spirit_num, gspirit_num FROM user WHERE user_name = '%1';").arg(username);
    QSqlQuery query;
    QJsonArray array;
    query.exec(sql);
    while(query.next())
    {
        user_ID = query.value(0).toInt();//用户ID
        online = query.value(1).toInt();//用户是否在线
        grade = query.value(2).toInt();//用户等级
        win_rate = query.value(3).toDouble();//用户胜率
        spirit_num = query.value(4).toInt();//小精灵个数
        gspirit_num = query.value(5).toInt();//高级小精灵个数

    }
    qDebug()<<"userID"<<user_ID<<endl;
    sql = QString("SELECT spirit_name, grade, evolved FROM spirit WHERE user_ID = %1;").arg(user_ID);
    query.exec(sql);
    while(query.next())
    {
        QString spirit_name = query.value(0).toString();
        int grade = query.value(1).toInt();
        int evolved = query.value(2).toInt();
        QJsonObject spirit = {
            {"spirit_name", spirit_name},
            {"grade", grade},
            {"evolved", evolved}
        };
        qDebug()<<"精灵："<<spirit<<endl;
        array.append(spirit);
    }

    json = {
        {"define", USERINFO},
        {"socketID", _socketID},
        {"username", username},
        {"online", online},
        {"grade", grade},
        {"win_rate", win_rate},
        {"spirit_num", spirit_num},
        {"gspirit_num", gspirit_num},
        {"spirits", array}
    };
    qDebug()<<"传给UserInfo："<<json<<endl;
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);
}

void MainWindow::Bag(QJsonObject json)
{
    qDebug()<<"BagWidget传来"<<json<<endl;
    QJsonArray array;
    QString username = json["username"].toString();
    int _socketID = json["socketID"].toInt();
    int user_ID;
    int money;
    QString sql = QString("SELECT user_ID, money from user WHERE user_name = '%1';").arg(username);
    QSqlQuery query;
    query.exec(sql);
    query.next();
    user_ID = query.value(0).toInt();
    money = query.value(1).toInt();
    qDebug()<<"用户ID"<<user_ID<<endl;

    sql = QString("SELECT spirit_name, grade, evolved, spirit_ID FROM spirit WHERE user_ID = %1;").arg(user_ID);
    query.exec(sql);
    while(query.next())
    {
        QString spirit_name = query.value(0).toString();
        int grade = query.value(1).toInt();
        int evolved = query.value(2).toInt();
        int spirit_ID = query.value(3).toInt();
        QJsonObject spirit = {
            {"spirit_name", spirit_name},
            {"grade", grade},
            {"evolved", evolved},
            {"spirit_ID", spirit_ID}
        };
        qDebug()<<"精灵："<<spirit<<endl;
        array.append(spirit);
    }
    json = {
        {"define", BAG},
        {"socketID", _socketID},
        {"spirits", array},
        {"money", money}
    };
    qDebug()<<"传给BagWidget："<<json<<endl;
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);
}

void MainWindow::SpiritInfo(QJsonObject json)
{
    qDebug()<<"SpiritInfo传来"<<json<<endl;
    QJsonArray array;
    int spirit_ID = json["spirit_ID"].toInt();//小精灵ID
    int _socketID = json["socketID"].toInt();
    QString sql = QString("SELECT * FROM spirit WHERE spirit_ID = %1;").arg(spirit_ID);
    QSqlQuery query;
    query.exec(sql);
    query.next();
    QString spirit_name = query.value(1).toString();//精灵姓名
    int spirit_type = query.value(2).toInt();//精灵类型
    int grade = query.value(4).toInt();//精灵等级
    int evolved = query.value(5).toInt();//是否进化
    int exp = query.value(6).toInt();//经验值
    int attack = query.value(7).toInt();//攻击值
    int defend = query.value(8).toInt();//防御值
    int hp = query.value(9).toInt();//生命值
    int interval = query.value(10).toInt();//攻击间隔
    int user_ID = query.value(3).toInt();//用户ID
    int skillEvolved = query.value(11).toInt();
    sql = QString("SELECT money from user WHERE user_ID = %1;").arg(user_ID);
    query.exec(sql);
    query.next();
    int money = query.value(0).toInt();
    json = {
        {"define", SPIRINTINFO},
        {"socketID", _socketID},
        {"money", money},
        {"spirit_name", spirit_name},
        {"spirit_type", spirit_type},
        {"grade", grade},
        {"evolved", evolved},
        {"exp",exp},
        {"attack",attack},
        {"defend",defend},
        {"hp",hp},
        {"interval",interval},
        {"skillEvolved", skillEvolved}

    };
    qDebug()<<"传给SpiritInfo："<<json<<endl;
    //tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    SendMessage(json);
}

void MainWindow::SendMessage(QJsonObject json)
{
    int size = socketList.size();
    qDebug()<<"向"<<size<<"个客户发送信息"<<endl;
    //给所有的客户端发送信息
    for(int i = 0; i < size; i++)
    {
        QTcpSocket *tem = socketList[i];
        tem->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

