#ifndef MANAGER_H
#define MANAGER_H
#pragma execution_character_set("utf-8")
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QTextCodec>
#include<QDebug>
#include<QMessageBox>

class Manager
{
public:
    bool isOpen;//是否打开
    Manager();
    QSqlDatabase db;
    void openDatabase();
    void closeDatabase();
    void logIn(QString name, QString passWord);//登陆
private:

};

#endif // MANAGER_H
