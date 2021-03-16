#include "node.h"

Node::Node(QString stationName,int num,int stationNum,int n):stationName(stationName),station_tag(n)
{
    lineNums.push_back(num);
    stationNums.push_back(stationNum);
}

void Node::addFeature(int lineNum,int stationNum)
{
    lineNums.push_back(lineNum);
    stationNums.push_back(stationNum);
}
