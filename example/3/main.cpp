#include"mytrain.h"
#include"train.h"
#include<QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QString station_filename = ":/qFile/station_info.txt";
    QString line_filename = ":/qFile/tmp.txt";
    Train WuHanTrain(station_filename,line_filename,Time(0,0));
    QApplication a(argc,argv);
    MyTrain w(nullptr,WuHanTrain);
    w.show();
    return a.exec();
}
