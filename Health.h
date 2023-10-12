#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
public:
    Health(int health, QGraphicsItem * parent=0);
    void decrease(int attack);
    void increase(int add);
    int getHealth();
private:
    int health;
};

#endif // HEALTH_H
