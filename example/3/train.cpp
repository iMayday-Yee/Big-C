#include "train.h"

Train::Train(QString station_filename,QString line_filename,Time nowTime):nowTime(nowTime)
{
    //打开文件
    QFile station_file(station_filename);
    QFile line_file(line_filename);

    //初始化stations
    if(station_file.open(QIODevice::ReadOnly))
    {
        //记录当前读取在第几行
        int num=0;
        QString s;
        //记录当前站点的标号
        int n=0;
        int line_num;
        while(!station_file.atEnd())
        {

            QTextCodec *codec = QTextCodec::codecForName("GBK");
            QString line = codec->toUnicode(station_file.readLine());

            num++;
            //奇数行为线路总信息
            if(num%2 == 1) line_num = line[3].unicode()-'0';
            else
            {
                stringstream buf;
                buf<<line.toStdString();
                string tmp;
                int station_num;
                while(buf>>station_num>>tmp)
                {
                    //当前站点未存在在map中
                    QString station_name = QString::fromStdString(tmp);
                    if(nameToTag.find(station_name) == nameToTag.end())
                    {
                        //将n作为该站点的标号
                        nameToTag.insert(station_name,n);
                        //初始化该站点
                        Node temp_station = Node(station_name,line_num,station_num,n);
                        stations.push_back(temp_station);
                        n++;
                    }
                    //已经存在在map中，则要为其添加新的lineNum和stationNum
                    else
                    {
                        //获取该站点的标号
                        int temp = nameToTag[station_name];
                        stations[temp].addFeature(line_num,station_num);
                    }
                }
            }

        }
        station_file.close();
    }
    //初始化edges
    if(line_file.open(QIODevice::ReadOnly))
    {
        while(!line_file.atEnd())
        {
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            QString line = codec->toUnicode(line_file.readLine());

            stringstream buf;
            buf<<line.toStdString();
            string begin_tmp,end_tmp;
            int begin_station_num,end_station_num,line_num;
            double distance;
            buf>>line_num>>begin_station_num>>end_station_num>>begin_tmp>>end_tmp>>distance;
            QString begin_name = QString::fromStdString(begin_tmp);
            QString end_name = QString::fromStdString(end_tmp);
            int begin_tag = nameToTag[begin_name];
            int end_tag = nameToTag[end_name];
            Edge edge(begin_tag,end_tag,distance,line_num);
            edges.push_back(edge);
        }
    }

    edgeSize = edges.size();
    stationSize = stations.size();


    //初始化邻接矩阵，线路矩阵
    distanceMatrix = QVector<QVector<double>>(stationSize,QVector<double>(stationSize,INT_MAX));
    for(int i=0;i<stationSize;i++)
    {
        int begin_tag = edges[i].begin_tag;
        int end_tag = edges[i].end_tag;
        distanceMatrix[begin_tag][end_tag] = edges[i].distance;
        distanceMatrix[end_tag][begin_tag] = edges[i].distance;
        distanceMatrix[i][i] = 0;
    }
    for(int i=stationSize;i<edgeSize;i++)
    {
        int begin_tag = edges[i].begin_tag;
        int end_tag = edges[i].end_tag;
        distanceMatrix[begin_tag][end_tag] = edges[i].distance;
        distanceMatrix[end_tag][begin_tag] = edges[i].distance;
    }

    //初始化邻接表
    adjList = QVector<QVector<int>>(stationSize,QVector<int>());
    for(int i=0;i<edgeSize;i++)
    {
        int begin_tag = edges[i].begin_tag;
        int end_tag = edges[i].end_tag;
        adjList[begin_tag].push_back(end_tag);
        adjList[end_tag].push_back(begin_tag);
    }
}

Train::~Train(){}

bool Train::cmp(QVector<int> a,QVector<int> b)
{
    return a.size()<b.size();
}

