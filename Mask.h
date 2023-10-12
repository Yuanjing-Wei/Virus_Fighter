#ifndef MASK_H
#define MASK_H

#include "props.h"

class Mask :public props
{
public:
    Mask();
    ~Mask();
private:
    virtual void work(){shield();};
    void shield();
    QTimer* shield_timer=nullptr;
};

#endif // MASK_H
