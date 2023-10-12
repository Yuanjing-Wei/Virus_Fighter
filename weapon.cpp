#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "weapon.h"
#include "WildAnimal.h"
#include "Anti.h"
#include "Devil.h"
#include "boss.h"
#include <QtMath>
#include "gameengine.h"

extern GameEngine * game;
Weapon::Weapon(int speed,int attack_potential,qreal angle):Bullet(Bullet::Type::WEAPON),speed(speed),attack_potential(attack_potential), angle(angle), xdir(qSin(angle)*speed),ydir(qCos(angle)*speed)
{
    QSize size{WEITH,HEIGHT};
    QPixmap weaponImg=QPixmap(":/images/game_resource/images/pb1.png").scaled(size,Qt::KeepAspectRatio);
    setPixmap(QPixmap(weaponImg));

    connect_n_start();
}
//The function move() controls the movement of weapons. When it touches the left or right
//bound, it will bounce back and when touch upper or lower bound, it will be removed.
void Weapon::move(){

    setPos(x()+xdir,y()+ydir);
    if (pos().x()<-8||pos().x()>410)
    {
       xdir = -xdir;
    }
    if (pos().y() < 0||pos().y()>750)
    {
       scene()->removeItem(this);
       delete this;
    }
}

bool Weapon::check_collide(){return false;}


/*
 * The function attack() first
 * check whether the weapon has been used since a weapon will be removed when it collide with
 * an enemy. Then it will get a list of all the items currently colliding with the weapon, if there
 * is an enemy, set the variable used to be true, remove the weapon, increase the score and
 * damage will caused to the enemy according to the attack potential of weapon.
*/

void Weapon::attack(){
    if(!used)
{

    // get all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy the bullet(weapon) and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){
            // increase the score//to be adjusted when enemies are done
            game->score->increase();

            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // delete them from the heap to save memory
            delete colliding_items[i];
            delete this;

            // return (all code below refers to a non existint bullet)
            return;
        }

        if (typeid(*(colliding_items[i])) == typeid(WildAnimal)){
                    // increase the score
            used = true;
                    game->score->increase();
                    WildAnimal *wild_animal = qgraphicsitem_cast<WildAnimal*>(colliding_items[i]);
                    wild_animal->get_attack(attack_potential);
                    // remove them from the scene (still on the heap)
                    //scene()->removeItem(colliding_items[i]);

                    scene()->removeItem(this);

                    // delete them from the heap to save memory
                    //delete colliding_items[i];

                    delete this;

                    // return (all code below refers to a non existint bullet)
                    return;
                }
        if (typeid(*(colliding_items[i])) == typeid(Devil)){
            used = true;
                    // increase the score
                    game->score->increase();
                    Devil *devil = qgraphicsitem_cast<Devil*>(colliding_items[i]);
                    devil->get_attack(attack_potential);
                    // remove them from the scene (still on the heap)
                    //scene()->removeItem(colliding_items[i]);

                    scene()->removeItem(this);

                    // delete them from the heap to save memory
                    //delete colliding_items[i];
                    delete this;

                    // return (all code below refers to a non existint bullet)
                    return;
                }
        if (typeid(*(colliding_items[i])) == typeid(Anti)){
            used = true;
                    // increase the score
                    game->score->increase();
                   Anti *anti = qgraphicsitem_cast<Anti*>(colliding_items[i]);
                    anti->get_attack(attack_potential);
                    // remove them from the scene (still on the heap)
                    //scene()->removeItem(colliding_items[i]);

                    scene()->removeItem(this);

                    // delete them from the heap to save memory
                    //delete colliding_items[i];
                    delete this;

                    // return (all code below refers to a non existint bullet)
                    return;
                }

                if (typeid(*(colliding_items[i])) == typeid(Boss)){
                    used = true;
                    // increase the score
                    game->score->increase();
                    Boss *boss = qgraphicsitem_cast<Boss*>(colliding_items[i]);
                    boss->get_attack(attack_potential);
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
    }
}
}
