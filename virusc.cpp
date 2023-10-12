#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "virusc.h"
#include "virusa.h"
#include "virusb.h"

static const double PI = 3.14159265358979323846264338327950288419717;

VirusC::VirusC(int requested_speed,int requested_potential,qreal angle):Virus(Virus::VType::C,requested_speed,requested_potential,angle)
{
    //fix the virus size
    QSize size{WEITH,HEIGHT};
    QPixmap virusCImg=QPixmap(":/images/game_resource/images/virusorange.png").scaled(size,Qt::KeepAspectRatio);
    setPixmap(QPixmap(virusCImg));

    //adjust the image angle so it looks like heading to the player
    if (angle >= 0 && angle < PI) {
       // Rotate left
        setRotation(rotation() - angle * 180 /PI);
    } else if (angle <= 2.0*PI && angle> PI) {
       // Rotate right
        setRotation(rotation() + (angle - 2.0*PI )* (-180) /PI);
    }

    Virus::connect_n_start();

    //create and connect a timer to attack() the player every so often
    QTimer* infectTimer = new QTimer();
    connect(infectTimer,SIGNAL(timeout()),this,SLOT(infect()));
    infectTimer->start(250);
}

/* If a C-type virus collides with an A or B-type virus, we name that virus as v,
 * we generate a new C-type virus at the colliidng position
 * and let it move along the original track of v.
 * Then delete v so it looks like v is infected and become a C-type virus, which does more damage and moves faster.
*/
void VirusC::infect(){
    //virusC could only does infection after level 3
    if(allow_infect){
        //there is a 50% chance that the virus could infect
        srand(time(NULL));
        int prob=rand()%100;
        if(prob<=50)
            return;
        // get a list of all the items currently colliding with this bullet
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for (int i = 0, n = colliding_items.size(); i<n; ++i){
            auto &obj=*colliding_items[i];
            if (typeid(obj) == typeid(VirusA)||typeid(obj) == typeid(VirusB)){
                Virus* v=dynamic_cast<Virus*>(colliding_items[i]);
                VirusC*virus=new VirusC(5,3,v->get_angle());
                virus->setPos(colliding_items[i]->x(),colliding_items[i]->y());
                scene()->addItem(virus);
                scene()->removeItem(colliding_items[i]);
                delete colliding_items[i];
            }
        }
    }
}
