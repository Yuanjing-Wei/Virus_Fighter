#ifndef VIRUSA_H
#define VIRUSA_H

#include"virus.h"

class VirusA:public Virus
{
public:
    VirusA(int requested_speed,int requested_potential,qreal angle);
    ~VirusA(){};
};

#endif // VIRUSA_H
