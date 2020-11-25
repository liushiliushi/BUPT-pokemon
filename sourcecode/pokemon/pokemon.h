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
protected:
    //属性
    QString name;//名字
    QString attackName;//攻击名
    int id;//编号（唯一）
    int grade;//等级
    bool evolved;//是否进化 （到达8级之后可以进化）
    bool skillEvolved;//技能是否进化
    int exp;//经验值
    int atta;//攻击力7
    int defense;//防御力55
    int hp;//生命值
    int interval;//攻击间隔

    //方法
public:
    Pokemon();//构造函数
    Pokemon(QString spirit_name, int grade, int evolved, int exp, int attack, int defend, int hp, int interval, int skillEvolved);
    virtual void upgrade() = 0;//升级
    virtual void attack(Pokemon *) = 0;//攻击函数
    bool isDead() const;//判断是否死亡
    QString getAttackName() const;//获取攻击名
    int getID() const;//获取小精灵ID
    bool isEvolved() const;//小精灵是否进化
    bool isSkillEvolved() const;//小精灵技能是否进化
    void setEvolved(bool evol);//设置小精灵是否进化
    void setSkillEvolved(bool evol);//设置小精灵技能是否进化
    int getExp() const;//获取小精灵经验值
    int getAtta() const;//获取小精灵攻击值
    int getDefense() const;//获取小精灵防御值
    int getHp() const;//获取小精灵HP
    int getInterval() const;//获取小精灵攻击间隔
    void setExp(int value);//设置小精灵经验值
    void setAtta(int value);//设置小精灵攻击值
    void setDefense(int value);//设置小精灵防御值
    void setHp(int value);//设置小精灵HP
    void setInterval(int value);//设置小精灵攻击间隔
    int getGrade() const;//获得小精灵等级
    void setGrade(int gra);//设置小精灵等级
    QString getName() const;//获取小精灵姓名
};

//力量型
class Attack :public Pokemon
{
public:

    Attack() {}
    virtual void attack(Pokemon *) = 0;//攻击函数
    void upgrade();
};

//独角兽
class Horse :public Attack
{
public:
    Horse(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved) {
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
    void attack(Pokemon *enemy);
    ~Horse() {}
};

//石锤犀牛
class Ox :public Attack
{
public:
    Ox(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved) {
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

    void attack(Pokemon *enemy);
    ~Ox() {}
};


//肉盾型
class Hp :public Pokemon
{
public:
    //Hp();
    virtual void attack(Pokemon *) = 0;//攻击函数
    void upgrade();
};

//紫鬃龙
class Dragon :public Hp
{
public:
    Dragon(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved) {
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
    void attack(Pokemon *enemy);
};

//派大星
class Star :public Hp
{
public:
    Star(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved) {
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
    void attack(Pokemon *enemy);
};

//防御型
class Defend :public Pokemon
{
public:
    Defend() {}
    virtual void attack(Pokemon *) = 0;//攻击函数
    void upgrade();
};

//石盾牌
class Rock :public Defend
{
public:
    Rock() {
        name = "石盾牌";
    };
    Rock(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved) {
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
    void attack(Pokemon *enemy);
};

//冰蜗牛
class Snail :public Defend
{
public:
    Snail() {
        name = "冰蜗牛";
    }
    Snail(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved) {
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
    void attack(Pokemon *enemy);
    bool getFlag();
    void setFlag(bool fla);
private:
    bool flag = false;//是否使用减缓对方速度技能
};

//敏捷型
class Interval :public Pokemon
{
public:
    Interval() {}
    virtual void attack(Pokemon *) = 0;//攻击函数
    void upgrade();
};

//咕咕鸡
class Bird :public Interval
{
public:
    Bird() {
        name = "咕咕鸡";
    }
    Bird(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved) {
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
    void attack(Pokemon *enemy);
};

//海马先生
class Haima :public Interval
{
public:
    Haima()
    {
        name = "海马先生";
    }
    Haima(int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved) {
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
    void attack(Pokemon *enemy);
};



#endif // POKEMON_H
