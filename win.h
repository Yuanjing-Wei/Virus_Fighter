#ifndef WIN_H
#define WIN_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class Win;
}

class Win : public QDialog
{
    Q_OBJECT

public:
    explicit Win(int score,int num_enemies,QWidget *parent = nullptr);
    void display_score();
    void display_enemy_num();
    void random(); //Function not used
    ~Win();
    int score;
    int num_enemies;

private slots:
    void on_OK_clicked();
private:
    Ui::Win *ui=nullptr;

};

#endif // WIN_H
