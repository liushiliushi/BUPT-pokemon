#ifndef POKEMON_H
#define POKEMON_H
#pragma execution_character_set("utf-8")

#include <QString>
#include"config.h"
#include"manager.h"
#include<QString>
extern Manager ma;
class Pokemon
{
public:
    //属性
    QString name;//名字
    QString attackName;
    int id;//编号（唯一）
    int grade;//等级
    bool evolved;//是否进化 （到达8级之后可以进化）
    bool skillEvolved;//技能是否进化
    int exp;//经验值
    int atta;//攻击力
    int defense;//防御力
    int hp;//生命值
    int interval;//攻击间隔

    //方法
    Pokemon();//构造函数
    Pokemon(QString spirit_name, int grade, int evolved, int exp, int attack, int defend, int hp, int interval, int skillEvolved);
    virtual void upgrade() = 0;//升级
    virtual int attack() = 0;//攻击函数
    void attacked(int value) ;//被攻击函数
};

//力量型
class Attack :public Pokemon
{
public:

    Attack() {}
    virtual int attack() = 0 ;//攻击函数
    void upgrade();
};

//独角兽
class Horse :public Attack
{
public:
    Horse(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved){
        name = "独角兽";
        grade = _grade;
        evolved = (bool)_evolved;
        exp = _exp;
        atta = _attack;
        defense = _defend;
        hp = _hp;
        interval = _interval;
        skillEvolved = (bool)_skillEvolved;
    }

    Horse() {
        name = "独角兽";
    }
    int attack();
    ~Horse() {}
};

//石锤犀牛
class Ox :public Attack
{
public:
    Ox(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved){
        name = "石锤犀牛";
        grade = _grade;
        evolved = (bool)_evolved;
        exp = _exp;
        atta = _attack;
        defense = _defend;
        hp = _hp;
        interval = _interval;
        skillEvolved = (bool)_skillEvolved;
    }

    int attack();
    ~Ox() {}
};


//肉盾型
class Hp :public Pokemon
{
public:
    //Hp();
    virtual int attack() = 0 ;//攻击函数
    void upgrade();
};

//紫鬃龙
class Dragon :public Hp
{
public:
    Dragon(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved){
        name = "紫鬃龙";
        grade = _grade;
        evolved = (bool)_evolved;
        exp = _exp;
        atta = _attack;
        defense = _defend;
        hp = _hp;
        interval = _interval;
        skillEvolved = (bool)_skillEvolved;
    }
    int attack();
};

//派大星
class Star :public Hp
{
public:
    Star(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved){
        name = "派大星";
        grade = _grade;
        evolved = (bool)_evolved;
        exp = _exp;
        atta = _attack;
        defense = _defend;
        hp = _hp;
        interval = _interval;
        skillEvolved = (bool)_skillEvolved;
    }
    int attack();
};

//防御型
class Defend :public Pokemon
{
public:
    Defend() {}
    virtual int attack() = 0 ;//攻击函数
    void upgrade();
};

//石盾牌
class Rock :public Defend
{
public:
    Rock() {
        name = "石盾牌";
    };
    Rock(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved){
        name = "石盾牌";
        grade = _grade;
        evolved = (bool)_evolved;
        exp = _exp;
        atta = _attack;
        defense = _defend;
        hp = _hp;
        interval = _interval;
        skillEvolved = (bool)_skillEvolved;
    }
    int attack();
};

//冰蜗牛
class Snail :public Defend
{
public:
    Snail() {
        name = "冰蜗牛";
    }
    Snail(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved){
        name = "冰蜗牛";
        grade = _grade;
        evolved = (bool)_evolved;
        exp = _exp;
        atta = _attack;
        defense = _defend;
        hp = _hp;
        interval = _interval;
        skillEvolved = (bool)_skillEvolved;
    }
    int attack();
};

//敏捷型
class Interval :public Pokemon
{
public:
    Interval() {}
    virtual int attack() = 0 ;//攻击函数
    void upgrade();
};

//咕咕鸡
class Bird :public Interval
{
public:
    Bird() {
        name = "咕咕鸡";
    }
    Bird(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved){
        name = "咕咕鸡";
        grade = _grade;
        evolved = (bool)_evolved;
        exp = _exp;
        atta = _attack;
        defense = _defend;
        hp = _hp;
        interval = _interval;
        skillEvolved = (bool)_skillEvolved;
    }
    int attack();
};

//海马先生
class Haima :public Interval
{
public:
    Haima()
    {
        name = "海马先生";
    }
    Haima(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved){
        name = "海马先生";
        grade = _grade;
        evolved = (bool)_evolved;
        exp = _exp;
        atta = _attack;
        defense = _defend;
        hp = _hp;
        interval = _interval;
        skillEvolved = (bool)_skillEvolved;
    }
    int attack();
};

#endif // POKEMON_H
