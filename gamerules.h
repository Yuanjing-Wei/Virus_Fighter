#ifndef GAMERULES_H
#define GAMERULES_H

#include <QDialog>

namespace Ui {
class GameRules;
}

class GameRules : public QDialog
{
    Q_OBJECT

public:
    explicit GameRules(QWidget *parent = nullptr);
    ~GameRules();

private:
    Ui::GameRules *ui=nullptr;
};

#endif // GAMERULES_H
