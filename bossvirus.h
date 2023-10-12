#ifndef BOSSVIRUS_H
#define BOSSVIRUS_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include "virus.h"

class BossVirus :public Virus//, public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BossVirus(int startx,int starty,double rad,int requested_speed,int requested_potential,qreal angle);
    ~BossVirus(){};
private:
    int startx;
    int starty;
    double rad;
    //int speed;
    QTimer* timer=nullptr;
private slots:
    virtual void move() override;
    /*void check_collide();
    void check_out();   */
};

#endif // BOSSVIRUS_H
