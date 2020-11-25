#include "pokemon.h"

Pokemon::Pokemon()
{
    grade = 1;
    evolved = false;//未进化
    exp = 0;
    atta = 10;
    defense = 10;
    hp = 100;
    interval = 5;
}

Pokemon::Pokemon(QString _spirit_name, int _grade, int _evolved, int _exp, int _attack, int _defend, int _hp, int _interval, int _skillEvolved)
{
    name = _spirit_name;
    grade = _grade;
    evolved = (bool)_evolved;
    exp = _exp;
    atta = _attack;
    defense = _defend;
    hp = _hp;
    interval = _interval;
    skillEvolved = (bool)_skillEvolved;
}

//被攻击函数
void Pokemon::attacked(int value)
{
    if(evolved == true)
    {
        hp -= value * 0.8;
    }
    else
    {
        hp -= value;
    }
}

void Attack::upgrade()
{
    if (grade < 15)
    {
        grade += 1;
    }
    atta += 2 * INC;
    defense += INC;
    hp += INC;
    if (grade < 15)
    {
        interval = 5 - grade / 3;
    }
}

int Horse::attack()
{
    int value = atta * 0.1;
    if(skillEvolved == true)
    {
        value *= 1.2;
        attackName = "十万马力";
    }
    else
    {
        attackName = "踩踏";
    }
    return value;
}

int Ox::attack()
{
    int value = atta * 0.1;
    if(skillEvolved == true)
    {
        value *= 1.2;
        attackName = "原始之力";
    }
    else
    {
        attackName = "吼叫";
    }
    return value;
}

void Hp::upgrade()
{
    if (grade < 15)
    {
        grade += 1;
    }
    atta += INC;
    defense += INC;
    hp += 2 * INC;
    if (grade < 15)
    {
        interval = 5 - grade / 3;
    }
}

int Dragon::attack()
{
    int value = atta * 0.1;
    if(skillEvolved == true)
    {
        value *= 1.2;
        attackName = "火焰漩涡";
    }
    else
    {
        attackName = "风火轮";
    }
    return value;
}

int Star::attack()
{
    int value = atta * 0.1;
    if(skillEvolved == true)
    {
        value *= 1.2;
        attackName = "神秘守护";
    }
    else
    {
        attackName = "泡沫攻击";
    }
    return value;
}

void Defend::upgrade()
{
    if (grade < 15)
    {
        grade += 1;
    }
    atta += INC;
    defense += 2 * INC;
    hp += INC;
    if (grade < 15)
    {
        interval = 5 - grade / 3;
    }
}

int Rock::attack()
{
    int value = atta * 0.1;
    if(skillEvolved == true)
    {
        value *= 1.2;
        attackName = "沙暴";
    }
    else
    {
        attackName = "岩崩";
    }
    return value;
}

int Snail::attack()
{
    int value = atta * 0.1;
    if(skillEvolved == true)
    {
        value *= 1.2;
        attackName = "海妖之啸";
    }
    else
    {
        attackName = "水滴攻击";
    }
    return value;
}

void Interval::upgrade()
{
    if (grade < 15)
    {
        grade += 1;
    }
    atta += INC;
    defense += INC;
    hp += INC;
    if (grade <= 5)
    {
        interval = 6 - grade;
    }
}

int Bird::attack()
{
    int value = atta * 0.1;
    if(skillEvolved == true)
    {
        value *= 1.2;
        attackName = "空气斩";
    }
    else
    {
        attackName = "羽毛舞";
    }
    return value;
}

int Haima::attack()
{
    int value = atta * 0.1;
    if(skillEvolved == true)
    {
        value *= 1.2;
        attackName = "水之波动";
    }
    else
    {
        attackName = "冰冻之风";
    }
    return value;
}
