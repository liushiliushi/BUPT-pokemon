#include "listitem.h"

ListItem::ListItem(QWidget *parent, const QString &icon1, const QString &text1, const QString &text2) : QWidget(parent)
{
    model = 1;

    la1.setText(text1);
    QFont font1("微软雅黑",13);
    la1.setFont(font1);
    QFont font2("微软雅黑",13);
    la2.setText(text2);
    la2.setFont(font2);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(&la1);
    layout->addWidget(&la2);
}

ListItem::ListItem(QWidget *parent, QString spirit_name, QString grade, int evolved)
{
    model = 3;//用户信息小精灵项
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPixmap pix;

    la1.setParent(this);
    la2.setParent(this);
    la3.setParent(this);

    //找到小精灵头像地址
    QString path;
    //假如已进化
    if(evolved == 1)
    {
        path = ma.bhmap[spirit_name];
    }
    //假如未进化
    else
    {
        path = ma.shmap[spirit_name];
    }

    pix.load(path);
    la1.setPixmap(pix);
    layout->addWidget(&la1);

    //小精灵姓名
    QFont namefont("微软雅黑", 12);
    la2.setText(spirit_name);
    la2.setFont(namefont);
    la2.setAlignment(Qt::AlignHCenter);
    layout->addWidget(&la2);


    //小精灵等级
    QFont gradefont("微软雅黑", 12);
    la3.setText("Lv: " + grade);
    la3.setFont(gradefont);
    la3.setAlignment(Qt::AlignHCenter);
    layout->addWidget(&la3);




}
//背包小精灵项
ListItem::ListItem(QWidget *parent, int evolved, QString spirit_name, QString grade) : QWidget(parent)
{
    //配置场景
    setFixedSize(280, 375);
    model = 2;

    QVBoxLayout *layout = new QVBoxLayout(this);
    QPixmap pix;

    la1.setParent(this);
    la2.setParent(this);
    la3.setParent(this);

    //找到小精灵头像地址
    QString path;

    //假如已进化
    if(evolved == 1)
    {
        path = ma.bfmap[spirit_name];
    }
    //假如未进化
    else
    {
        path = ma.sfmap[spirit_name];
    }

    pix.load(path);

    la1.setPixmap(pix);

    //小精灵等级

    layout->addWidget(&la1);

    //小精灵姓名
    QFont namefont("微软雅黑", 12);
    la2.setText(spirit_name);
    la2.setFont(namefont);
    la2.setAlignment(Qt::AlignHCenter);
    la3.setText("Lv:" + grade);
    la3.setFont(namefont);
    la3.setAlignment(Qt::AlignHCenter);
    layout->addWidget(&la2);
    layout->addWidget(&la3);

}

//用户列表项
ListItem::ListItem(QWidget *parent, QString username, int online, QString grade)
{
    model = 1;
    la1.setAlignment(Qt::AlignHCenter);
    la2.setAlignment(Qt::AlignHCenter);
    la3.setAlignment(Qt::AlignHCenter);
    la1.setText(username);//姓名
    QFont font1("微软雅黑",13);
    la1.setFont(font1);
    QFont font2("微软雅黑",13);
    if(online == 1)
    {
        la2.setStyleSheet("color:green");
        la2.setText("在线");
        la2.setFont(font2);
    }
    else
    {
        la2.setText("离线");
        la2.setFont(font2);
        la2.setStyleSheet("color:red");
    }
    la3.setText("等级："+grade);
    la3.setFont(font2);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(&la1);
    layout->addWidget(&la2);
    layout->addWidget(&la3);
}

void ListItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //用户列表项
    if(model == 1)
    {
        QPixmap pix;
        pix.load(UFRAME_PATH);
        painter.drawPixmap(0, 0, this->width(), this->height(), pix);//绘制用户栏
    }
    //小精灵列表项
    else if(model == 2)
    {
        QPixmap pix;
        pix.load(FRAME2_PATH);
        painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    }
    else
    {

    }
}


void ListItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug()<<"选中了第"<<index<<"个"<<endl;
        emit this->listItemClicked(index);
    }

}

void ListItem::setIndex(int a)
{
    this->index = a;
}

int ListItem::getIndex()
{
    return index;
}
