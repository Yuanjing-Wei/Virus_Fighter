#ifndef LOSE_H
#define LOSE_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class Lose;
}

class Lose : public QDialog
{
    Q_OBJECT

public:
    explicit Lose(int score,int num_enemies,int level,QWidget *parent = nullptr);
    ~Lose();

private slots:
    void on_OK_clicked();

private:
    Ui::Lose *ui=nullptr;
    int score;
    int num_enemies;
    int level;
    void display_score();
    void display_enemy_num();
    void display_level();
};

#endif // LOSE_H
