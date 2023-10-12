#ifndef VIRUSC_H
#define VIRUSC_H

#include"virus.h"

class VirusC:public Virus
{
    Q_OBJECT
private:
    static bool allow_infect;//static data member applies to all C-type viruses

public:
    VirusC(int requested_speed,int requested_potential,qreal angle);
    ~VirusC(){};
    static void allowInfect(){
        allow_infect=true;
    };

private slots:
    void infect();//a C-type virus can infect a virus of another type, i.e. change that virus to C-type
};

#endif // VIRUSC_H
