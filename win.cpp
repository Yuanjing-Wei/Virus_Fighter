#include "win.h"
#include "ui_win.h"
#include "gameengine.h"

extern GameEngine* game;

Win::Win(int score,int num_enemies,QWidget *parent):
    QDialog(parent),
    ui(new Ui::Win),score(score) , num_enemies(num_enemies){
    ui->setupUi(this);
    this->show();
    display_score();
    display_enemy_num();
}

Win::~Win()
{
    delete ui;
}

//Fuction not used
void Win::random(){
     QLCDNumber* score_lcd=ui->Score;
     score_lcd->display(score);
     score_lcd->show();
}

//Function used to display the score
void Win::display_score(){
     QLCDNumber* score_lcd=ui->Score;
     score_lcd->display(score);
     score_lcd->show();
}

//Function used to display the number of the enemy
void Win::display_enemy_num(){
    QLCDNumber* num_lcd=ui->Enemy_num;
    num_lcd->display(num_enemies);
    num_lcd->show();
}

//After OK is clicked, function write_in_ranking_and_finish_game() will be executed to update and display the ranking
void Win::on_OK_clicked()
{
    this->setVisible(false);
    game->write_in_ranking_and_finish_game();
}
