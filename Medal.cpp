#include "Medal.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "ui_gameengine.h"
#include "gameengine.h"

extern GameEngine * game;
Medal::Medal(int add): props(),add(add)
{
    setPixmap(QPixmap(":/images/game_resource/images/medal.png"));
}

// Utility function to increase the score of the player.
// The medal will be destructed after executing this function
void Medal::add_score()
{
    game->ui->textBrowser->setTextColor(QColor(122,122,122));
    game->ui->textBrowser->QTextEdit::append(QString("Medal obtained with score bonus:") + QString::number(add));
    for(int i = 0; i < add; i++)
    game->score->increase();
}

