#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
    int begin_tag;
    int end_tag;
    double distance;
    int lineNum;
    Edge(int begin_tag,int end_tag,double distance,int lineNum);
    Edge(){};
};

#endif // EDGE_HQ
