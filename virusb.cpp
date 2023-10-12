#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "virusb.h"

static const double PI = 3.14159265358979323846264338327950288419717;

VirusB::VirusB(int requested_speed,int requested_potential,qreal angle):Virus(Virus::VType::B,requested_speed,requested_potential,angle)
{
    //fix the virus size
    QSize size{WEITH,HEIGHT};
    QPixmap virusBImg=QPixmap(":/images/game_resource/images/virusgreen.png").scaled(size,Qt::KeepAspectRatio);
    setPixmap(QPixmap(virusBImg));

    //adjust the image angle so it looks like heading to the player
    if (angle >= 0 && angle < PI) {
       // Rotate left
        setRotation(rotation() - angle * 180 /PI);
    } else if (angle <= 2.0*PI && angle> PI) {
       // Rotate right
        setRotation(rotation() + (angle - 2.0*PI )* (-180) /PI);
    }

    Virus::connect_n_start();
}