QVector<QVector<int>> Train::simpleDirected(QString begin, QString end)
{
    QVector<QVector<int>> errorList{{},{0,0,0}};
    if(nowTime == Time(0,0))
    {
        errorList[1][0] = -1;
    }
    else if(nowTime >= Time(23,0) || nowTime < Time(6,0))
    {
        errorList[1][0] = -1;
    }
    if(begin == "")
    {
        errorList[1][1] = -1;
    }
    if(end == "")
    {
        errorList[1][2] = -1;
    }
    if(errorList[1][0]!=0 || errorList[1][1]!=0 || errorList[1][2]!=0) return errorList;



    QVector<QVector<int>> pathes;
    int begin_tag = nameToTag[begin];
    int end_tag = nameToTag[end];
    QVector<bool> visited(stationSize,false);
    QVector<int> path{end_tag};
    QVector<int> table(8,0);
    for(int i:stations[end_tag].lineNums)
    {
        table[i-1]++;
    }
    Train::simpleDirectedPathes(begin_tag,end_tag,path,visited,table,0,pathes);

    sort(pathes.begin(),pathes.end(),cmp);

    return pathes;
}

//求出
void Train::simpleDirectedPathes(int begin_tag,int end_tag,QVector<int> path,QVector<bool> visited,QVector<int> table,int transfer_times,QVector<QVector<int>> &pathes)
{
    if(transfer_times > 2) return;

    visited[end_tag] = true;
    for(int i:adjList[end_tag])
    {
        if(i == begin_tag)
        {
            if(ifTransfer(table,i)) transfer_times++;
            path.push_back(i);
            pathes.push_back(path);
            return;

        }
        else if(!visited[i])
        {
            //如果在此处换乘
            QVector<int> tmp = table;
            if(ifTransfer(table,i))
            {
                table = changeTable(table,i);
                path.push_back(i);
                simpleDirectedPathes(begin_tag,i,path,visited,table,transfer_times+1,pathes);
                path.pop_back();
                table = tmp;
            }
            else
            {
                path.push_back(i);
                simpleDirectedPathes(begin_tag,i,path,visited,table,transfer_times,pathes);
                path.pop_back();
                table = tmp;
            }
        }
    }
    visited[end_tag] = false;
}

bool Train::ifTransfer(QVector<int> table,int now_station_tag)
{
    for(int i:stations[now_station_tag].lineNums)
    {
        table[i-1]++;
    }
    for(int i=0;i<8;i++)
    {
        if(table[i] == 2)
        {
             return false;
        }
    }
    return true;
}

QVector<int> Train::changeTable(QVector<int> table, int now_station_tag)
{
    for(int i:stations[now_station_tag].lineNums)
    {
        table[i-1]++;
    }
    for(int i=0;i<8;i++)
    {
        if(table[i] == 2)
        {
             table[i]=1;
        }
        else table[i]=0;
    }
    for(int i:table)
    {
        if(i==1) return table;
    }

    for(int i:stations[now_station_tag].lineNums)
    {
        table[i-1]++;
    }
    return table;
}

double Train::getDistance(QVector<int> route)
{
    double dist = 0;
    for(int i=0;i<route.size()-1;i++)
    {
        dist += distanceMatrix[route[i]][route[i+1]];
    }
    return dist;
}
//获取票价
int Train::getPay(double dist)
{
    if(dist <= 4) return 2;
    if(dist > 4 && dist <= 12) return 2+(dist-4)/4+1;
    if(dist > 12 && dist <= 24) return 4+(dist-12)/6+1;
    if(dist > 24 && dist <= 40) return 6+(dist-24)/8+1;
    if(dist > 40 && dist <= 50) return 8+(dist-40)/10+1;
    if(dist > 50) return 9+(dist-50)/20+1;
}

