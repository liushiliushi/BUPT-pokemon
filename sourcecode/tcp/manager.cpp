#include "manager.h"

Manager::Manager()
{
    isOpen = false;
    openDatabase();//打开数据库

}

void Manager::openDatabase()
{
    if(isOpen == true)
    {
        return;
    }
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("pokemon");
    db.setUserName("root");
    db.setPassword("7043834");

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    isOpen = true;

    if(!db.open())
    {
        qDebug()<<"can't open database";
        isOpen = false;
    }
    else
    {
        qDebug()<<"成功连接数据库";
        isOpen = true;
    }
}



void Manager::closeDatabase()
{
    db.close();
    isOpen = false;
}
