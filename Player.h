#ifndef PLAYER_H
#define PLAYER_H
#include "weapon.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>
#include <vector>
using namespace std;

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    ~Player();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    QPointF get_attack_dest(){
        return QPointF(x(),y());
    }
    void level_up(int level);

private:
    //QMediaPlayer * bulletsound;
    int key[5]={0,0,0,0,0}; //Up(W),Down(S),Left(V),Right(D),Space
    void create_bullet_and_sound(int x, int y);

    int xcount=0; //used to change player movement photo
    int ycount=0; //used to change player movement photo
    int ix=0; //used to change player movement photo
    int iy=0; //used to change player movement photo
    int result=0; //used to change player movement photo
    QPixmap player_photo[12]; //used to change player movement photo
    void move();
    Weapon** weapon {nullptr};
    int requested_shooting_number = 1;
    int requested_speed = 10;
    int attack_potential = 5;
    QTimer* shooting_inertia=nullptr;

};

#endif // PLAYER_H
