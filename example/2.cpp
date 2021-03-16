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
typedef int StationsType;//StationsType  �������εı���
typedef struct TrafficNode
{
    char name[MAX_STRING_NUM]; // ������  //MAX_STRING_NUM ��Ϊ 10
    int EndStations; // �������ָ��Ķ����������е�λ�ã����ù���վ���
    int Number ; // ���ڼ�¼ÿվ֮��ľ���
} TrafficNodeDat;
typedef struct VNode
{
    StationsType stations;
    int BusNum; // ������� Bus ������Ԫ�ظ���
    TrafficNodeDat Bus[MAX_TRAFFIC_NUM]; // �����ԱΪ�ṹ�壬��¼�˵�����յ�վ������0���͹�����
} VNodeDat;

VNodeDat AdjList[MAX_VERTEX_NUM];
char StationsName[MAX_VERTEX_NUM][MAX_STRING_NUM]; // ����վ�������õ�һ�±�Ϊ�ó����ڱ������еı��
int StationsNum; // ����վ��Ŀ


int ShowMenu()
{
    printf("\n|****************** ��ӭʹ�ó��н�ͨϵͳ *******|\n");
    printf("\n|------------------1:  ��ӹ���վ --------------|");
    printf("\n|------------------2:  ɾ��������· ------------|");
    printf("\n|------------------3:  ��ӽ�ͨ·�� ------------|");
    printf("\n|------------------4:  ɾ������ ----------------|");
    printf("\n|------------------5:  ��ѯ��̵�·�� ----------|");
    printf("\n|------------------6:  ��ѯ������· ------------|");
    printf("\n|------------------7:  �����Ļ ----------------|");
    printf("\n|------------------0:  �˳� --------------------|");
    printf("\n|***********************************************|\n");
    printf("\n ���������ѡ�� :");
    return 0;
}

int SeekStations(char *name) // Ѱ�ҹ���վ
{
    int i;
    for (i = 0; i<StationsNum; i++)
    {
        if (strcmp(name, StationsName[i]) == 0) // �ȽϺ���������ȣ��򷵻� i ֵ
        {
            return i;
        }
    }
    return -1;
}


int SaveSysInfo() // �������������
{
    FILE *fp;
    int i, j, total;
    fp = fopen(StationsFile, "w"); // �� StationsFile �ĵ�
    fprintf(fp, "%d\n", StationsNum); // ���ĵ���д����վ������
    for (i = 0; i<StationsNum; i++)
    {
        fprintf(fp, "%s\n", StationsName[i]); // ���ĵ���д����վ������
    }
    fclose(fp);// �� StationsFile �ĵ��ر�
    total = 0;
    fp = fopen(BusFile, "w");// �� BusFile �ĵ�
    for (i = 0; i<StationsNum; i++) // ���㹫��������
    {
        total += AdjList[i].BusNum;
    }
    fprintf(fp, "%d\n", total); // ���ĵ���д����������
    for (i = 0; i<StationsNum; i++) //
    {
        for (j = 0; j<AdjList[i].BusNum; j++) // ���ĵ���д�����ĳ��Ρ�ʼ��վ���յ�վ
        {
            fprintf(fp, "%s %s %s ", AdjList[i].Bus[j].name,
                                     StationsName[i],
                                     StationsName[AdjList[i].Bus[j].EndStations]);
            fprintf(fp, " %d\n", AdjList[i].Bus[j].Number);// ���ĵ���д
        }
    }
    fclose(fp);

    return 1;
}

int InsertStations(char *Name) // ��ӹ���վ
{
    strcpy(StationsName[StationsNum], Name);
    AdjList[StationsNum].stations = StationsNum;
    AdjList[StationsNum].BusNum = 0;
    StationsNum++;
    return 1;
}

int DelStations(char *Name) // ɾ������վ
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
            printf(" δ�ҵ��˹���վ�����������룡 ");
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

int InsertBus(char *bus, char *StartCity, char *EndStations, int number)//��ӹ���
{
    int i, j;
    i = SeekStations(StartCity);
    j = SeekStations(EndStations);
    AdjList[i].Bus[AdjList[i].BusNum].Number = number;
    AdjList[i].Bus[AdjList[i].BusNum].EndStations = j;
    strcpy(AdjList[i].Bus[AdjList[i].BusNum].name, bus);
    AdjList[i].BusNum++; // ���������� 1
    return 1;
}

