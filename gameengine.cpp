#include "gameengine.h"
#include "ui_gameengine.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "windows.h"
#include <iostream>
#include "Enemy.h"
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <QTimer>
#include "Button.h"
#include <QFont>
#include "boss.h"
#include <QFileDialog>
#include <QTextStream>
#include "win.h"
#include "lose.h"
#include "virusc.h"
#include "WildAnimal.h"
#include "Anti.h"
#include "Devil.h"
#include <stdlib.h>

//using namespace std;

bool VirusC::allow_infect=false;
bool Boss::boss_is_killed=false;

GameEngine::GameEngine(QString name,QWidget *parent):ui(new Ui::GameEngine),name(name)//: ui(new Ui::GameEngine)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/background/game_resource/background/game_background.jpg")));
    scene->setSceneRect(0,0,430,780);
    //ui->graphicsView->setSceneRect(scene->sceneRect());
    ui->graphicsView->setFocus();

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QFont newFont("Courier", 8, QFont::Bold, true);
    ui->textBrowser->setFont(newFont);

    game_begin();
}

GameEngine::~GameEngine()
{
    delete scene;
    delete timer_for_enemy;
    delete timer_for_boss;
    delete timer_for_focus;

    delete player;
    delete score;
    delete ui;
    delete timer_for_clock;
    delete timer_for_level;
    delete main_background_music;
}

void GameEngine::Quit_clicked()
{
    // A short cut to end the game
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Escape warning","You will lose all the data once you exit. Are you sure to proceed?",
                                                        QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
    {
       close();
     //MainWindow* w=new MainWindow;
     //w->show();

    }
    else{}
}
void GameEngine::game_begin()
{
    // create the player
    player = new Player();
    player->setPos(210,500); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add the player to the scene
    scene->addItem(player);

    // create the score
    score = new Score();
    scene->addItem(score);
    score->setPos(score->x()+430,score->y()+90);

    // create the health and set it to 100
    health = new Health(100);
    health->setPos(health->x()+430,health->y()+130);
    scene->addItem(health);


    /*
    Unlike the game implemented in PA4 and other similar games, the shooting game requires not
    only the input event-based reaction of the program, but also the capability of continuing the game
    smoothly in parallel with the player's input. As a result, several QTimer are used to update dierent
    displays and parameters in the game to bring about better game experience. In addition, there are
    utility functions used to handle the update of parameters and GUI surface.
    */

    // timer_for_enemy will invoke spawn() every period of time
    timer_for_enemy = new QTimer();
    QObject::connect(timer_for_enemy,SIGNAL(timeout()),this,SLOT(spawn()));

    // timer_for_focus is in charge of the update of score, health, and
    // level readings on the GUI surface as well as setting the focus (to prevent other programs
    // interrupting the keyboard input)
    timer_for_focus = new QTimer();
    QObject::connect(timer_for_focus,SIGNAL(timeout()),this,SLOT(set_focus()));
    QObject::connect(timer_for_focus,SIGNAL(timeout()),this,SLOT(set_score()));
    QObject::connect(timer_for_focus,SIGNAL(timeout()),this,SLOT(set_health()));
    QObject::connect(timer_for_focus,SIGNAL(timeout()),this,SLOT(set_level()));
    timer_for_focus->start(500);

    //This is the clock on the game GUI surface, so it will update every second
    timer_for_clock = new QTimer();
    QObject::connect(timer_for_clock,SIGNAL(timeout()),this,SLOT(set_time()));
    timer_for_clock->start(1000);

    //Update the level based on the score criterion
    timer_for_level = new QTimer();
    QObject::connect(timer_for_level,SIGNAL(timeout()),this,SLOT(level_control()));
    timer_for_level->start(200);

    // play background music
    main_background_music = new QMediaPlayer();
    main_background_music->setMedia(QUrl("qrc:/music/game_resource/music/infinite.mp3"));
    main_background_music->play();

    //QGraphicsView::show();

    //This is the function used for debug, it's not appeared on the real GUI surface
    Button* button = new Button("Quit");
    button->setPos(500,60);
    connect(button,SIGNAL(clicked()),this,SLOT(Quit_clicked()));
    scene->addItem(button);

}

//This is the function used for debug, it's not appeared on the real GUI surface
void GameEngine::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void GameEngine::update_speed_and_potential()
{
    //If the level has been increased, the function will be invoked to upgrade
    //different parameters of enemies (and virus) produced
    int layer = level-1;
    for(int i=0;i<3;++i)
        enemy_parameters[i]=level_array[layer][i];

}

