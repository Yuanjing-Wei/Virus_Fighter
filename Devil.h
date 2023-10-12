#ifndef DEVIL_H
#define DEVIL_H
#include "Enemy.h"
#include "virusb.h"
class Devil : public Enemy
{
public:
    Devil(int period = 1000, int requested_potential = 3 , int requested_speed = 10, int requested_shooting_number = 1);
    ~Devil();
private slots:
    void shoot() override;
    void update_result() override;

private:
    QPixmap devil_photo[12]; //used to change enemy's movement photo
    VirusB** virus=nullptr;
};

#endif // DEVIL_H
