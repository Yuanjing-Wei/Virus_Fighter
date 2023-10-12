#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    score = 0;
}

void Score::increase(){
    score++;
}

int Score::getScore(){
    return score;
}