void GameEngine::update_speed_and_potential_frozen()
{
    //If the freezer(disinfector) has been obtained, the function will be invoked to upgrade
    //different parameters of enemies (and virus) produced
    this->ui->textBrowser->setTextColor(QColor(0,0,255));
    this->ui->textBrowser->QTextEdit::append("Freezer obtained!");

    int layer = level-1;
    for(int i=0;i<3;++i)
        enemy_parameters[i]=level_array_frozen[layer][i];

}

void GameEngine::update_speed_and_potential_shield()
{

    //If the mask has been obtained, the function will be invoked to upgrade
    //different parameters of enemies (and virus) produced
    this->ui->textBrowser->setTextColor(QColor(0,255,0));
    this->ui->textBrowser->QTextEdit::append("Mask obtained!");

    int layer = level-1;
    for(int i=0;i<3;++i)
        enemy_parameters[i]=level_array_shield[layer][i];

}

//This is the function used for debug, it's not appeared on the real GUI surface
void GameEngine::drawGUI(){
    // draw the right panel
    drawPanel(420,0,180,800,Qt::white,1);

    // place player 1 text
    QGraphicsTextItem* p2 = new QGraphicsTextItem("Game Panel");
    QFont f;
    f.setPixelSize(22);
    f.setBold(true);
    p2->setFont(f);
    p2->setPos(460,20);
    scene->addItem(p2);
}

void GameEngine::create_boss(){
    //A boss will be created on certain stage of the game
    this->ui->textBrowser->setTextColor(QColor(30,104,97));
    this->ui->textBrowser->QTextEdit::append("Boss is coming!");
    boss = new Boss;
}

void GameEngine::set_focus()
{
    //If we don't set focus to the player from time to time, our keyboard input
    //would lose connect once we click the game surface.
    player->setFocus();
}

void GameEngine::game_logic_control()
{
    //This function is used to control the freqeuncy of the production of enemies, it can be seen that
    //the frequency becomes larger as level becomes higher.
    switch (level) {
        case 1:{
        timer_for_enemy->start(5000);
        break;
    }
        case 2:{
        timer_for_enemy->start(4000);
        break;
    }
        case 3:{
        VirusC::allowInfect();
        timer_for_enemy->start(3500);
        break;
    }
        case 4:{
        timer_for_enemy->start(3000);
        //timer_for_boss->start(200);
        break;
    }
        case 5:{
        create_boss();
        timer_for_enemy->start(3000);
        //timer_for_boss->start(1000);
        break;
    }

    }
}
void GameEngine::level_control()
{
    //This function is used to check and upgrade the level of the player, then invoke different functions
    //to create events (), it can be seen that
    //the level of the player is determined by its score.

    //level_new is the variable determined in the current vall of level_control() function
    int level_new = 0;
    int score_new = score->getScore();
    //if(health->getHealth() == 0 && end == false && score_new <= 170)

    //To finish the game boss need to be killed and health runs out or time runs out
    if(!Boss::bossIsKilled()&&(health->getHealth() <= 0||time<=0) && end == false)
    {
        this->close();
        //qDebug() << "Game finished";
        Lose* new_lose = new Lose(score->getScore(),enemy_num,level,this);
        new_lose->show();
        // play background music
        main_background_music->stop();
        QMediaPlayer * music = new QMediaPlayer();
        music->setMedia(QUrl("qrc:/music/game_resource/music/sprint.mp3"));
        music->play();

        end = true;
        return;
    }
    //else if((score_new>=380||Boss::bossIsKilled())&&time>=0&&health->getHealth()>=0&&end==false)
    else if((score_new>=380||Boss::bossIsKilled())&&(time<=0||health->getHealth()<=0)&&end==false)
    {
        this->close();
        //qDebug() << "Game finished";
        //this->setVisible(false);
        //timer_for_enemy->stop();
        //timer_for_boss->stop();
        //timer_for_clock->stop();
        //timer_for_focus->stop();
        //timer_for_level->stop();
        score_record = score->getScore();
        Win* new_win = new Win(score->getScore(),enemy_num,this);
        new_win->show();
        // play background music
        main_background_music->stop();
        QMediaPlayer * music = new QMediaPlayer();
        music->setMedia(QUrl("qrc:/music/game_resource/music/legends never die.mp3"));
        music->play();

        end = true;
        //write_in_ranking_and_finish_game(); //execute final progam after win has beem closed
        return;
    }
    else if(score_new < 40) level_new = 1;
    else if(score_new < 80) level_new = 2;
    else if(score_new < 120) level_new = 3;
    else if(score_new < 170) level_new = 4;
    else if(score_new < 380&&!Boss::bossIsKilled()) level_new = 5;
    //else if(score_new >= 380 && time >= 0 && health->getHealth() > 0) level_new = 5;
    //else if(score_new > 380 && (time <= 0 || health->getHealth() == 0) && end == false)
    /*else if(Boss::bossIsKilled()&&time>=0&&health->getHealth()>=0&&end==false)
    {
        this->close();
        qDebug() << "Game finished";
        //this->setVisible(false);
        //timer_for_enemy->stop();
        //timer_for_boss->stop();
        //timer_for_clock->stop();
        //timer_for_focus->stop();
        //timer_for_level->stop();
        score_record = score->getScore();
        Win* new_win = new Win(score->getScore(),enemy_num,this);
        new_win->show();


        end = true;
        //write_in_ranking_and_finish_game(); //execute final progam after win has beem closed
    }*/

    // The following statements will be executed only when there's discrepancy between old level and new level
    // Event-based reaction to save resource
    if(level_new != level && level_new != 0)
    {
        level = level_new;
        player->level_up(level_new);
        update_speed_and_potential();
        game_logic_control();
        if(level_new == 1)
        {
            this->ui->textBrowser->setTextColor(QColor(255,0,0));
            this->ui->textBrowser->QTextEdit::append("Game Start!");
        }
        else
        {
            this->ui->textBrowser->setTextColor(QColor(255,0,0));
            this->ui->textBrowser->QTextEdit::append("Level up to " + QString::number(level_new) + " !");
        }
            //qDebug() << "Level now: "<<level;
    }

}

