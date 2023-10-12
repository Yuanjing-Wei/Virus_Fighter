#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "gameengine.h"
#include "Player.h"
#include "BloodBag.h"
#include "Freezer.h"
#include "Mask.h"
#include "Medal.h"

extern GameEngine * game;

Enemy::Enemy(int period , int requested_potential , int requested_speed, int requested_shooting_number,QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent),period(period),requested_potential(requested_potential),requested_speed(requested_speed)
  ,requested_shooting_number(requested_shooting_number){
    //set random x position
    srand(time(NULL));
    int random_number = rand() % 420;
    setPos(random_number,0);

    health = new Health(30);

     timer = new QTimer(this);
     connect(timer,SIGNAL(timeout()),this,SLOT(handle_move()));

     connect(timer,SIGNAL(timeout()),this,SLOT(shoot()));

     timer->start(period);

     get_prop = rand() % 100;


}


Enemy::~Enemy()
{
    delete health;
    delete timer;
}

void Enemy::handle_move(){

    xcount=0;
    ycount=0;
    ix=0;
    iy=0;
    result=0;
    QTimer * timer_for_move_inertia = new QTimer(this);
    timer_for_move_inertia->setSingleShot(1);
    timer_for_move_inertia->start(999);
    QTimer * timer_for_move = new QTimer(this);
    timer_for_move->start(50);

    connect(timer_for_move_inertia,SIGNAL(timeout()),timer_for_move,SLOT(stop()));
    //if(timer_for_move_inertia->isActive()) return;

    int random_number = rand() % 100;
    if(random_number <= 60){
    connect(timer_for_move,SIGNAL(timeout()),this,SLOT(move()));}
    else if(random_number > 60 && random_number <= 80)
    {connect(timer_for_move,SIGNAL(timeout()),this,SLOT(move_left()));}
    else if(random_number > 80)
    {connect(timer_for_move,SIGNAL(timeout()),this,SLOT(move_right()));}

}

void Enemy::get_attack(int attack)
{
    health->decrease(attack);
    if(health->getHealth() <= 0)
    {
        //qDebug()<< "OK";
        game->score->increase();
        if(get_prop > 50)
        {
            if(get_prop>=88)
            {
                BloodBag* bloodbag = new BloodBag(10);
                scene()->addItem(bloodbag);
                bloodbag->setPos(pos().x(),pos().y());
            }
            else if(get_prop>=76)
            {
                Freezer* freezer = new Freezer();
                scene()->addItem(freezer);
                freezer->setPos(pos().x(),pos().y());
            }
            else if(get_prop>=64)
            {
                Mask* mask = new Mask();
                scene()->addItem(mask);
                mask->setPos(pos().x(),pos().y());
            }
            else if(get_prop>=50)
            {
                Medal* medal = new Medal(10);
                scene()->addItem(medal);
                medal->setPos(pos().x(),pos().y());
            }
        }
        scene()->removeItem(this);
        game->enemy_num++;
        delete this;
        return;
    }
}

void Enemy::move(){
    // move enemy down
    setPos(x(),y()+2);

    if(ycount<0)
        ycount=0;
    ++ycount;


    // destroy enemy when it goes out of the screen
    if (pos().y() > 800){
        //decrease the health
        game->health->decrease(2);

        scene()->removeItem(this);
        delete this;
        return;
    }
    update_result();
}


void Enemy::move_right(){
    // move enemy down
    if(xcount<0)
        xcount=0;
    ++xcount;
    setPos(x()+2,y());

    // destroy enemy when it goes out of the screen
    if (pos().x() > 410){
        scene()->removeItem(this);
        delete this;
        return;
    }
   update_result();
}


void Enemy::move_left(){
    if(xcount>0)
        xcount=0;
    --xcount;
    // move enemy down

    setPos(x()-2,y());

    // destroy enemy when it goes out of the screen
    if (pos().x() < 0){
        scene()->removeItem(this);
        delete this;
        return;
    }
    update_result();
}

void Enemy::update_result()
{
    ix=abs(xcount)%30/10;
    iy=abs(ycount)%30/10;

    if(xcount>0){
        ix+=3;
        result=ix;
    }else if(xcount<0){
        ix+=9;
        result=ix;
    }


    if(ycount>0){
        iy+=6;
        result=iy;
    }else if(ycount<0){
        iy+=0;
        result=iy;
    }

}
