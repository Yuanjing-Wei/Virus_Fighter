#ifndef VIRUSB_H
#define VIRUSB_H

#include"virus.h"

class VirusB:public Virus
{
public:
    VirusB(int requested_speed,int requested_potential,qreal angle);
    ~VirusB(){};
};

#endif // VIRUSB_H
