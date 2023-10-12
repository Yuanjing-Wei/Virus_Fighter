#include "WildAnimal.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "gameengine.h"
#include "windows.h"
#include "virusc.h"
#include <cmath>
#include "Player.h"
#include "BloodBag.h"
#include "Freezer.h"
#include "Mask.h"
#include "Medal.h"

extern GameEngine * game;
const double PI=3.1415926;

WildAnimal::WildAnimal(int period , int requested_potential , int requested_speed , int requested_shooting_number): Enemy(period,requested_potential,requested_speed,requested_shooting_number)
{
    //Add pictures to the QPixmap array
    wildanimal_photo[0]=QPixmap(":/enemy/game_resource/enemy/w1.png");
    wildanimal_photo[1]=QPixmap(":/enemy/game_resource/enemy/w2.png");
    wildanimal_photo[2]=QPixmap(":/enemy/game_resource/enemy/w3.png");
    wildanimal_photo[3]=QPixmap(":/enemy/game_resource/enemy/w4.png");
    wildanimal_photo[4]=QPixmap(":/enemy/game_resource/enemy/w5.png");
    wildanimal_photo[5]=QPixmap(":/enemy/game_resource/enemy/w6.png");
    wildanimal_photo[6]=QPixmap(":/enemy/game_resource/enemy/w7.png");
    wildanimal_photo[7]=QPixmap(":/enemy/game_resource/enemy/w8.png");
    wildanimal_photo[8]=QPixmap(":/enemy/game_resource/enemy/w9.png");
    wildanimal_photo[9]=QPixmap(":/enemy/game_resource/enemy/w10.png");
    wildanimal_photo[10]=QPixmap(":/enemy/game_resource/enemy/w11.png");
    wildanimal_photo[11]=QPixmap(":/enemy/game_resource/enemy/w12.png");
    //The default picture of the whid animal
    setPixmap(QPixmap(wildanimal_photo[6]));
}

WildAnimal::~WildAnimal(){delete []virus;}

//Create virus(es) according to variable requested shooting number, requested speed and attack potential.
void WildAnimal::shoot()
{
    if(game->is_end())
        return;

    //calculating the current angle between the player and the shooter
    //so the virus(es) look(s) like heading to the player
    QLineF ln(QPointF(x(),y()),game->player->get_attack_dest());
    qreal angle=-::acos(ln.dx()/ln.length())+PI/2;
    if(ln.dy()<0)
        angle=PI-angle;

    //Avoid memory leak in previous shooting (the virus will be automatically deleted
    //in it goes out of the bound or attach the player)
    if(virus!=nullptr) delete []virus;
    //generate new virus/viruses with respect to the current game status
    virus = new VirusC* [requested_shooting_number];

    if(requested_shooting_number == 1)
    {
        virus[0]=new VirusC(requested_speed,requested_potential,angle);
        virus[0]->setPos(x(),y());
        scene()->addItem(virus[0]);
    }
    else {
        for(int i = 0 ; i < requested_shooting_number ; i++)
        {
          virus[i]=new VirusC(requested_speed,requested_potential,angle-PI/6+i*PI/(3*(requested_shooting_number-1)));
          virus[i]->setPos(x(),y());
          scene()->addItem(virus[i]);
        }
    }
}

//update the requested image index and switch the picture
void WildAnimal::update_result()
{
    Enemy::update_result();
    setPixmap(wildanimal_photo[result]);
}
