#include "BloodBag.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "ui_gameengine.h"
#include "gameengine.h"

extern GameEngine * game;
BloodBag::BloodBag(int add): props(),add(add)
{
    setPixmap(QPixmap(":/images/game_resource/images/pill.png"));
}

//utility functions to add health of the player. The bloodbag will be destructed after executing this function
void BloodBag::add_health()
{
    //Update the display in the textBrowser
   int old_health = game->health->getHealth();
   game->ui->textBrowser->setTextColor(QColor(200,15,122));   
   game->health->increase(add);
   int new_health = game->health->getHealth();
   game->ui->textBrowser->QTextEdit::append(QString("Pills obtained with health: ") + QString::number(new_health-old_health));
}

