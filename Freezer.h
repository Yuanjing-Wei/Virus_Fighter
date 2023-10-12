#ifndef FREEZER_H
#define FREEZER_H

#include "props.h"

class Freezer :public props
{
public:
    Freezer();
    ~Freezer();
private:
    virtual void work(){freeze();};
    void freeze();
    QTimer* freeze_timer=nullptr;
};


#endif // FREEZER_H
