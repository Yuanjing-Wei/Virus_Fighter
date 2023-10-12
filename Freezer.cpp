#include "Freezer.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "gameengine.h"
#include <QDebug>

extern GameEngine * game;
Freezer::Freezer(): props()
{
    freeze_timer = new QTimer(this);
    connect(freeze_timer,SIGNAL(timeout()),this,SLOT(finish()));
    setPixmap(QPixmap(":/images/game_resource/images/disinfector.png"));
}

Freezer::~Freezer(){delete freeze_timer;}

//utility functions to decrease the speed and attack potential of
//the player. The freezer will be destructed after executing this function
void Freezer::freeze()
{
    //The freezer will call finish() to recover everything
    // and will be automatically deleted after 10 seconds
    freeze_timer->start(10*1000);
    game->update_speed_and_potential_frozen();
}
