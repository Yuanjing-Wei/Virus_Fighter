#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "Player.h"
#include "Enemy.h"
#include <QObject>
#include "Score.h"
#include "Health.h"
#include <QGraphicsView>
#include "boss.h"
#include <vector>
using namespace std;

namespace Ui {
class GameEngine;
}

class GameEngine :  public QMainWindow
{
    Q_OBJECT

public:
    explicit GameEngine(QString name = NULL,QWidget *parent = nullptr);
    ~GameEngine();
    void game_begin();
    void update_speed_and_potential();
    void update_speed_and_potential_frozen();
    void update_speed_and_potential_shield();
    void write_in_ranking_and_finish_game();
    Player* player=nullptr;
    Score* score=nullptr;
    Health * health=nullptr;
    QGraphicsScene *scene=nullptr;
    int level = 0;
    QString name;
    Ui::GameEngine *ui=nullptr;
    int enemy_num = 0;
    bool is_end(){return end;}


private slots:
    void Quit_clicked();
    void create_boss();
    void set_focus();
    void game_logic_control();
    void level_control();
    void set_score();
    void set_health();
    void set_level();
    void set_time();
    void spawn();


    void on_Esc_clicked();

private:

    void drawGUI();
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);

    QTimer* timer_for_enemy=nullptr;
    QTimer* timer_for_boss=nullptr;
    QTimer* timer_for_clock=nullptr;
    QTimer* timer_for_focus=nullptr;
    QTimer* timer_for_level=nullptr;
    vector<vector<int>> enemy_parameters={{1000,3,10,1},{1000,3,10,1},{1000,3,10,1}};

    vector<vector<vector<int>>> level_array={ {{1500,2,6,1},{2500,2,7,1},{2500,3,7,1}},
                                      {{1500,2,6,1},{2500,2,7,1},{2000,3,9,2}},
                                      {{1000,2,8,2},{2000,2,9,2},{1500,3,10,2}},
                                      {{1000,2,9,2},{1500,2,10,3},{1500,3,11,2}},
                                      {{1000,2,10,3},{1000,2,10,2},{1500,3,11,3}}
                                      } ;

    vector<vector<vector<int>>> level_array_frozen={ {{2000,2,4,1},{3000,2,5,1},{3000,3,5,1}},
                                                     {{2000,2,4,1},{2500,2,5,1},{2500,3,6,1}},
                                                     {{1500,2,5,1},{2500,2,6,1},{2000,3,6,1}},
                                                     {{1500,2,5,2},{2000,2,6,2},{2000,3,7,2}},
                                                     {{1500,2,6,2},{1500,2,7,2},{1500,3,7,3}}
                                                     } ;

    vector<vector<vector<int>>> level_array_shield={ {{2000,0,6,1},{3000,0,7,1},{3000,1,7,1}},
                                                     {{2000,0,6,1},{2500,0,7,1},{2500,1,9,2}},
                                                     {{1500,0,8,2},{2500,0,9,2},{2000,1,10,2}},
                                                     {{1500,0,9,2},{1500,1,10,3},{1500,1,11,2}},
                                                     {{1200,1,10,3},{1200,1,10,2},{1000,2,11,3}}
                                                     } ;

   Boss* boss = nullptr;
   int time = 200;
   bool end = false;
   int score_record = 0;
   QMediaPlayer *main_background_music=nullptr;

};

#endif // GAMEENGINE_H
