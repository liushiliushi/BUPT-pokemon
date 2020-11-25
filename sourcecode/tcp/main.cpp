#include "mainwindow.h"
#include <QApplication>
#include"manager.h"
Manager ma;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
