#include "Ranking.h"
#include "ui_Ranking.h"
#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout;
using std::endl;
#include <cmath>
using std::abs;
#include <string>
using std::string;
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
Ranking::Ranking(QString filename, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ranking),filename(filename)
{
    ui->setupUi(this);
    this->setWindowTitle("Ranking");
    this->show();

    Read_the_file();
    Set_the_table();
    setAttribute(Qt::WA_DeleteOnClose);


}

Ranking::~Ranking()
{
    delete ui;
    // Remove all the item in the hash table
    for(int i =0;i<player_num;i++)
        hash->RemoveItem(names[i]);
    delete hash;
    cout<<"All over";
}


void Ranking::Read_the_file()
{
    while(filename == NULL)
    {
     filename = QFileDialog::getOpenFileName(this, tr("Open Map File"), ".", tr("Text Files (*.txt)"));
    }
    ifstream players_and_units_file(filename.toStdString());

    int index = 0;
    while(!players_and_units_file.eof())
    {
        string s;
        int i;
        players_and_units_file >> s >> i;
        //Append the QList, this function is quite useful because it's hard to know the number
        //of names beforehand
        names.append(s);
        scores.append(i);
        index+=1;
    }
    player_num = index  ;
}

void Ranking::Set_the_table()
{
    ui->ranking->setColumnCount(2);
    ui->ranking->setRowCount(player_num);
    //Set headers of the table
    QStringList headers;
    headers << QStringLiteral("Name") << QStringLiteral("Score") ;
    ui->ranking->setHorizontalHeaderLabels(headers);

    //Rearrange the order of players in score-decreasing order
    for (int i = 0; i < player_num; i++) {
        for (int j = i+1; j < player_num; j++) {
            if (scores[i] < scores[j]) {

                int temp;                
                //Exchange the score
                temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;

                string temp2;
                //Exchange the name as well
                temp2 = names[i];
                names[i] = names[j];
                names[j] = temp2;
            }
        }
     }
    hash = new Hashtable;

    //Add names and corresponding index to the hashtable
    for(int i = 0; i < player_num; ++i)
    hash->add(names[i], i);

    //Insert datas into the QTableWidget
    for (int ridx = 0 ; ridx < player_num ; ridx++ )
    {

          QTableWidgetItem* item1 = new QTableWidgetItem();
          item1->setText(QString::fromStdString(names[ridx]));
          ui->ranking->setItem(ridx,0,item1);

          QTableWidgetItem* item2 = new QTableWidgetItem();
          item2->setText(QString::number(scores[ridx]));
          ui->ranking->setItem(ridx,1,item2);


    }
}

void Ranking::on_Find_clicked()
{
    if(hash->FindIndex(name_tentative.toStdString())==-1)
    {
        QMessageBox::StandardButton reply = QMessageBox::warning(this,"Warning","No results found",
                                                            QMessageBox::Ok);
    }
    else
    {
        //Highlight the row containing the wanted name
        ui->ranking->selectRow(hash->FindIndex(name_tentative.toStdString()));
    }

}

void Ranking::on_name_requested_textChanged(const QString &arg1)
{
    //Record the temporary input, on_Find_clicked() will read the input when "Find" Button is clicked
    name_tentative = arg1;
}
