#include "Mask.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "gameengine.h"

extern GameEngine * game;

Mask::Mask(): props()
{
    shield_timer = new QTimer(this);
    connect(shield_timer,SIGNAL(timeout()),this,SLOT(finish()));
    setPixmap(QPixmap(":/images/game_resource/images/mask.png"));

}

Mask::~Mask(){delete shield_timer;}

// Utility function to change the speed or potential of the player.
// The mask will be destructed after executing this function
void Mask::shield()
{
    //The mask will call finish() to recover everything
    // and will be automatically deleted after 10 seconds
    shield_timer->start(10*1000);
    game->update_speed_and_potential_shield();
}
