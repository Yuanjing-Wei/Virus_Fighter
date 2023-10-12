#ifndef LEVEL_H
#define LEVEL_H
#include <QTimer>

class Level
{
public:
    Level();
    ~Level();
    void increase();
    int getLevel();
private:
    QTimer* timer;
    int level;
};

#endif // LEVEL_H

