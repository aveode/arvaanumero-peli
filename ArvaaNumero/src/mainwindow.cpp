#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <ctime>
#include <string>

using namespace std;


int generate_Number()
{
    unsigned int t = time(0);

    mt19937 generator{ t };
    uniform_int_distribution<int> distribution(0, 100);

    int number = distribution(generator);

    qDebug()<<to_string(number);

    return number;
}

// Game variables
int roundsLeft = 10;
int number = generate_Number();
QString numberText =QVariant(number).toString();
// -------------


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->labelStatus->setText("Aloita peli");
    ui->labelCounter->setText(QVariant(roundsLeft).toString());
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(roundsLeft > 0)
    {
        int guess = ui->textGuess->toPlainText().toInt();

        if(guess == number)
        {
            ui->labelStatus->setText("Numero oikein | Voitit pelin");
            ui->pushButton->hide();
        }
        else
        {
            if(guess > number){ui->labelStatus->setText("Numero on vähemmän");}
            else{ui->labelStatus->setText("Numero on enemmän");}

            roundsLeft--;
            ui->labelCounter->setText("Yrityksiä jäljellä: " + QVariant(roundsLeft).toString());
        }
    }
    else
    {
        ui->labelStatus->setText("Sinulla loppui arvaukset | Game over");
        ui->pushButton->hide();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"RESTART PRESSED";
    roundsLeft = 10;
    number = generate_Number();
    numberText =QVariant(number).toString();

    ui->labelStatus->setText("Aloita peli");
    ui->labelCounter->setText(QVariant(roundsLeft).toString());

    ui->pushButton->show();
}


