#include "Health.h"
#include <QFont>

Health::Health(int health, QGraphicsItem *parent): QGraphicsTextItem(parent), health(health){
    // initialize the score to 0
    //health = 100;

  /*  // draw the text
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));*/
}

void Health::decrease(int attack){
    health-=attack;
    if(health <=0) health = 0;
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 2
}

void Health::increase(int add){
    health+=add;
    //Set the upper limit for the health to be 100
    if(health > 100) health = 100;
    //setPlainText(QString("Health: ") + QString::number(health)); // Health: 2
}

int Health::getHealth(){
    return health;
}

