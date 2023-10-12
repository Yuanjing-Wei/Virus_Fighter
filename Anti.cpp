#include "Anti.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "gameengine.h"
#include "windows.h"
#include "virusa.h"
#include <cmath>
#include "Player.h"
#include "BloodBag.h"
#include "Freezer.h"
#include "Mask.h"
#include "Medal.h"
extern GameEngine * game;
const double PI=3.1415926;
Anti::Anti(int period , int requested_potential , int requested_speed, int requested_shooting_number ): Enemy(period,requested_potential,requested_speed,requested_shooting_number)
{
    //Add pictures to the QPixmap array
    anti_photo[0]=QPixmap(":/enemy/game_resource/enemy/a1.png");
    anti_photo[1]=QPixmap(":/enemy/game_resource/enemy/a2.png");
    anti_photo[2]=QPixmap(":/enemy/game_resource/enemy/a3.png");
    anti_photo[3]=QPixmap(":/enemy/game_resource/enemy/a4.png");
    anti_photo[4]=QPixmap(":/enemy/game_resource/enemy/a5.png");
    anti_photo[5]=QPixmap(":/enemy/game_resource/enemy/a6.png");
    anti_photo[6]=QPixmap(":/enemy/game_resource/enemy/a7.png");
    anti_photo[7]=QPixmap(":/enemy/game_resource/enemy/a8.png");
    anti_photo[8]=QPixmap(":/enemy/game_resource/enemy/a9.png");
    anti_photo[9]=QPixmap(":/enemy/game_resource/enemy/a10.png");
    anti_photo[10]=QPixmap(":/enemy/game_resource/enemy/a11.png");
    anti_photo[11]=QPixmap(":/enemy/game_resource/enemy/a12.png");
    //The default picture of the anti
    setPixmap(QPixmap(anti_photo[6]));
}
Anti::~Anti(){delete []virus;}

//Create virus(es) according to variable requested shooting number, requested speed and attack potential.
void Anti::shoot()
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
    virus = new VirusA* [requested_shooting_number];
    if(requested_shooting_number == 1)
    {
        virus[0]=new VirusA(requested_speed,requested_potential,angle);
        virus[0]->setPos(x(),y());
        scene()->addItem(virus[0]);
    }
    else {
        for(int i = 0 ; i < requested_shooting_number ; i++)
        {
          virus[i]=new VirusA(requested_speed,requested_potential,angle-PI/6+i*PI/(3*(requested_shooting_number-1)));
          virus[i]->setPos(x(),y());
          scene()->addItem(virus[i]);
        }
    }
}

//update the requested image index and switch the picture
void Anti::update_result()
{
    Enemy::update_result();
    setPixmap(anti_photo[result]);
}
