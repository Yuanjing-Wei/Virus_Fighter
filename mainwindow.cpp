#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamerules.h"
#include "gameengine.h"
#include "windows.h"
#include <QTimer>
#include <QString>
extern GameEngine * game;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    QPixmap bkgnd(":/background/game_resource/background/background1.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_2_clicked()
{
    GameRules* game_rules = new GameRules;
    game_rules->exec();

}

void MainWindow::on_pushButton_4_clicked()
{
    Ranking* ranking = new Ranking;
    ranking->exec();

}

void MainWindow::on_pushButton_3_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_clicked()
{
    QString name = QInputDialog::getText(this, tr("Player Information"),
                                        tr("Please enter your name:"));


    game = new GameEngine(name);
    game->show();

    close();
}
