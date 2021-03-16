#include "mytrain.h"
#include "ui_mytrain.h"
#include<QApplication>
#include<QDebug>

MyTrain::MyTrain(QWidget *parent,Train train_)
    : QMainWindow(parent)
    , ui(new Ui::MyTrain)
    , train(train_)
{
    ui->setupUi(this);

    //设置水平头
    ui->beginTreeWidget->setHeaderLabels(QStringList()<<QString::fromLocal8Bit("线路号")<<QString::fromLocal8Bit("站点名"));
    ui->endTreeWidget->setHeaderLabels(QStringList()<<QString::fromLocal8Bit("线路号")<<QString::fromLocal8Bit("站点名"));

    QVector<QTreeWidgetItem*> beginLines;
    QVector<QTreeWidgetItem*> endLines;
    for(int i=0;i<8;i++)
    {
        if(i == 4)
        {
            beginLines.push_back(new QTreeWidgetItem());
            endLines.push_back(new QTreeWidgetItem());
            continue;
        }
        QString lineName = QString::fromLocal8Bit("号线");
        lineName.push_front(i+'0'+1);
        QTreeWidgetItem * bLine = new QTreeWidgetItem(QStringList()<<lineName);
        beginLines.push_back(bLine);
        ui->beginTreeWidget->addTopLevelItem(bLine);

        QTreeWidgetItem * eLine = new QTreeWidgetItem(QStringList()<<lineName);
        endLines.push_back(eLine);
        ui->endTreeWidget->addTopLevelItem(eLine);
    }

    //添加子节点（站台）
    for(int i=0;i<train.stations.size();i++)
    {
        for(int num:train.stations[i].lineNums)
        {
            QString s = QString::fromLocal8Bit("号线");
            s.push_front(num+'0');
            QTreeWidgetItem * lable1 = new QTreeWidgetItem(QStringList()<<s<<train.stations[i].stationName);
            QTreeWidgetItem * lable2 = new QTreeWidgetItem(QStringList()<<s<<train.stations[i].stationName);

            beginLines[num-1]->addChild(lable1);
            endLines[num-1]->addChild(lable2);

        }
    }
    //设置起始站
    connect(ui->beginTreeWidget,&QTreeWidget::itemPressed,this,&MyTrain::getBegin);
    //设置终点站
    connect(ui->endTreeWidget,&QTreeWidget::itemPressed,this,&MyTrain::getEnd);
    //设置时间
    connect(ui->timePushButton,&QPushButton::clicked,this,&MyTrain::getTime);
    //设置确定键
    connect(ui->okPushButton,&QPushButton::clicked,this,&MyTrain::getSolution);
    //设置取消键
    connect(ui->canclePushButton,&QPushButton::clicked,this,&MyTrain::close);

}

MyTrain::~MyTrain()
{
    delete ui;
}

void MyTrain::getBegin()
{
    QTreeWidgetItem* curItem = ui->beginTreeWidget->currentItem();
    if(curItem->text(1).size()==0) return;
    train.setBegin(curItem->text(1));
    QString s = QString::fromLocal8Bit("起始站:")+curItem->text(1)+"\n";
    ui->textBrowser->insertPlainText(s);
}

void MyTrain::getEnd()
{
    QTreeWidgetItem* curItem = ui->endTreeWidget->currentItem();
    if(curItem->text(1).size()==0) return;
    train.setEnd(curItem->text(1));
    QString s = QString::fromLocal8Bit("终点站:")+curItem->text(1)+"\n";
    ui->textBrowser->insertPlainText(s);
}

void MyTrain::getTime()
{
    QTime t = ui->timeEdit->time();
    Time nowTime = Time(t.hour(),t.minute());
    train.setTime(nowTime);

    QString s = QString::fromLocal8Bit("出发时间:  ")+QString::number(nowTime.hour)+":";
    if(nowTime.minute<10) s += "0"+QString::number(nowTime.minute)+"\n";
    else s += QString::number(nowTime.minute)+"\n";

    ui->textBrowser->insertPlainText(s);
}

void MyTrain::getSolution()
{
    ui->textBrowser->clear();

    QVector<QVector<int>> solutions = train.simpleDirected(train.end,train.begin);

    if(solutions[0].size()==0)
    {
        if(solutions[1][0] == -1) ui->textBrowser->insertPlainText(QString::fromLocal8Bit("请设置当前时间\n"));
        else if(solutions[1][0] == -2) ui->textBrowser->insertPlainText(QString::fromLocal8Bit("当前时刻未在地铁运营时段内\n"));
        if(solutions[1][1] == -1) ui->textBrowser->insertPlainText(QString::fromLocal8Bit("请设置起始站\n"));
        if(solutions[1][2] == -1) ui->textBrowser->insertPlainText(QString::fromLocal8Bit("请设置终点站\n"));
        return;
    }
    else
    {
        QString tip = "";
        tip += QString::fromLocal8Bit("起始站:")+train.begin+"\n";
        tip += QString::fromLocal8Bit("终点站:")+train.end+"\n";
        tip += QString::fromLocal8Bit("出发时间:  ")+QString::number(train.nowTime.hour)+":";

        if(train.nowTime.minute<10) tip += "0"+QString::number(train.nowTime.minute)+"\n";
        else tip += QString::number(train.nowTime.minute)+"\n";

        ui->textBrowser->insertPlainText(tip);

        //筛选出最短的三条路
        sort(solutions.begin(),solutions.end(),[=](QVector<int> a,QVector<int> b){
            return train.getDistance(a) < train.getDistance(b);
        });

        double min = this->train.getDistance(solutions[0]);
        for(int i=0;i<3 && i<solutions.size();i++)
        {
            if(train.getDistance(solutions[i]) > 1.3*min) continue;

            QString s = "\n";
            double dist = train.getDistance(solutions[i]);
            s += QString::fromLocal8Bit("总线路长:")+QString::number(dist)+"km";
            s += QString::fromLocal8Bit("    票价:")+QString::number(train.getPay(dist))+QString::fromLocal8Bit("元(CNY)\n");
            s += this->train.getRoute(solutions[i],train.nowTime);

            s+="\n";
            ui->textBrowser->insertPlainText(s);

        }
    }
}