void GameEngine::write_in_ranking_and_finish_game()
{
    //This function will be executed if the player wins, it will write the player's name and player's score

    QString filename = QFileDialog::getOpenFileName(this, tr("Open Map File"), ".", tr("Text Files (*.txt)"));
        //qDebug() << filename;  // You can use qDebug() for debug info
        if (filename == "") return;
    //ofstream players_and_units_file(filename.toStdString());
        QFile qFile(filename);

        // Write in the name and score of the player
        if (qFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream out(&qFile);
            qDebug()<<name;
            out <<"\n";
            out << name <<" "<< QString::number(score_record);
            //qFile.flush();
            qFile.close();
        }

        // Create the ranking object
        Ranking* ranking = new Ranking(filename);
        ranking->exec();

}

//Set the score on the GUI surface
void GameEngine::set_score()
{
    QLCDNumber* lcd=ui->Score;
    lcd->display(score->getScore());
    lcd->show();
}

//Set the health on the GUI surface
void GameEngine::set_health()
{
    QProgressBar* health_dis=ui->Health;
    health_dis->setValue(health->getHealth());
    health_dis->show();
}

//Set the level on the GUI surface
void GameEngine::set_level()
{
    QLCDNumber* level_lcd=ui->Level;
    level_lcd->display(level);
    level_lcd->show();
}

//Set the time on the GUI surface
void GameEngine::set_time()
{
    time-=1;
    QLCDNumber* time_lcd=ui->Time_left;
    time_lcd->display(time);
    time_lcd->show();
    //if(time == 110) create_boss();
    //if(time == 50) create_boss();
}

//If quit is clicked, the game will end automatically
void GameEngine::on_Esc_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Escape warning","You will lose all the data once you exit. Are you sure to proceed?",
                                                        QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
    {
       close();
     //MainWindow* w=new MainWindow;
     //w->show();

    }
    else{}
}

//Function used to create enemies on a random basis
void GameEngine::spawn(){
    // create an enemy
    if(this->is_end())
        return;
    //srand(time(NULL));
    int choice = rand() % 3;
    switch (choice) {
        case 0:
        {
            Anti * enemy = new Anti(enemy_parameters[0][0],enemy_parameters[0][1],enemy_parameters[0][2],enemy_parameters[0][3]);
            scene->addItem(enemy);
            break;
        }

        case 1:
        {
            Devil * enemy = new Devil(enemy_parameters[1][0],enemy_parameters[1][1],enemy_parameters[1][2],enemy_parameters[1][3]);
            scene->addItem(enemy);
            break;
        }
        case 2:
        {
            WildAnimal * enemy = new WildAnimal(enemy_parameters[2][0],enemy_parameters[2][1],enemy_parameters[2][2],enemy_parameters[2][3]);
            scene->addItem(enemy);
            break;
        }

    }

}
