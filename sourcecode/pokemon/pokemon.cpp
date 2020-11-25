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

QString Pokemon::getName() const
{
    return this->name;
}

int Pokemon::getGrade() const
{
    return grade;
}

void Pokemon::setGrade(int gra)
{
    grade = gra;
}

QString Pokemon::getAttackName() const
{
    return attackName;
}

bool Pokemon::isDead() const
{
    if (hp <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Pokemon::getID() const
{
    return id;
}
bool Pokemon::isEvolved() const
{
    return evolved;
}

bool Pokemon::isSkillEvolved() const
{
    return skillEvolved;
}

void Pokemon::setEvolved(bool evol)
{
    evolved = evol;
}

void Pokemon::setSkillEvolved(bool evol)
{
    skillEvolved = evol;
}

int Pokemon::getExp() const
{
    return exp;
}

int Pokemon::getAtta() const
{
    return atta;
}

int Pokemon::getDefense() const
{
    return defense;
}

int Pokemon::getHp() const
{
    return hp;
}

int Pokemon::getInterval() const
{
    return interval;
}

void Pokemon::setExp(int value)
{
    exp = value;
}

void Pokemon::setAtta(int value)
{
    atta = value;
}

void Pokemon::setDefense(int value)
{
    defense = value;
}

void Pokemon::setHp(int value)
{
    hp = value;
}

void Pokemon::setInterval(int value)
{
    interval = value;
}

void Attack::upgrade()
{
    if (grade == 15)
    {
        return;
    }
    grade += 1;
    atta += 2 * INC;
    defense += 1;
    hp += INC;
    if (grade < 15)
    {
        interval = 5 - grade / 3;
    }

}

void Horse::attack(Pokemon *enemy)
{
    int value;
    if (skillEvolved == true)
    {
        value = 1.2 * atta;
    }
    else
    {
        value = atta;
    }
    //特殊功能：削弱对方防御能力
    if (enemy->getDefense() > 8)
    {
        enemy->setDefense(enemy->getDefense() - 1);
        qDebug() << "特殊功能:对方小精灵防御能力降为" << enemy->getDefense() << endl;
    }
    value = 10 / enemy->getDefense() * value; //计算敌方小精灵hp减少值
    qDebug() << "对方hp-" << value << endl;
    enemy->setHp(enemy->getHp() - value);
}

void Ox::attack(Pokemon *enemy)
{
    int value;
    if (skillEvolved == true)
    {
        value = 1.2 * atta;
    }
    else
    {
        value = atta;
    }
    //特殊功能：让敌方小精灵升级技能失效
    enemy->setSkillEvolved(false);
    qDebug() << "特殊功能:使对方小精灵升级技能失效" << endl;
    value = 10 / enemy->getDefense() * value; //计算敌方小精灵hp减少值
    qDebug() << "对方hp-" << value << endl;
    enemy->setHp(enemy->getHp() - value);
}

void Hp::upgrade()
{
    if (grade == 15)
    {
        return;
    }
    grade += 1;
    atta += INC;
    defense += 1;
    hp += 2 * INC;

    if (grade < 15)
    {
        interval = 5 - grade / 3;
    }
}

void Dragon::attack(Pokemon *enemy)
{
    int value;
    if (skillEvolved == true)
    {
        value = 1.2 * atta;
    }
    else
    {
        value = atta;
    }
    //特殊功能：自愈功能
    this->setHp(this->getHp() + 2);
    qDebug() << "特殊功能:自身hp增加为" << this->getHp() << endl;
    value = 10 / enemy->getDefense() * value; //计算敌方小精灵hp减少值
    qDebug() << "对方hp-" << value << endl;
    enemy->setHp(enemy->getHp() - value);
}

void Star::attack(Pokemon *enemy)
{
    int value;
    if (skillEvolved == true)
    {
        value = 1.2 * atta;
    }
    else
    {
        value = atta;
    }
    value = 10 / enemy->getDefense() * value; //计算敌方小精灵hp减少值
    //特殊功能：给敌方小精灵造成额外的攻击
    value += 2;
    qDebug() << "特殊功能:对小精灵造成额外攻击" << endl;
    qDebug() << "对方hp-" << value << endl;
    enemy->setHp(enemy->getHp() - value);
}

void Defend::upgrade()
{
    if (grade == 15)
    {
        return;
    }
    grade += 1;
    atta += INC;
    defense += 2;
    hp += INC;
    if (grade < 15)
    {
        interval = 5 - grade / 3;
    }
}

void Rock::attack(Pokemon *enemy)
{
    int value;
    if (skillEvolved == true)
    {
        value = 1.2 * atta;
    }
    else
    {
        value = atta;
    }
    //特殊功能：降低敌方小精灵攻击值
    if (enemy->getAtta() > 5)
    {
        enemy->setAtta(enemy->getAtta() - 1);
        qDebug() << "特殊功能:对方小精灵攻击值降为" << enemy->getAtta() << endl;
    }

    value = 10 / enemy->getDefense() * value; //计算敌方小精灵hp减少值
    qDebug() << "对方hp-" << value << endl;
    enemy->setHp(enemy->getHp() - value);
}

bool Snail::getFlag()
{
    return flag;
}

void Snail::setFlag(bool fla)
{
    flag = fla;
}

void Snail::attack(Pokemon *enemy)
{
    int value;
    if (skillEvolved == true)
    {
        value = 1.2 * atta;
    }
    else
    {
        value = atta;
    }
    //特殊功能：减缓敌方小精灵速度(只能作用一次)
    if (flag == false)
    {
        enemy->setInterval(enemy->getInterval() + 1);
        qDebug() << "特殊功能:对方小精灵攻击间隔增加为" << enemy->getInterval() << endl;
        this->setFlag(true);
    }
    value = 10 / enemy->getDefense() * value; //计算敌方小精灵hp减少值
    qDebug() << "对方hp-" << value << endl;
    enemy->setHp(enemy->getHp() - value);
}

void Interval::upgrade()
{
    if (grade == 15)
    {
        return;
    }
    grade += 1;
    atta += INC;
    defense += 1;
    hp += INC;
    if (grade <= 5)
    {
        interval = 6 - grade;
    }
}

void Bird::attack(Pokemon *enemy)
{
    int value;
    if (skillEvolved == true)
    {
        value = 1.2 * atta;
    }
    else
    {
        value = atta;
    }
    //特殊功能：降低敌方小精灵防御值
    if (enemy->getDefense() > 8)
    {
        enemy->setDefense(enemy->getDefense() - 1);
        qDebug() << "特殊功能:对方小精灵防御值降为" << enemy->getDefense() << endl;
    }

    value = 10 / enemy->getDefense() * value; //计算敌方小精灵hp减少值
    qDebug() << "对方hp-" << value << endl;
    enemy->setHp(enemy->getHp() - value);
}

void Haima::attack(Pokemon *enemy)
{
    int value;
    if (skillEvolved == true)
    {
        value = 1.2 * atta;
    }
    else
    {
        value = atta;
    }
    //特殊功能：降低敌方小精灵攻击值
    if (enemy->getAtta() > 5)
    {
        enemy->setAtta(enemy->getAtta() - 1);
        qDebug() << "特殊功能:对方小精灵攻击值降为" << enemy->getAtta() << endl;
    }

    value = 10 / enemy->getDefense() * value; //计算敌方小精灵hp减少值
    qDebug() << "对方hp-" << value << endl;
    enemy->setHp(enemy->getHp() - value);
}
