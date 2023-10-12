#ifndef RANKING_H
#define RANKING_H

#include <QDialog>
#include <string>
#include <QString>
#include "Hashtable.h"
#include <QList>
using std::string;
namespace Ui {
class Ranking;
}

class Ranking : public QDialog
{
    Q_OBJECT

public:
    explicit Ranking(QString = NULL,QWidget *parent = nullptr);
    ~Ranking();
private:
    void Read_the_file();
    void Set_the_table();

private slots:
    void on_Find_clicked();

    void on_name_requested_textChanged(const QString &arg1);

private:
    Ui::Ranking *ui=nullptr;
    int player_num;
    QList<string> names;
    QList<int> scores;
    QString filename;
    QString name_tentative;
    Hashtable* hash=nullptr;
};

#endif // RANKING_H
