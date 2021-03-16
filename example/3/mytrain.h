#ifndef MYTRAIN_H
#define MYTRAIN_H

#include <QMainWindow>
#include"train.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyTrain;}
QT_END_NAMESPACE

class MyTrain : public QMainWindow
{
    Q_OBJECT

public:
    MyTrain(QWidget *parent = nullptr,Train train = Train());
    ~MyTrain();

    void getBegin();
    void getEnd();
    void getTime();
    void getSolution();



private:
    Ui::MyTrain *ui;
    Train train;
};
#endif // MYTRAIN_H
