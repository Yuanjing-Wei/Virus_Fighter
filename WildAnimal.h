#ifndef WILDANIMAL_H
#define WILDANIMAL_H
#include "Enemy.h"
#include "virusc.h"

class WildAnimal : public Enemy
{
public:
    WildAnimal(int period = 1000, int requested_potential = 3 , int requested_speed = 10, int requested_shooting_number = 1);
    ~WildAnimal();
private slots:
    void shoot() override;
    void update_result() override;

private:
    QPixmap wildanimal_photo[12]; //used to change enemy's movement photo
    VirusC** virus=nullptr;
};

#endif // WILDANIMAL_H