double Train::getThisConpreTime(int lineNum,Time t)
{
    double ret;
    switch (lineNum)
    {
    case 1:
    case 3:
    {
        if(t <= Time(6,0) || t >Time(23,0)) ret = 100;
        else if(t > Time(7,30) && t <= Time(9,0)) ret = 0.8;
        else if(t > Time(16,30) && t <= Time(16,30)) ret = 0.75;
        else ret = 0.4;
        break;
    }
    case 6:
    case 7:
    {
        if(t <= Time(6,0) || t >Time(23,0)) ret = 100;
        else if(t > Time(17,0) && t <= Time(22,0)) ret = 0.65;
        else ret = 0.15;
        break;
    }
    case 2:
    case 4:
    {
        ret = 0.5;
        break;
    }
    case 8:
    {
        if(t <= Time(6,0) || t >Time(23,0)) ret = 100;
        else if(t > Time(9,30) && t <= Time(15,0)) ret = 0.65;
        else return 0.2;
        break;
    }
    default:
    ret = 100;
        break;
    }
    if(ret>0 && ret<0.2) return 1.8;
    else if(ret >= 0.2 && ret<0.75) return 3;
    else if(ret>=0.75 && ret<=1) return 4.5;
    else return INT_MAX;
}

int Train::getSameLineNum(QVector<int> a,QVector<int> b)
{
    QVector<int> table(8,0);
    for(int i:a) table[i-1]++;
    for(int i:b) table[i-1]++;
    for(int i=0;i<8;i++)
    {
        if(table[i] == 2) return i+1;
    }
    return -1;
}


QString Train::getRoute(QVector<int> route,Time nowTime)
{
    int transTimes = 0;
    int spandTime = 0;
    double compreTime = 0;
    QString ans;
    QVector<int> lineNumTable(route.size()-1,-1);
    for(int i=1;i<route.size();i++)
    {
        lineNumTable[i-1] = Train::getSameLineNum(stations[route[i-1]].lineNums,stations[route[i]].lineNums);
    }
    for(int i=0;i<route.size();i++)
    {

        if(i==0) ans += stations[route[i]].stationName+"(乘坐"+QString::number(lineNumTable[0])+"号线)";
        else
        {
            compreTime += getThisConpreTime(lineNumTable[i-1],nowTime);
            if(i!=route.size()-1 && lineNumTable[i-1] != lineNumTable[i])
            {
                nowTime = nowTime + Time(0,3);
                ans+="(换乘"+QString::number(lineNumTable[i])+"号线)";
                transTimes++;
            }
            ans += " ==> "+stations[route[i]].stationName;
            nowTime = nowTime + Time(0,3);
        }

    }
    spandTime = transTimes*3 + (route.size()-1)*3;
    int hour = spandTime/60;
    int minute = spandTime%60;
    QString tmp0 = "预计到达时间: "+QString::number(nowTime.hour)+":";
    if(minute<10) tmp0 = tmp0+"0";
    tmp0 = tmp0+QString::number(nowTime.minute)+"\n";
    ans = tmp0 + ans;
    if(hour == 0) ans = "预计花费时间: "+QString::number(minute)+"min\n" + ans;
    else ans = "预计花费时间: "+QString::number(hour)+"h"+QString::number(minute)+"min\n" + ans;

    ans = "综合评估时间: "+QString::number(compreTime)+"\n" + ans;
    QString tmp = "";
    for(int i=0;i<lineNumTable.size()-1;i++)
    {

        if(lineNumTable[i] != lineNumTable[i+1])
        {
            if(tmp.size() == 0) tmp = tmp+QString::number(lineNumTable[i])+"号线";
            else tmp = tmp+"->"+QString::number(lineNumTable[i])+"号线";
        }
    }
    if(!tmp.isEmpty()) tmp = tmp + "->";
    tmp = tmp + QString::number(lineNumTable.back())+"号线";
    ans = "乘坐: "+tmp+"\n"+ans;
    return ans;
}

void Train::setTime(Time time)
{
    nowTime = time;
}

void Train::setBegin(QString beginN)
{
    this->begin = beginN;
}

void Train::setEnd(QString endN)
{
    this->end = endN;
}
