#ifndef VIRUS_H
#define VIRUS_H

#include <QPointF>
#include <stdlib.h>
#include"Bullet.h"

class Virus: public Bullet
{
public:
    enum class VType{A,B,C,BOSS};//possible types of viruses
    Virus(){};
    Virus(VType vtype,int speed,int attack_potential,qreal angle);
    virtual ~Virus(){};
    int get_attack_potential();//accesor of attack_potential
    qreal get_angle(){return angle;}//accesor of angle
protected:    
    const int WEITH{25}; //used to scale virus's photo
    const int HEIGHT{30}; //used to scale virus's photo
    int speed{0}; //virus's moving speed
    int attack_potential{0};//similar to "attack" in pa3
    qreal angle{0}; //virus's angle, not used directly, but used to calculate xdir and ydir
    const int xdir{0}; //the velocity in the x direction
    const int ydir{0}; //the velocity in the y direction
    VType vtype;// virus's type(A/B/C)
protected slots:
    virtual void move() override;
    virtual bool check_collide() override;
    virtual void attack() override;
};

#endif // VIRUS_H
