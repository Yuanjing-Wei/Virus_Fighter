#include "Player.h"
#include <QKeyEvent>
#include <windows.h>
#include "weapon.h"
#include <cmath>
#include <QTimer>
#include "gameengine.h"

extern GameEngine * game;
const double PI = 3.1415926;
Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    //The default picture of the player
    setPixmap(QPixmap(":/player/game_resource/player/p1.png"));

    //Add pictures to the QPixmap array
    player_photo[0]=QPixmap(":/player/game_resource/player/p1.png");
    player_photo[1]=QPixmap(":/player/game_resource/player/p2.png");
    player_photo[2]=QPixmap(":/player/game_resource/player/p3.png");
    player_photo[3]=QPixmap(":/player/game_resource/player/p4.png");
    player_photo[4]=QPixmap(":/player/game_resource/player/p5.png");
    player_photo[5]=QPixmap(":/player/game_resource/player/p6.png");
    player_photo[6]=QPixmap(":/player/game_resource/player/p7.png");
    player_photo[7]=QPixmap(":/player/game_resource/player/p8.png");
    player_photo[8]=QPixmap(":/player/game_resource/player/p9.png");
    player_photo[9]=QPixmap(":/player/game_resource/player/p10.png");
    player_photo[10]=QPixmap(":/player/game_resource/player/p11.png");
    player_photo[11]=QPixmap(":/player/game_resource/player/p12.png");

    //To prevent the continus pressing of the space (which will emit tons of weapons), QTimer shooting_inertia
    //is used to "ignore" the keyboard space input in a given period
    shooting_inertia = new QTimer(this);
    shooting_inertia->start(200);
    shooting_inertia->setSingleShot(true);

}

void Player::keyPressEvent(QKeyEvent *event){
    //Use an array key[] to present the status of the keys A,S,W,D and space. When user press
    //and release the keyboard, record the behavior press as 1 and release as 0.

    switch ( event->key() )
        {
        case Qt::Key_W:
            key[0] = 1;
            break;
        case Qt::Key_S:
            key[1] = 1;
            break;
        case Qt::Key_A:
            key[2] = 1;
            break;
        case Qt::Key_D:
            key[3] = 1;
            break;
        case Qt::Key_Space:
            key[4] = 1;
            break;
        }

        emit move();

        //setFocus();
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch ( event->key() )//event->isAutoRepeat()
        {
        case Qt::Key_W:
            key[0] = 0;
            break;
        case Qt::Key_S:
            key[1] = 0;
            break;
        case Qt::Key_A:
            key[2] = 0;
            break;
        case Qt::Key_D:
            key[3] = 0;
            break;
        case Qt::Key_Space:
            key[4] = 0;
            break;
        }
    setFocus();
}

void Player::level_up(int level)
{
    requested_shooting_number = level*0.7+1;
    requested_speed = 10 + level*0.6;
    attack_potential = 5 + level*0.5;
}

/*
    When user press ASWD, the player will move left, downward, upward and right, unless it
    is at the boundary. When space is pressed, if the game is not end and the last bullet has
    been shot for more than 200ms, create bullet(s). The variable result is used to determine the
    moving direction of the player and show the corresponding graph.
    You can refer to the documentation for a more fluent explanation
*/
void Player::move()
{
    if(key[0]){
        if(pos().y()>=-3)
            setPos(x(),y()-5);
        else
            setPos(x(),-8);
    }
    if(key[1]){
        if(pos().y()<=740)
            setPos(x(),y()+5);
        else
            setPos(x(),750);
    }
    if(key[2]){
        if(pos().x()>=-8)
            setPos(x()-5,y());
        else
            setPos(-10,y());
    }
    if(key[3]){
        if(pos().x()<415)
            setPos(x()+5,y());
        else
            setPos(418,y());
    }
    if(key[4]){
        if(game->is_end()||y()<=-5)
            return;
        if(shooting_inertia->remainingTime() > 0)
           return;
        shooting_inertia->start(200);
        shooting_inertia->setSingleShot(true);
        create_bullet_and_sound(x(),y());
    }

    //If the player moves to the right, then xcount should be positive and its value increases 1 once right
    // press is detected, and vice versa. If none of the keys are pressed, both values will set to 0.

    if(key[2]==1){
        if(xcount>0)
            xcount=0;
        --xcount;
    }

    if(key[3]==1){
        if(xcount<0)
            xcount=0;
        ++xcount;
    }

    if(key[0]==1){
        if(ycount>0)
            ycount=0;
        --ycount;
    }

    if(key[1]==1){
        if(ycount<0)
            ycount=0;
        ++ycount;
    }

    //The player would be rather rigid if it stands still during moving, so ix and iy are used
    //to create periodically "replacement" (by using modulus arithmetic) of the photo to show that the
    //player is "walking".

    ix=abs(xcount)%30/10;
    iy=abs(ycount)%30/10;

    /* 0,3,6,9 are the numbers to "lift" the ix /iy to the given
    row of the photo (please note that the array index is numbered from rst row to last row, from
    leftmost column to rightmost column in a given row). The sign of xcount /ycount is used to
    determine the selection of the photo. */

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

    //make sure the hierarchy between directions such that the player will go "right" if it
    //moves right and up simultaneously.
    if((key[0]&&key[2])||(key[0]&&key[3])||(key[1]&&key[2])||(key[1]&&key[3]))
        result=ix;


    if(key[2]!=1 && key[3]!=1){
        xcount=0;
    }
    if(key[0]!=1 && key[1]!=1){
        ycount=0;
    }
    //Set the reult of the photo
    setPixmap(player_photo[result]);

    //setFocus();
}


//Create weapon(s) according to variable requested shooting number, requested speed and attack potential.
//Parameter x, y are the position to create the bullet.
void Player::create_bullet_and_sound(int x, int y)
{
    // orientation angle of the bullet
    double angle = PI;

        if(weapon != nullptr)   delete []weapon;

        weapon = new Weapon* [requested_shooting_number];
        //shooting only one bullet
        if(requested_shooting_number == 1)
        {
            weapon[0]=new Weapon(requested_speed,attack_potential,angle);
            weapon[0]->setPos(x,y);
            scene()->addItem(weapon[0]);
        }
        else {
            //Multiple bullets
            for(int i = 0 ; i < requested_shooting_number ; i++)
            {
                //The weapon is emitted with in a range of angle plue/minus PI/6
              weapon[i]=new Weapon(requested_speed,attack_potential,angle-PI/6+i*PI/(3*(requested_shooting_number-1)));
              weapon[i]->setPos(x,y);
              scene()->addItem(weapon[i]);
            }
        }
}

Player::~Player()
{
    delete this;
}
