#ifndef BOSS_H
#define BOSS_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include "Health.h"
#include "bossvirus.h"
class Boss:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    static bool boss_is_killed;
    //static bool enemy_inhibitor;
 public:
    static bool bossIsKilled(){return boss_is_killed;}
    Boss();
    ~Boss();
    void get_attack(int attack);
private:
    int time = 0;
    int count_cycle;
    void Appear(); //Appear
    void Move1(); //Different patterns of moving
    void Move2(); //Different patterns of moving
    QTimer* shoot_timer=nullptr;
    QTimer* boss_timer=nullptr;

    double x,y,prev_x,prev_y;

    QPixmap boss_image;
    Health* health=nullptr;
    int move_pattern =0;

    //BossVirus* shot;

    int angle,raise;
    int raise2;
    int width;
    int height;
    double movex,movey;
    double virus_angle = 0;
private slots:
    void Move();
    void Shoot_Barrage();
    void Shoot_Circle();
};

#endif // BOSS_H
