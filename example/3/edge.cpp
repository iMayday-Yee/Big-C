#include "edge.h"

Edge::Edge(int begin_tag,int end_tag,double distance,int lineNum)
{
    this->begin_tag = begin_tag;
    this->end_tag = end_tag;
    this->distance = distance;
    this->lineNum = lineNum;
}
