#include "Devil.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "gameengine.h"
#include "windows.h"
#include "virusb.h"
#include <cmath>
#include "Player.h"
#include "BloodBag.h"
#include "Freezer.h"
#include "Mask.h"
#include "Medal.h"

extern GameEngine * game;
const double PI=3.1415926;

Devil::Devil(int period , int requested_potential , int requested_speed, int requested_shooting_number): Enemy(period,requested_potential,requested_speed,requested_shooting_number)
{
    //Add pictures to the QPixmap array
    devil_photo[0]=QPixmap(":/enemy/game_resource/enemy/d1.png");
    devil_photo[1]=QPixmap(":/enemy/game_resource/enemy/d2.png");
    devil_photo[2]=QPixmap(":/enemy/game_resource/enemy/d3.png");
    devil_photo[3]=QPixmap(":/enemy/game_resource/enemy/d4.png");
    devil_photo[4]=QPixmap(":/enemy/game_resource/enemy/d5.png");
    devil_photo[5]=QPixmap(":/enemy/game_resource/enemy/d6.png");
    devil_photo[6]=QPixmap(":/enemy/game_resource/enemy/d7.png");
    devil_photo[7]=QPixmap(":/enemy/game_resource/enemy/d8.png");
    devil_photo[8]=QPixmap(":/enemy/game_resource/enemy/d9.png");
    devil_photo[9]=QPixmap(":/enemy/game_resource/enemy/d10.png");
    devil_photo[10]=QPixmap(":/enemy/game_resource/enemy/d11.png");
    devil_photo[11]=QPixmap(":/enemy/game_resource/enemy/d12.png");
    //The default picture of the devil
    setPixmap(QPixmap(devil_photo[6]));
}

Devil::~Devil(){delete []virus;}

//Create virus(es) according to variable requested shooting number, requested speed and attack potential.
void Devil::shoot()
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
    virus = new VirusB* [requested_shooting_number];
    if(requested_shooting_number == 1)
    {
        virus[0]=new VirusB(requested_speed,requested_potential,angle);
        virus[0]->setPos(x(),y());
        scene()->addItem(virus[0]);
    }
    else {
        for(int i = 0 ; i < requested_shooting_number ; i++)
        {
          virus[i]=new VirusB(requested_speed,requested_potential,angle-PI/6+i*PI/(3*(requested_shooting_number-1)));
          virus[i]->setPos(x(),y());
          scene()->addItem(virus[i]);
        }
    }
}

//update the requested image index and switch the picture
void Devil::update_result()
{
    Enemy::update_result();
    setPixmap(devil_photo[result]);
}
