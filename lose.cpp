#include "lose.h"
#include "ui_lose.h"
#include "gameengine.h"

extern GameEngine* game;

Lose::Lose(int score,int num_enemies,int level,QWidget *parent):
    QDialog(parent),
    ui(new Ui::Lose),score(score) , num_enemies(num_enemies), level(level){
    ui->setupUi(this);
    //timer = new QTimer;
    display_score();
    display_enemy_num();
    display_level();

}

Lose::~Lose()
{
    delete ui;
}

void Lose::display_score(){
     QLCDNumber* score_lcd=ui->Score;
     score_lcd->display(score);
     score_lcd->show();
}
void Lose::display_enemy_num(){
    QLCDNumber* num_lcd=ui->Enemy_num;
    num_lcd->display(num_enemies);
    num_lcd->show();
}

void Lose::display_level(){
     QLCDNumber* level_lcd=ui->level;
     level_lcd->display(level);
     level_lcd->show();
}

void Lose::on_OK_clicked()
{
    this->close();
    //game->write_in_ranking_and_finish_game();

}
