#include "gamerules.h"
#include "ui_gamerules.h"

GameRules::GameRules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameRules)
{
    ui->setupUi(this);

        setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
        setFixedSize(this->width(), this->height()+500);

        QPixmap bkgnd(":/background/game_resource/background/background2.jpg");

            bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
            QPalette palette;
            //palette.setColor(QPalette::Background, QColor (255, 255 , 255, 255));
            palette.setBrush(QPalette::Background, bkgnd);
            this->setPalette(palette);
            ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

GameRules::~GameRules()
{
    delete ui;
}
