#ifndef ANTI_H
#define ANTI_H
#include "Enemy.h"
#include "virusa.h"
class Anti : public Enemy
{
public:
    Anti(int period = 1000, int requested_potential = 3 , int requested_speed = 10, int requested_shooting_number = 1);
    ~Anti();
private slots:
    void shoot() override;
    void update_result() override;

private:
    QPixmap anti_photo[12]; //used to change enemy's movement photo
    VirusA** virus=nullptr;
};

#endif // ANTI_H
