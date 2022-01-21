#include "calculator.h"
#include "ui_calculator.h"

double calVal = 0.0;
bool divTrigger = false;
bool multiTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

//calculator class and calculator constructor using scope resolution operator
Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent) //qmainwindow constructor
    , ui(new Ui::Calculator) //creating ui class and assigning to ui member
{
    ui->setupUi(this); //setup UI
    ui->Display->setText(QString::number(calVal)); //double converted to string and text is set in the UIs Display
    QPushButton *numberButtons[10]; //array declaration

    //assigning signal and slots
        for(int i=0; i<10; i++){
            QString btnName = "Button" + QString::number(i);
            numberButtons[i] = Calculator::findChild<QPushButton *>(btnName); //assigning child widget with the name "Button_" in Calclulator UI to the array element
            connect(numberButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
        }

        connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
        connect(ui->Substract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
        connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
        connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));

        connect(ui->Total, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
        connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
        connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearAll()));

}

Calculator::~Calculator()
{
    delete ui;
}

//To display pressed number button value
void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender(); //sender returns a pointer to the button when pressed
    QString buttonVal = button->text(); //assign button pointer's text is assigned to to newly created buttonVal(declaration)
    QString displayVal = ui->Display->text(); //assign display's text buttonVal to newly created displayVal(declaration)

    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0){
        ui->Display->setText(buttonVal);
    }else{ //if the display has a previous value entered already
        double dblnewVal = (displayVal + buttonVal).toDouble();
        ui->Display->setText(QString::number(dblnewVal, 'g', 16));


    }
   }

//To trigger the mathematical operation
    void Calculator::MathButtonPressed(){
        divTrigger = false;
        multiTrigger = false;
        addTrigger = false;
        subTrigger = false;

        QString displayVal = ui->Display->text();
        calVal = displayVal.toDouble();
        QPushButton *button = (QPushButton *)sender();
        QString buttonVal = button->text();
        if(QString::compare(buttonVal, "/", Qt::CaseInsensitive) == 0){
            divTrigger = true;
        }
        else if(QString::compare(buttonVal, "*", Qt::CaseInsensitive) == 0){
            multiTrigger = true;
        }
        else if(QString::compare(buttonVal, "+", Qt::CaseInsensitive) == 0){
            addTrigger = true;
        }
        else
            subTrigger = true;

        ui->Display->setText("");
    }

    //To do the calculation and give solution
    void Calculator::EqualButtonPressed(){
        double solution = 0.0;
        QString displayVal = ui->Display->text();
        double dblDisplayVal = displayVal.toDouble();
        if(addTrigger || subTrigger || multiTrigger || divTrigger){
            if(addTrigger){
                solution = calVal + dblDisplayVal;
            }
            else if(subTrigger){
                solution = calVal - dblDisplayVal;
            }
            else if(multiTrigger){
                solution = calVal * dblDisplayVal;
            }
            else if(divTrigger){
                solution = calVal / dblDisplayVal;
            }

            ui->Display->setText(QString::number(solution));
        }

    }

    //Changing +/- number sign
    void Calculator::ChangeNumberSign(){
        QString displayVal = ui->Display->text();
        QRegExp reg("[-]?[0-9.]*");
        if(reg.exactMatch(displayVal)){
            double dblDisplayVal = displayVal.toDouble();
            double dblDisplayValSign = -1 * dblDisplayVal;
            ui->Display->setText(QString::number(dblDisplayValSign));
        }


    }

    //clear all
    void Calculator::ClearAll(){
        ui->Display->setText("0");
        calVal = 0;


    }


