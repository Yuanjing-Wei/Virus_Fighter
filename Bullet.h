#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
//#include "Enemy.h"
//#include "Player.h"
//#include "gameengine.h"

//extern GameEngine * game;

class Bullet: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum class Type{WEAPON,VIRUS};
private:
    Type type;
    const int BULLET_BOUNDS[4]={-8,450,0,750};
    QTimer* timer=nullptr;
protected:
    void connect_n_start();
public:
    Bullet(){};
    Bullet(Type type,QGraphicsItem * parent=0);
    virtual ~Bullet();
private slots:
    virtual void move()=0;
    virtual bool check_collide()=0;   
    virtual void attack()=0;
public slots:
    void check_out();
};

#endif // BULLET_H
