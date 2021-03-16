#ifndef TRAIN_H
#define TRAIN_H
#include"mytime.h"
#include"edge.h"
#include"node.h"
#include<iostream>
#include<QTextCodec>
#include<QFile>
#include<QMap>
#include<QSet>
#include<sstream>
#include<string>
using namespace std;
class Train
{
private:
    int stationSize,edgeSize;
    double distBeginToEnd;
    //��¼station_name��station_tag��ӳ��
    QMap<QString,int> nameToTag;
    //�������
    QVector<QVector<double>> distanceMatrix;
    //�ڽӱ�
    QVector<QVector<int>> adjList;
    //��ȡ��begin_tag��end_tag֮��ļ�·��
    void simpleDirectedPathes(int begin_tag,int end_Tag,QVector<int> path,QVector<bool> visited,QVector<int> table,int transfer_times,QVector<QVector<int>> &pathes);
    //��ȡ��ǰʱ�䣬��lineNum��Ӧ���ۺ�����ʱ��
    double getThisConpreTime(int lineNum,Time t);
    static bool cmp(QVector<int> a,QVector<int> b);
    int getSameLineNum(QVector<int> a,QVector<int> b);

public:
    Train(QString station_filename,QString line_filename,Time nowTime);
    Train();
    ~Train();

    QVector<Node> stations;
    QVector<Edge> edges;
    QString begin;
    QString end;
    Time nowTime;

    void setTime(Time time);
    void setBegin(QString begin);
    void setEnd(QString end);
    //����ۺ�����ʱ�䷽��
    void shortestComprehensiveTime(QString begin,QString end);
    //���·�̷���
    void shortestDistance(QString begin,QString end);
    //���ڽ�QStringת����intȻ�����private�е�simpleDirectedPathes()����
    QVector<QVector<int>> simpleDirected(QString begin,QString end);
    //��ȡ·��
    double getDistance(QVector<int> route);
    //��ȡƱ��
    int getPay(double dist);
    //��·��ת��ΪQString���
    QString getRoute(QVector<int> route,Time nowTime);
    bool ifTransfer(QVector<int> table,int now_tag);
    QVector<int> changeTable(QVector<int> table,int now_tag);
};
#endif // TRAIN_H
