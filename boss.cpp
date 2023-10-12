#include "boss.h"
#include <cmath>
#include <QTimer>
#include "gameengine.h"

const double PI = 3.1415926;
extern GameEngine * game;

Boss::Boss()
{
    boss_image = QPixmap(":/enemy/game_resource/enemy/gameboss.png");
    //boss_image = QPixmap(":/enemy/boss1.png").scaled(QSize(350,350),Qt::KeepAspectRatio);
    setPixmap(boss_image);
    x=game->player->pos().x();
    y=-5;
    if(x>200) x =200;
    if(x<100) x = 100;

    setPos(x,y);
    prev_x=x;
    prev_y=y;

    raise=2;
    angle=0;
    width = boss_image.width();
    height = boss_image.height();

    movex=0;
    movey=180;

    boss_timer = new QTimer(this);
    connect(boss_timer,SIGNAL(timeout()),this,SLOT(Move()));
    boss_timer->start(80);
    game->scene->addItem(this);

    shoot_timer = new QTimer(this);
    connect(shoot_timer,SIGNAL(timeout()),this,SLOT(Shoot_Barrage()));
    shoot_timer->start(150);

    count_cycle = 0;
    health = new Health(1000);

}

/*
    Compared with ordinary enemies, the boss has more patterns of moving and shooting. Its bullet
    has higher attack potential and dierent image. Move pattern is the indicator of the move state of
    the boss, and the movement of the boss is controlled by the following member function move()
*/
void Boss::Move()
{   
    switch(move_pattern){
        case 0:
            Appear();
            break;
        case 1:
            Move1();
            break;
        case 2:
            Move2();
            break;
    }
    setPos(x,y);

}
/*
    The following function handles the way that the boss appears, sin function is used to make the
    movement more smoothly.
*/
void Boss::Appear()
{
    double temp;

    angle+=2;

    temp=sin(angle*PI/180);

    //x = 180;
    y = prev_y+temp*movey;

    if(angle==90){
        //angle=0;
        move_pattern=1;
        //shotflag=true;
    }
}

/*
    The boss will "swing" back and forth (as the function of y suggests) in the screen as the angle
    increases, Move2() will be executed once the angle reaches 450 degrees (angle is reset to 90 in
    order to prevent the integer being too large because only the remainder matters).
*/

void Boss::Move1()
{
    angle+=raise;

    //y=80+sin(angle*PI/180)*100;
    y = prev_y+sin(90*PI/180)*movey-sin(1.5*(angle-90)*PI/180)*70;

    if(angle % 360==90){
        raise=-2;
        angle = 90;
        count_cycle=count_cycle+1;
    }else if(angle % 360==-90 || angle % 360==270){
        raise=2;
    }

    if(count_cycle == 1)
    {move_pattern=2;}
}

/*
    In this stage, the boss will move in a "curved" way.
    When the boss is moving in above ways, it's also shooting simultaneously. The shooting pattern of
    the boss can be divided into two genres.
*/

void Boss::Move2()
{
   angle+=2;
    x = prev_x+50*cos(3*angle*PI/180);
}

/*
    Shoot Barrage() produces a barrage of bullets heading towards the player with random discrepancy
    ranging from 5 degrees. It's worthy to note that the shooting mode will change to Shoot Circle()
    after a given period of time
*/

void Boss::Shoot_Barrage()
{
    if(game->is_end())
        return;
    BossVirus* shoot = new BossVirus(x+width/2,y+height/2,atan((x+width/2-game->player->x())/(y+height/2-game->player->y()))+ (rand() % 5)*PI/180,5,6,0);
    game->scene->addItem(shoot);
    time+=1;
    //qDebug()<< "Time now: "<<time;
    if(floor(time / 10) == 6)
    {
        shoot_timer->stop();
        disconnect(shoot_timer,SIGNAL(timeout()),this,SLOT(Shoot_Barrage()));
        connect(shoot_timer,SIGNAL(timeout()),this,SLOT(Shoot_Circle()));
        time = 0;
        shoot_timer->start(150);
    }

}

/*
    For Shoot Circle(), bullets will be divided into ve branches and spread out. It's worthy to
    note that the shooting mode will change to Shoot Barrage() after a given period of time. So a
    circulation of shooting between Shoot Barrage() and Shoot Circle() is formed.
*/

void Boss::Shoot_Circle()
{
    if(game->is_end())
        return;
    virus_angle+=PI/15;
    for(int i=0;i<5;i++)
    {
        BossVirus* shoot = new BossVirus(x+width/2,y+height/2,virus_angle+i*2*PI/5,5,6,0);
        game->scene->addItem(shoot);
    }

    time+=1;
    if(floor(time / 10) == 6)
    {
        time = 0;
        shoot_timer->stop();
        disconnect(shoot_timer,SIGNAL(timeout()),this,SLOT(Shoot_Circle()));
        connect(shoot_timer,SIGNAL(timeout()),this,SLOT(Shoot_Barrage()));
        shoot_timer->start(150);
    }

}

Boss::~Boss()
{
    delete shoot_timer;
    delete boss_timer;
    delete health;
}

void Boss::get_attack(int attack)
{
    health->decrease(attack);
    if(health->getHealth() <= 0)
    {
        game->score->increase();
       // if(get_prop > 75)
       // {
            // To randomly choose the prons get
       // }

        /*BloodBag* bloodbag = new BloodBag(50);
        scene()->addItem(bloodbag);*/
        boss_is_killed=true;
        scene()->removeItem(this);
        delete this;
        return;
    }
}

