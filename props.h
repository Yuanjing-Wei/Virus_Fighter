#ifndef PROPS_H
#define PROPS_H
#include <QGraphicsPixmapItem>
#include <QObject>

class props:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    props();
    virtual ~props();
private:
    int x;
    int y;
    int time=0;
    bool add_finished = false;
    QTimer* timer=nullptr;
    virtual void work()=0;
private slots:
    void time_update();
    void collide_check();
    void finish();
};

#endif // PROPS_H
