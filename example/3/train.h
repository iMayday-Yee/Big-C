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
    //记录station_name和station_tag的映射
    QMap<QString,int> nameToTag;
    //距离矩阵
    QVector<QVector<double>> distanceMatrix;
    //邻接表
    QVector<QVector<int>> adjList;
    //获取从begin_tag到end_tag之间的简单路径
    void simpleDirectedPathes(int begin_tag,int end_Tag,QVector<int> path,QVector<bool> visited,QVector<int> table,int transfer_times,QVector<QVector<int>> &pathes);
    //获取当前时间，该lineNum对应的综合评估时间
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
    //最低综合评估时间方案
    void shortestComprehensiveTime(QString begin,QString end);
    //最短路程方案
    void shortestDistance(QString begin,QString end);
    //用于将QString转化成int然后调用private中的simpleDirectedPathes()函数
    QVector<QVector<int>> simpleDirected(QString begin,QString end);
    //获取路程
    double getDistance(QVector<int> route);
    //获取票价
    int getPay(double dist);
    //将路线转化为QString输出
    QString getRoute(QVector<int> route,Time nowTime);
    bool ifTransfer(QVector<int> table,int now_tag);
    QVector<int> changeTable(QVector<int> table,int now_tag);
};
#endif // TRAIN_H
