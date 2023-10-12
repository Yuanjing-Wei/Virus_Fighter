#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>
#include "Health.h"

class Enemy: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(int period , int requested_potential , int requested_speed, int requested_shooting_number,QGraphicsItem * parent=nullptr);
    virtual ~Enemy();
private slots:
    void move();
    virtual void shoot() = 0;
    void handle_move();
    void move_right();
    void move_left();

public slots:
    void get_attack(int attack);
protected:
    Health* health;
    const int SIZEW=100;
    const int SIZEH=100;
    int xcount=0; //used to change enemy's movement photo
    int ycount=0; //used to change enemy's movement photo
    int ix=0; //used to change enemy's movement photo
    int iy=0; //used to change enemy's movement photo
    int result=0; //used to change enemy's movement photo
    int get_prop; //Random number generated to see if a prop can be gotten
    QTimer* timer=nullptr;
    int period = 1000; //shooting period
    int requested_potential = 3; //viruses' attacking potential, similar to "attack" in pa3
    int requested_speed = 10; //viruses' moving speed
    int requested_shooting_number = 1;//number of viruses shot each time
    virtual void update_result();// make sure that the enemy looks like facing its moving direction
};

#endif // ENEMY_H
