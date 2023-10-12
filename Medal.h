#ifndef MEDAL_H
#define MEDAL_H

#include "props.h"

class Medal :public props
{
public:
    Medal(int add);

private:
    int add;
    void add_score();
    virtual void work(){add_score();};
};
#endif // MEDAL_H
