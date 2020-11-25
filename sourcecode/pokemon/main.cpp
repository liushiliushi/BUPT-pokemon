#include "widget.h"
#include"manager.h"
#include <QResource>
#include <QApplication>
#include"manager.h"
Manager ma;
int main(int argc, char *argv[])
{
    qDebug()<<"1111"<<endl;
    QApplication a(argc, argv);
    //QResource::registerResource();

    Widget w;
    qDebug()<<"显示开始界面"<<endl;
    w.show();
    return a.exec();
}
