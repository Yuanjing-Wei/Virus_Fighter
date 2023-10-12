#ifndef WEAPON_H
#define WEAPON_H

#include "Bullet.h"

class Weapon: public Bullet
{
private:
    const int WEITH{25};
    const int HEIGHT{30};
    int speed{10};
    int attack_potential{0};

    bool used = false;
    qreal angle{0};
    int xdir{0};
    int ydir{0};
public:
    //Weapon();
    Weapon(int speed,int attack_potential,qreal angle);
    ~Weapon(){};
private slots:
    virtual void move() override;
    virtual bool check_collide() override;
    virtual void attack() override;
};

#endif // WEAPON_H
