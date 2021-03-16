#ifndef NODE_H
#define NODE_H
#include<QString>
#include<QVector>

class Node
{
public:
    //每个站点独有的名字
    QString stationName;
    //每个站点所在的地铁线路号
    QVector<int> lineNums;
    //每个站点在其线路号所在的位置
    QVector<int> stationNums;
    //每个站点独有的标号
    int station_tag;
    Node(QString stationName,int num,int stationNum,int n);
    Node(){};
    void addFeature(int lineNum,int stationNum);
};

#endif // NODE_H
