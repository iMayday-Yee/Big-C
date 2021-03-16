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

    //����ˮƽͷ
    ui->beginTreeWidget->setHeaderLabels(QStringList()<<QString::fromLocal8Bit("��·��")<<QString::fromLocal8Bit("վ����"));
    ui->endTreeWidget->setHeaderLabels(QStringList()<<QString::fromLocal8Bit("��·��")<<QString::fromLocal8Bit("վ����"));

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
        QString lineName = QString::fromLocal8Bit("����");
        lineName.push_front(i+'0'+1);
        QTreeWidgetItem * bLine = new QTreeWidgetItem(QStringList()<<lineName);
        beginLines.push_back(bLine);
        ui->beginTreeWidget->addTopLevelItem(bLine);

        QTreeWidgetItem * eLine = new QTreeWidgetItem(QStringList()<<lineName);
        endLines.push_back(eLine);
        ui->endTreeWidget->addTopLevelItem(eLine);
    }

    //����ӽڵ㣨վ̨��
    for(int i=0;i<train.stations.size();i++)
    {
        for(int num:train.stations[i].lineNums)
        {
            QString s = QString::fromLocal8Bit("����");
            s.push_front(num+'0');
            QTreeWidgetItem * lable1 = new QTreeWidgetItem(QStringList()<<s<<train.stations[i].stationName);
            QTreeWidgetItem * lable2 = new QTreeWidgetItem(QStringList()<<s<<train.stations[i].stationName);

            beginLines[num-1]->addChild(lable1);
            endLines[num-1]->addChild(lable2);

        }
    }
    //������ʼվ
    connect(ui->beginTreeWidget,&QTreeWidget::itemPressed,this,&MyTrain::getBegin);
    //�����յ�վ
    connect(ui->endTreeWidget,&QTreeWidget::itemPressed,this,&MyTrain::getEnd);
    //����ʱ��
    connect(ui->timePushButton,&QPushButton::clicked,this,&MyTrain::getTime);
    //����ȷ����
    connect(ui->okPushButton,&QPushButton::clicked,this,&MyTrain::getSolution);
    //����ȡ����
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
    QString s = QString::fromLocal8Bit("��ʼվ:")+curItem->text(1)+"\n";
    ui->textBrowser->insertPlainText(s);
}

void MyTrain::getEnd()
{
    QTreeWidgetItem* curItem = ui->endTreeWidget->currentItem();
    if(curItem->text(1).size()==0) return;
    train.setEnd(curItem->text(1));
    QString s = QString::fromLocal8Bit("�յ�վ:")+curItem->text(1)+"\n";
    ui->textBrowser->insertPlainText(s);
}

void MyTrain::getTime()
{
    QTime t = ui->timeEdit->time();
    Time nowTime = Time(t.hour(),t.minute());
    train.setTime(nowTime);

    QString s = QString::fromLocal8Bit("����ʱ��:  ")+QString::number(nowTime.hour)+":";
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
        if(solutions[1][0] == -1) ui->textBrowser->insertPlainText(QString::fromLocal8Bit("�����õ�ǰʱ��\n"));
        else if(solutions[1][0] == -2) ui->textBrowser->insertPlainText(QString::fromLocal8Bit("��ǰʱ��δ�ڵ�����Ӫʱ����\n"));
        if(solutions[1][1] == -1) ui->textBrowser->insertPlainText(QString::fromLocal8Bit("��������ʼվ\n"));
        if(solutions[1][2] == -1) ui->textBrowser->insertPlainText(QString::fromLocal8Bit("�������յ�վ\n"));
        return;
    }
    else
    {
        QString tip = "";
        tip += QString::fromLocal8Bit("��ʼվ:")+train.begin+"\n";
        tip += QString::fromLocal8Bit("�յ�վ:")+train.end+"\n";
        tip += QString::fromLocal8Bit("����ʱ��:  ")+QString::number(train.nowTime.hour)+":";

        if(train.nowTime.minute<10) tip += "0"+QString::number(train.nowTime.minute)+"\n";
        else tip += QString::number(train.nowTime.minute)+"\n";

        ui->textBrowser->insertPlainText(tip);

        //ɸѡ����̵�����·
        sort(solutions.begin(),solutions.end(),[=](QVector<int> a,QVector<int> b){
            return train.getDistance(a) < train.getDistance(b);
        });

        double min = this->train.getDistance(solutions[0]);
        for(int i=0;i<3 && i<solutions.size();i++)
        {
            if(train.getDistance(solutions[i]) > 1.3*min) continue;

            QString s = "\n";
            double dist = train.getDistance(solutions[i]);
            s += QString::fromLocal8Bit("����·��:")+QString::number(dist)+"km";
            s += QString::fromLocal8Bit("    Ʊ��:")+QString::number(train.getPay(dist))+QString::fromLocal8Bit("Ԫ(CNY)\n");
            s += this->train.getRoute(solutions[i],train.nowTime);

            s+="\n";
            ui->textBrowser->insertPlainText(s);

        }
    }
}
