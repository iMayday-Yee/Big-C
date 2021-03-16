#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERR 0
#define OK 1
#define Dij_MAXN 100
#define MAX_VERTEX_NUM 100
#define MAX_STRING_NUM 100
#define MAX_TRAFFIC_NUM 100

const char StationsFile[] = "stations.txt";
const char BusFile[] = "bus.txt";
typedef int StationsType;//StationsType  定义整形的变量
typedef struct TrafficNode
{
    char name[MAX_STRING_NUM]; // 公交号  //MAX_STRING_NUM 最为 10
    int EndStations; // 该有向边指向的顶点在数组中的位置，即该公交站编号
    int Number ; // 用于记录每站之间的距离
} TrafficNodeDat;
typedef struct VNode
{
    StationsType stations;
    int BusNum; // 标记下面 Bus 数组里元素个数
    TrafficNodeDat Bus[MAX_TRAFFIC_NUM]; // 数组成员为结构体，记录了到达的终点站、距离0、和公交号
} VNodeDat;

VNodeDat AdjList[MAX_VERTEX_NUM];
char StationsName[MAX_VERTEX_NUM][MAX_STRING_NUM]; // 公交站名，采用第一下标为该城市在本程序中的编号
int StationsNum; // 公交站数目


int ShowMenu()
{
    printf("\n|****************** 欢迎使用城市交通系统 *******|\n");
    printf("\n|------------------1:  添加公交站 --------------|");
    printf("\n|------------------2:  删除公交线路 ------------|");
    printf("\n|------------------3:  添加交通路线 ------------|");
    printf("\n|------------------4:  删除公交 ----------------|");
    printf("\n|------------------5:  查询最短的路线 ----------|");
    printf("\n|------------------6:  查询公交线路 ------------|");
    printf("\n|------------------7:  清除屏幕 ----------------|");
    printf("\n|------------------0:  退出 --------------------|");
    printf("\n|***********************************************|\n");
    printf("\n 请输入你的选择 :");
    return 0;
}

int SeekStations(char *name) // 寻找公交站
{
    int i;
    for (i = 0; i<StationsNum; i++)
    {
        if (strcmp(name, StationsName[i]) == 0) // 比较函数，若相等，则返回 i 值
        {
            return i;
        }
    }
    return -1;
}


int SaveSysInfo() // 向程序输入数据
{
    FILE *fp;
    int i, j, total;
    fp = fopen(StationsFile, "w"); // 打开 StationsFile 文档
    fprintf(fp, "%d\n", StationsNum); // 往文档中写公交站的数量
    for (i = 0; i<StationsNum; i++)
    {
        fprintf(fp, "%s\n", StationsName[i]); // 往文档中写公交站的名字
    }
    fclose(fp);// 将 StationsFile 文档关闭
    total = 0;
    fp = fopen(BusFile, "w");// 打开 BusFile 文档
    for (i = 0; i<StationsNum; i++) // 计算公交的数量
    {
        total += AdjList[i].BusNum;
    }
    fprintf(fp, "%d\n", total); // 往文档中写公交的数量
    for (i = 0; i<StationsNum; i++) //
    {
        for (j = 0; j<AdjList[i].BusNum; j++) // 往文档中写公交的车次、始发站、终点站
        {
            fprintf(fp, "%s %s %s ", AdjList[i].Bus[j].name,
                                     StationsName[i],
                                     StationsName[AdjList[i].Bus[j].EndStations]);
            fprintf(fp, " %d\n", AdjList[i].Bus[j].Number);// 往文档中写
        }
    }
    fclose(fp);

    return 1;
}

int InsertStations(char *Name) // 添加公交站
{
    strcpy(StationsName[StationsNum], Name);
    AdjList[StationsNum].stations = StationsNum;
    AdjList[StationsNum].BusNum = 0;
    StationsNum++;
    return 1;
}

int DelStations(char *Name) // 删除公交站
{
    int stations, i, j,o=1,k=0;
    stations = SeekStations(Name);
    printf("%s",Name);
    while (true)
    {
        while (strcmp(StationsName[k], Name) != 0)
        {
            k++;
        }
        if (k > StationsNum)
        {
            o--;
            printf(" 未找到此公交站，请重新输入！ ");
            return 0;
        }
        for (i = stations; i < StationsNum - 1; i++)
        {
            strcpy(StationsName[i], StationsName[i + 1]);
            AdjList[i].BusNum = AdjList[i + 1].BusNum;
            for (j = 0; j < AdjList[i].BusNum; j++)
            {
                strcpy(AdjList[i].Bus[j].name, AdjList[i + 1].Bus[j].name);
                AdjList[i].Bus[j].EndStations = AdjList[i + 1].Bus[j].EndStations;
                AdjList[i].Bus[j].Number = AdjList[i + 1].Bus[j].Number;
            }
        }
        StationsNum--;
    }
    return 1;
}

int InsertBus(char *bus, char *StartCity, char *EndStations, int number)//添加公交
{
    int i, j;
    i = SeekStations(StartCity);
    j = SeekStations(EndStations);
    AdjList[i].Bus[AdjList[i].BusNum].Number = number;
    AdjList[i].Bus[AdjList[i].BusNum].EndStations = j;
    strcpy(AdjList[i].Bus[AdjList[i].BusNum].name, bus);
    AdjList[i].BusNum++; // 公交的数加 1
    return 1;
}

