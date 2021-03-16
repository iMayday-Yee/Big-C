#ifndef NODE_H
#define NODE_H
#include<QString>
#include<QVector>

class Node
{
public:
    //ÿ��վ����е�����
    QString stationName;
    //ÿ��վ�����ڵĵ�����·��
    QVector<int> lineNums;
    //ÿ��վ��������·�����ڵ�λ��
    QVector<int> stationNums;
    //ÿ��վ����еı��
    int station_tag;
    Node(QString stationName,int num,int stationNum,int n);
    Node(){};
    void addFeature(int lineNum,int stationNum);
};

#endif // NODE_H
