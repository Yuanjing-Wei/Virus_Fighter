#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QtMath>
#include <math.h>
#include <QGraphicsItem>
#include "gameengine.h"
#include "virus.h"

extern GameEngine * game;

Virus::Virus(VType vtype,int speed,int attack_potential,qreal angle):Bullet(Bullet::Type::VIRUS),vtype(vtype),speed(speed),attack_potential(attack_potential), angle(angle), xdir(qSin(angle)*speed),ydir(qCos(angle)*speed){}

void Virus::move(){
    setPos(x()+xdir,y()+ydir);
    //check whether it is out of bound
    Virus::check_out();
}

int Virus::get_attack_potential(){
    return this->attack_potential;
}

bool Virus::check_collide()
{
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if it collide with the player, return true
    for (int i = 0, n = colliding_items.size(); i<n; ++i){
        auto &obj=*colliding_items[i];
        if (typeid(obj) == typeid(Player)){
            return true;
        }
    }

    return false;
}

void Virus::attack(){
    if(check_collide()){
        //access the amount of damage depends on the virus type
        int damage=get_attack_potential();
        //actually do the damage
        game->health->decrease(damage);
        //after attack, the virus's job is done and should disapper from the screen
        delete this;
    }
}