int DelPath(char *name)// 删除公交
{
    int i, j, flag = 0;
    for (i = 0; i<StationsNum; i++)
    {
        for (j = 0; j<AdjList[i].BusNum; j++)
            if (strcmp(AdjList[i].Bus[j].name, name) == 0)
            {
                flag = 1;
                break;
            }
        if (flag==0)
        {
            for (; j<AdjList[i].BusNum - 1; j++) // 把删除的公交后的每个公交都前移一位
            {
                AdjList[i].Bus[j].Number = AdjList[i].Bus[j + 1].Number;
                AdjList[i].Bus[j].EndStations = AdjList[i].Bus[j + 1].EndStations;
                strcpy(AdjList[i].Bus[j].name, AdjList[i].Bus[j + 1].name);
            }
            AdjList[i].BusNum--;
            break;
        }
    }
    return 1;
}

int InitSysData()
{
    FILE *fp;
    int i, j, num, number;
    char stmp1[MAX_STRING_NUM];
    char stmp2[MAX_STRING_NUM];
    char stmp3[MAX_STRING_NUM];
    fp = fopen(StationsFile, "r");
    if (!fp)
    {
        printf("\nError:Cannot Open Stations File...\n");
        return -1;
    }
    fscanf(fp, "%d", &StationsNum);
    for (i = 0; i<StationsNum; i++)
    {
        fscanf(fp, "%s", &StationsName[i]);
        AdjList[i].stations = i;
        AdjList[i].BusNum = 0;
    }
    fclose(fp);
    fp = fopen(BusFile, "r");
    if (!fp)
    {
        printf("\nError:Cannot Open Bus File...\n");
        return -1;
    }
    fscanf(fp, "%d", &num);
    for (i = 0; i<num; i++)
    {
        fscanf(fp, "%s", &stmp1); // 公交的车次
        fscanf(fp, "%s", &stmp2); // 公交的始发站
        fscanf(fp, "%s", &stmp3); // 公交的终点站
        j = SeekStations(stmp2);
        AdjList[j].Bus[AdjList[j].BusNum].EndStations = SeekStations(stmp3); // 将公交的车号、始发站、终点站读出
        strcpy(AdjList[j].Bus[AdjList[j].BusNum].name, stmp1);
        fscanf(fp, "%d", &number);
        AdjList[j].Bus[AdjList[j].BusNum].Number = number;
        AdjList[j].BusNum++;
    }
    fclose(fp);
    return 1;
}

int SearchBus(char *name)// 查询公交站
{
    FILE *fp;
    int i, j, num, number;
    char stmp1[MAX_STRING_NUM];
    char stmp2[MAX_STRING_NUM];
    char stmp3[MAX_STRING_NUM];
    int stmp4;
    fp = fopen(BusFile, "r");
    if (!fp)
    {
        printf("\nError:Cannot Open Bus File...\n");
        return -1;
    }
    fscanf(fp, "%d", &num);
    for (i = 0; i<num; i++)
    {
        fscanf(fp, "%s", &stmp1); // 公交的车次
        fscanf(fp, "%s", &stmp2); // 公交的始发站
        fscanf(fp, "%s", &stmp3); // 公交的终点站
        fscanf(fp, "%d", &stmp4); // 公交站之间的距离
        if(strcmp(stmp1,name) == 0)
        {
            printf("%s  %s  %s  %d\n" , stmp1 ,stmp2 ,stmp3 ,stmp4);
        }
    }
    fclose(fp);
    return 1;
}

int main()
{
    char name[MAX_STRING_NUM]; // 公交站名
    char s_city[MAX_STRING_NUM]; // 始发站
    char e_city[MAX_STRING_NUM]; // 终点站
    int Command, number = 1;
    int startcity, endcity, traveltype = 0;
    while (true)
    {
        printf("\n");
        ShowMenu(); // 主菜单
        scanf("%d", &Command);// 输入选择
        switch (Command) // 对菜单的内容进行选择
        {
        case 0: // 退出
            return 0;
        case 1: // 添加公交
            InitSysData(); // 读出文档中已存的信息
            printf("\n 输入公交站名 :");
            scanf("%s", &name); // 输入城市名
            InsertStations(name); // 将城市插入到数组中
            SaveSysInfo(); // 把公交的信息写入文档中
            printf(" Save OK!\n");
            break;
        case 2: // 删除公交站
            InitSysData(); // 读出文档中已有的信息
            printf("\n 输入公交站名 :");
            scanf("%s", &name);
            DelStations(name); // 将公交删除
            SaveSysInfo(); // 将处理过的信息写入文档中
            printf("Save OK!\n");
            break;
        case 3: // 添加路线
            InitSysData();
            printf(" 起始公交站名 :");
            scanf("%s", &s_city); // 起始站
            printf(" 终点公交站名 :");
            scanf("%s", &e_city); // 终点站
            printf(" 输入公交号  :");
            scanf("%s", &name);
            printf(" 距离 :");
            scanf("%d", &number);
            InsertBus(name, s_city, e_city, number);
            SaveSysInfo();

            printf(" Save OK!\n");
            break;
        case 4: // 删除公交
            InitSysData();
            printf(" 输入需要删除的公交车名 :");
            scanf("%s", &name);
            DelPath(name); // 将路线进行删除
            SaveSysInfo();
            printf("Save OK!\n");
            break;
        /*case 5: // 最小所坐站
            InitSysData();
            printf("\n 起始公交站 :");
            scanf("%s", &name);
            startcity = SeekStations(name);
            if (startcity<0)
            {
                printf("Error station Name:No such station!\n");
                break;
            }
            printf(" 终点公交站 :");
            scanf("%s", &name);
            endcity = SeekStations(name);
            if (endcity<0)
            {
                printf("Error station Name:No such station!\n");
                break;
            }
            //CalcMinNum(startcity, endcity, traveltype); // 计算最少的站数
            printf("\n");
            break;
            */
        case 6:
            InitSysData();
            printf(" 输入公交号 :");
            scanf("%s", &name);
            SearchBus(name);
            break;
        case 7:
            system("cls");// 清除屏幕
        }
    }
}

