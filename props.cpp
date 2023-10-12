#include "props.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "gameengine.h"

extern GameEngine * game;

props::props()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_update()));
    timer->start(50);

}

props::~props(){delete timer;}

void props::time_update()
{
    //The prop will be automatically deleted after 7.5 seconds if the player doesn't pick it up
    time +=1;
    if(time > 150 && add_finished ==false) delete this;
    collide_check();
}

void props::collide_check()
{
    //Check the collision between the player and this object, then take actions
    //work() is the pure virtual function which will be implemented in derived classes
        QList<QGraphicsItem *> colliding_items = collidingItems();

        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if ((typeid(*(colliding_items[i])) == typeid(Player)) && (add_finished ==false)){
                work();
                add_finished = true;
                this->setVisible(false);
            }
        }
}

void props::finish()
{
    //The prop has limited period of functioning, this function will be executed to make everything go back to normal
    game->update_speed_and_potential();
    delete this;
}
