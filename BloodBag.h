#ifndef BLOODBAG_H
#define BLOODBAG_H
#include "props.h"

class BloodBag :public props
{
public:
    BloodBag(int add);

private:
    int add;
    void add_health();
    virtual void work(){add_health();}; //Implementation of the pure virtual function in props
};

#endif // BLOODBAG_H
