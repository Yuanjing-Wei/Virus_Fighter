#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

Bullet::Bullet(Type type,QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent), type(type){
    timer=new QTimer(this);
}

Bullet::~Bullet(){delete timer;}

void Bullet::check_out(){
    // if the bullet is off the screen, destroy it //parameters to be changed to const
    if (pos().x()<BULLET_BOUNDS[0]||pos().x()>BULLET_BOUNDS[1]||pos().y() < BULLET_BOUNDS[2]||pos().y()>BULLET_BOUNDS[3]){
        scene()->removeItem(this);
        delete this;
    }
}

void Bullet::connect_n_start(){
    // make/connect a timer to move() the bullet every so often
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(timer,SIGNAL(timeout()),this,SLOT(attack()));

    // start the timer
    timer->start(50);
}
