#include "bossvirus.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "gameengine.h"
#include <cmath>

extern GameEngine * game; // there is an external global object called game

BossVirus::BossVirus(int startx,int starty,double rad,int requested_speed,int requested_potential,qreal angle):startx(startx),starty(starty),rad(rad),Virus(Virus::VType::BOSS,requested_speed,requested_potential,0){
    // make/connect a timer to move() the bullet every so often
    //delete timer;
    //timer = new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    QPixmap virusBossImg=QPixmap(":/images/game_resource/images/bossvirus.png");
    setPixmap(QPixmap(virusBossImg));

    setPos(startx,starty);
    Virus::connect_n_start();
    //speed = 5;
    // start the timer
    //timer->start(50);
}

/*BossVirus::~BossVirus(){
    delete timer;
}*/

/*void BossVirus::check_collide(){
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Player)){
            game->health->decrease(6);

            scene()->removeItem(this);
            delete this;
            return;
        }
    }

}

void BossVirus::check_out(){
    // if the virus moves out of the range, then delete it
    if (pos().y() < 0||pos().y()>750){
        scene()->removeItem(this);
        delete this; return;
    }
    if (pos().x() < -8||pos().x()>450){
        scene()->removeItem(this);
        delete this; return;
    }
}*/


void BossVirus::move(){
    setPos(pos().x()+speed*sin(rad),pos().y()+speed*cos(rad));
    //check_collide();
    check_out();
}