int DelPath(char *name)// ɾ������
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
            for (; j<AdjList[i].BusNum - 1; j++) // ��ɾ���Ĺ������ÿ��������ǰ��һλ
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
        fscanf(fp, "%s", &stmp1); // �����ĳ���
        fscanf(fp, "%s", &stmp2); // ������ʼ��վ
        fscanf(fp, "%s", &stmp3); // �������յ�վ
        j = SeekStations(stmp2);
        AdjList[j].Bus[AdjList[j].BusNum].EndStations = SeekStations(stmp3); // �������ĳ��š�ʼ��վ���յ�վ����
        strcpy(AdjList[j].Bus[AdjList[j].BusNum].name, stmp1);
        fscanf(fp, "%d", &number);
        AdjList[j].Bus[AdjList[j].BusNum].Number = number;
        AdjList[j].BusNum++;
    }
    fclose(fp);
    return 1;
}

int SearchBus(char *name)// ��ѯ����վ
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
        fscanf(fp, "%s", &stmp1); // �����ĳ���
        fscanf(fp, "%s", &stmp2); // ������ʼ��վ
        fscanf(fp, "%s", &stmp3); // �������յ�վ
        fscanf(fp, "%d", &stmp4); // ����վ֮��ľ���
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
    char name[MAX_STRING_NUM]; // ����վ��
    char s_city[MAX_STRING_NUM]; // ʼ��վ
    char e_city[MAX_STRING_NUM]; // �յ�վ
    int Command, number = 1;
    int startcity, endcity, traveltype = 0;
    while (true)
    {
        printf("\n");
        ShowMenu(); // ���˵�
        scanf("%d", &Command);// ����ѡ��
        switch (Command) // �Բ˵������ݽ���ѡ��
        {
        case 0: // �˳�
            return 0;
        case 1: // ��ӹ���
            InitSysData(); // �����ĵ����Ѵ����Ϣ
            printf("\n ���빫��վ�� :");
            scanf("%s", &name); // ���������
            InsertStations(name); // �����в��뵽������
            SaveSysInfo(); // �ѹ�������Ϣд���ĵ���
            printf(" Save OK!\n");
            break;
        case 2: // ɾ������վ
            InitSysData(); // �����ĵ������е���Ϣ
            printf("\n ���빫��վ�� :");
            scanf("%s", &name);
            DelStations(name); // ������ɾ��
            SaveSysInfo(); // �����������Ϣд���ĵ���
            printf("Save OK!\n");
            break;
        case 3: // ���·��
            InitSysData();
            printf(" ��ʼ����վ�� :");
            scanf("%s", &s_city); // ��ʼվ
            printf(" �յ㹫��վ�� :");
            scanf("%s", &e_city); // �յ�վ
            printf(" ���빫����  :");
            scanf("%s", &name);
            printf(" ���� :");
            scanf("%d", &number);
            InsertBus(name, s_city, e_city, number);
            SaveSysInfo();

            printf(" Save OK!\n");
            break;
        case 4: // ɾ������
            InitSysData();
            printf(" ������Ҫɾ���Ĺ������� :");
            scanf("%s", &name);
            DelPath(name); // ��·�߽���ɾ��
            SaveSysInfo();
            printf("Save OK!\n");
            break;
        /*case 5: // ��С����վ
            InitSysData();
            printf("\n ��ʼ����վ :");
            scanf("%s", &name);
            startcity = SeekStations(name);
            if (startcity<0)
            {
                printf("Error station Name:No such station!\n");
                break;
            }
            printf(" �յ㹫��վ :");
            scanf("%s", &name);
            endcity = SeekStations(name);
            if (endcity<0)
            {
                printf("Error station Name:No such station!\n");
                break;
            }
            //CalcMinNum(startcity, endcity, traveltype); // �������ٵ�վ��
            printf("\n");
            break;
            */
        case 6:
            InitSysData();
            printf(" ���빫���� :");
            scanf("%s", &name);
            SearchBus(name);
            break;
        case 7:
            system("cls");// �����Ļ
        }
    }
}

