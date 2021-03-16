#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6011)
#pragma warning(disable:6387)
#pragma warning(disable:28182)
#pragma warning(disable:4715)
#pragma warning(disable:6385)
#pragma warning(disable:26451)
#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<algorithm>
#include"PrintAndChoose.h"
#include"MetroStruct.h"
#define MAX_NUM_LINE 10
using namespace std;

void MainPage();
void InputMap();
void InputByKey();
void InputByFile();
void ViewMap();
void StartTrip();
void Exit();
void MakeMap();
void StepView();
void RunTime();
void FindRoad(Map &map, int startstationnum, int endstationnum, int f);
void MakeVMap();
void SortByTime();
void SortByPrice();
void SortByMind();
void Confuse();
void PrintResult();
void SetYongjidu0();
void SetYongjidu();
bool cmp(Solution a, Solution b);
bool CmpByTime(Solution a, Solution b);
bool CmpByPrice(Solution a, Solution b);
bool CmpByMind(Solution a, Solution b);
int LinenumToLinknum(int a);
int FindMaxNum();

int path[100];
int visited[200];
int startno, endno;
int maxofsolution;
int starth, startmin;
Line line[MAX_NUM_LINE];//��ʼ��MAX_NUM_LINE����·
Line* line0, * line1;//ָ��Ŀǰ��������·
Station* station0, * station1;//ָ��Ŀǰ������վ��
int sum_line;//��·������
Map map;
Edge edge[200][200];
Solution solution[5];
Station* start0, * end0;
Quan quan[10][48];
Quan quan0[10][48];
char stationnames[200][20];
int FLAG=0;

void MainPage()
{
	SetYongjidu0();
	switch (Output_Welcome())
	{
		case 1:
			InputMap();
			break;
		case 2:
			ViewMap();
			break;
		case 3:
			StepView();
			break;
		case 4:
			RunTime();
			break;
		case 5:
			StartTrip();
			break;
		case 6:
			SetYongjidu();
		case 0:
			Exit();
			break;
	}
	return;
}

void InputMap()
{
	switch (Output_InputMap())
	{
		case 1:
			Output_InputByKey();
			InputByKey();
			break;
		case 2:
			Output_InputByFile();
			InputByFile();
			break;
		case 0:
			MainPage();
			break;
	}
	return;
}



//ͨ�����̼�����·����
/*
�����ʽ��
��·������(sum_line)
#��·���1(line0->line_order) ��·�ܳ�1(line0->length) ��·վ������1(line0->num_station)
##վ�����11(station0->station_order) վ����11(station0->name) վ�����12 վ����12 վ�����13 վ����13 ...
#��·���2(line0->line_order) ��·�ܳ�2(line0->length) ��·վ������2(line0->num_station)
##վ�����21(station0->station_order) վ����21(station0->name) վ�����22 վ����22 վ�����23 վ����23 ...
...
*/
void InputByKey()
{
	cin >> sum_line;//������·������
	for (int i = 0; i < sum_line; i++)
	{
		line0 = &line[i];
		cin >> line0->line_order;
		cin >> line0->length;
		cin >> line0->num_station;
		line0->eachlen = line0->length / (line0->num_station - 1.0);
		line0->start = (Station*)malloc(sizeof(Station));
		station0 = line0->start;//ָ��Ŀǰ������վ��
		station0->pre = NULL;
		for (int j = 0; j < line0->num_station; j++)
		{
			cin >> station0->station_order;
			cin >> station0->name;
			cin >> station0->exline1 >> station0->exorder1 >> station0->exline2 >> station0->exorder2;
			station0->equal1 = NULL;
			station0->equal2 = NULL;
			station0->next = (Station*)malloc(sizeof(Station));
			station0->next->pre = station0;
			station0 = station0->next;
		}
		station0->pre->next = NULL;
	}
	MakeMap();
	printf("�ɹ�������ͼ��\n");
	system("pause");
	MainPage();
}

//ͨ���ļ���ȡ��·����
void InputByFile()
{
	char filename[50] = {0};
LOOP3:
	scanf("%s", filename);
	FILE *fp=fopen(filename, "r");
	while(fp==NULL)
	{
		printf("���ļ������ڣ�\n");
		printf("��������ȷ���ļ�·����\n");
		goto LOOP3;
	}
	fscanf(fp, "%d", &sum_line);
	for (int i = 0; i < sum_line; i++)
	{
		line0 = &line[i];
		fscanf(fp, "%d", &line0->line_order);
		fscanf(fp, "%lf", &line0->length);
		fscanf(fp, "%d", &line0->num_station);
		line0->eachlen = line0->length / (line0->num_station - 1.0);
		line0->start = (Station*)malloc(sizeof(Station));
		station0 = line0->start;//ָ��Ŀǰ������վ��
		station0->pre = NULL;
		for (int j = 0; j < line0->num_station; j++)
		{
			fscanf(fp, "%d", &station0->station_order);
			fscanf(fp, "%s", station0->name);
			fscanf(fp, "%d %d %d %d", &station0->exline1, &station0->exorder1, &station0->exline2, &station0->exorder2);
			station0->equal1 = NULL;
			station0->equal2 = NULL;
			station0->next = (Station*)malloc(sizeof(Station));
			station0->next->pre = station0;
			station0 = station0->next;
		}
		station0->pre->next = NULL;
	}
	fclose(fp);
	MakeMap();
	printf("�ɹ�������ͼ��\n");
	system("pause");
	MainPage();
}

//���ڲ�����5���ߣ����ң�����line[]�Ǵ�line[0]��ʼ��ŵ�1����
//��ˣ�Ϊ��ʹ�������·���ָ���Ӧ������Ԫ�أ������˸ú���
int LinenumToLinknum(int a)
{
	if (1 <= a && a <= 4)
		return a - 1;
	else if (6 <= a && a <= 8)
		return a - 2;
}

//������������������·ͼ��������������˫������
//�����ڲ�ͬ��·�е���ͬվ��û����ϵ����
//�˺�������Ϊ����ͬ��վ����ϵ����

void MakeMap()
{
	int k;
	for (int i = 0; i < MAX_NUM_LINE; i++)
	{
		line0 = &line[i];
		if (line0 == NULL)
			continue;
		else
		{
			station0 = line0->start;
			while (station0 != NULL)
			{
				if (station0->exline1 == 0)
				{
					station0 = station0->next;
					continue;
				}
				else
				{
					line1 = &line[LinenumToLinknum(station0->exline1)];
					station1 = line1->start;
					k = station0->exorder1-1;
					while (k--)
					{
						station1 = station1->next;
					}
					station0->equal1 = station1;
					if (station0->exline2 != 0)
					{
						line1 = &line[LinenumToLinknum(station0->exline2)];
						station1 = line1->start;
						k = station0->exorder2 - 1;
						while (k--)
						{
							station1 = station1->next;
						}
						station0->equal2 = station1;
					}
					station0 = station0->next;
				}
			}

		}
	}
}


void ViewMap()
{
	if (sum_line==0)//�ж��Ƿ��Ѿ���������·��Ϣ
	{
		printf("����������·ͼ���ݣ�\n");
		system("pause");
		MainPage();
		return;
	}
	else
	{
		int viewnum = Output_View_LineChoose();
		if (viewnum == 0)
		{
			MainPage();
			return;
		}
		viewnum = LinenumToLinknum(viewnum);//���������·��ת��Ϊline[i]�е�i
		Line* lineview = &line[viewnum];
		Station* viewnow = lineview->start;
		while (viewnow)
		{
			printf("%d %s\n", viewnow->station_order, viewnow->name);
			viewnow = viewnow->next;
		}
		system("pause");
		ViewMap();
	}
}

void StepView()
{
	int op_step,exchoose;
	if (sum_line == 0)//�ж��Ƿ��Ѿ���������·��Ϣ
	{
		printf("����������·ͼ���ݣ�\n");
		system("pause");
		MainPage();
		return;
	}
	else
	{
		int viewnum = Output_View_LineChoose();
		if (viewnum == 0)
		{
			MainPage();
			return;
		}
		viewnum = LinenumToLinknum(viewnum);//���������·��ת��Ϊline[i]�е�i
		Line* lineview = &line[viewnum];
		Station* viewnow = lineview->start;
		while (viewnow)
		{
			printf("%d %s\n", viewnow->station_order, viewnow->name);
			viewnow = viewnow->next;
		}
		station0 = Output_StepStart(viewnum, line);
		if (station0 == 0)
		{
			MainPage();
			return;
		}
		else
		{
			while (1)
			{
				scanf("%d", &op_step);
				if (op_step == 0)
				{
					MainPage();
					return;
				}
				//���ѡ�����һվ����
				else if (op_step == 1)
				{
					if (station0->equal1==NULL)//�����һվ���ǻ���վ
					{
						if (station0->next == NULL)//���û����һվ
						{
							printf("û����һվ�ˣ�\n");
						}
						else
						{
							station0 = station0->next;
							printf("�������� %s ��\n", station0->name);
						}
					}
					else//�����һվ�ǻ���վ
					{
						if (station0->equal2 == NULL)//�����һվֻ��һ������·��
						{
							printf("��վ����Ի��˵�%d���ߣ������뻻����·���:(����0ѡ�񲻻���)\n", station0->exline1);
							scanf("%d", &exchoose);
							if (exchoose == 0)
							{
								printf("��ѡ��ԭ��·��ʻ�������ѡ����·�н�����\n");
								station0 = station0;
							}
							else
							{
								printf("���ѻ��˵�%d���ߣ������ѡ����·�н�����\n", station0->exline1);
								station0 = station0->equal1;
							}
LOOP6:
							scanf("%d", &op_step);
							if (op_step == 1)
							{
								if (station0->next == NULL)
								{
									printf("û����һվ�ˣ�\n");
									goto LOOP6;
								}
								else
								{
									station0 = station0->next;
									printf("�������� %s ��\n", station0->name);
								}
							}
							else if (op_step == 2)
							{
								if (station0->pre == NULL)
								{
									printf("û����һվ�ˣ�\n");
									goto LOOP6;
								}
								station0 = station0->pre;
								printf("�������� %s ��\n", station0->name);
							}
						}
						else//�����һվ����������·��
						{
							printf("��վ����Ի��˵�%d���ߺ�%d���ߣ������뻻����·���:(����0ѡ�񲻻���)\n", station0->exline1, station0->exline2);
							scanf("%d", &exchoose);
							if (exchoose == 0)
							{
								printf("��ѡ��ԭ��·��ʻ�������ѡ����·�н�����\n");
								station0 = station0;
							}
							else if (exchoose == station0->exline1)
							{
								printf("���ѻ��˵�%d���ߣ������ѡ����·�н�����\n", station0->exline1);
								station0 = station0->equal1;
							}
							else
							{
								printf("���ѻ��˵�%d���ߣ������ѡ����·�н�����\n", station0->exline2);
								station0 = station0->equal2;
							}
LOOP7:
							scanf("%d", &op_step);
							{
								if (op_step == 1)
								{
									if (station0->next == NULL)
									{
										printf("û����һվ�ˣ�\n");
										goto LOOP7;
									}
									else
									{
										station0 = station0->next;
										printf("�������� %s ��\n", station0->name);
									}
								}
								else if (op_step == 2)
								{
									if (station0->pre == NULL)
									{
										printf("û����һվ�ˣ�\n");
										goto LOOP6;
									}
									station0 = station0->pre;
									printf("�������� %s ��\n", station0->name);
								}
							}	
						}
					}
				}
				//���ѡ����ǰһվ����
				else if (op_step == 2)
				{
					if (station0->equal1 == NULL)//�����һվ���ǻ���վ
					{
						if (station0->pre == NULL)//���û����һվ
						{
							printf("û����һվ�ˣ�\n");
						}
						else
						{
							station0 = station0->pre;
							printf("�������� %s ��\n", station0->name);
						}
					}
					else//�����һվ�ǻ���վ
					{
						if (station0->equal2 == NULL)//�����һվֻ��һ������·��
						{
							printf("��վ����Ի��˵�%d���ߣ������뻻����·���:(����0ѡ�񲻻���)\n", station0->exline1);
							scanf("%d", &exchoose);
							if (exchoose == 0)
							{
								printf("��ѡ��ԭ��·��ʻ�������ѡ����·�н�����\n");
								station0 = station0;
							}
							else
							{
								printf("���ѻ��˵�%d���ߣ������ѡ����·�н�����\n", station0->exline1);
								station0 = station0->equal1;
							}
LOOP8:
							scanf("%d", &op_step);
							if (op_step == 1)
							{
								if (station0->next == NULL)
								{
									printf("û����һվ�ˣ�\n");
									goto LOOP6;
								}
								else
								{
									station0 = station0->next;
									printf("�������� %s ��\n", station0->name);
								}
							}
							else if (op_step == 2)
							{
								if (station0->pre == NULL)
								{
									printf("û����һվ�ˣ�\n");
									goto LOOP8;
								}
								station0 = station0->pre;
								printf("�������� %s ��\n", station0->name);
							}
						}
						else//�����һվ����������·��
						{
							printf("��վ����Ի��˵�%d���ߺ�%d���ߣ������뻻����·���:(����0ѡ�񲻻���)\n", station0->exline1, station0->exline2);
							scanf("%d", &exchoose);
							if (exchoose == 0)
							{
								printf("��ѡ��ԭ��·��ʻ�������ѡ����·�н�����\n");
								station0 = station0;
							}
							else if (exchoose == station0->exline1)
							{
								printf("���ѻ��˵�%d���ߣ������ѡ����·�н�����\n", station0->exline1);
								station0 = station0->equal1;
							}
							else
							{
								printf("���ѻ��˵�%d���ߣ������ѡ����·�н�����\n", station0->exline2);
								station0 = station0->equal2;
							}
LOOP9:
							scanf("%d", &op_step);
							if (op_step == 1)
							{
								if (station0->next == NULL)
								{
									printf("û����һվ�ˣ�\n");
									goto LOOP9;
								}
								else
								{
									station0 = station0->next;
									printf("�������� %s ��\n", station0->name);
								}
							}
							else if (op_step == 2)
							{
								if (station0->pre == NULL)
								{
									printf("û����һվ�ˣ�\n");
									goto LOOP6;
								}
								station0 = station0->pre;
								printf("�������� %s ��\n", station0->name);
							}
						}
					}
				}
			}
		}
	}
}

//�г�����ʱ�̱�
void RunTime()
{
	if (sum_line == 0)
	{
		printf("����������·ͼ���ݣ�\n");
		system("pause");
		MainPage();
		return;
	}
	else
	{
		Output_Runtime(line);
		MainPage();
		return;
	}
}


void StartTrip()
{
	MakeVMap();
	if (sum_line == 0)
	{
		printf("����������·ͼ���ݣ�\n");
		system("pause");
		MainPage();
		return;
	}
	start0 = Output_Start(line);
	end0 = Output_End(line);
	//printf("��ѡ���� %s ��Ϊ����վ�㣬%s ��ΪĿ��վ�㣡\n", start0->name, end0->name);
	for (int i = 1; i < 198; i++)
	{
		if (strcmp(stationnames[i], start0->name) == 0)
		{
			startno = i;
			break;
		}
		else
			continue;
	}
	for (int j = 1; j < 198; j++)
	{
		if (strcmp(stationnames[j], end0->name) == 0)
		{
			endno = j;
			break;
		}
		else
			continue;
	}
	for (int k = 0; k < 5; k++)
	{
		solution[k].numofstation = 50;
	}
	FindRoad(map, startno, endno, 0);
	sort(solution, solution+5, cmp);
	system("cls");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("��        Welcome to take metro of Wuhan!          ��\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("�� 1.Sort by time you will spend                   ��\n");
	printf("�� 2.Sort by price                                 ��\n");
	printf("�� 3.Sort by time in mind                          ��\n");
	printf("�� 0.Exit                                          ��\n");
	printf("��                                                 ��\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("��ѡ���� %s ��Ϊ����վ�㣬%s ��ΪĿ��վ�㣡\n", start0->name, end0->name);
	printf("�����뵱ǰʱ�̣�\n");
	scanf_s("%d:%d", &starth, &startmin);
	Confuse();
	printf("��ѡ��һ�����򷽰���\n");
	int op_fchoose;
	scanf_s("%d", &op_fchoose);
	switch (op_fchoose)
	{
		case 1:
			sort(solution, solution + 5, CmpByTime);
			break;
		case 2:
			sort(solution, solution + 5, CmpByPrice);
			break;
		case 3:
			sort(solution, solution + 5, CmpByMind);
			break;
		case 0:
			MainPage();
			return;
			break;
	}
	PrintResult();
	system("pause");
	MainPage();
	return;
}

void Confuse()
{
	
	double runtime = 0;
	int smin = startmin;
	double sumtime;
	double dertmin = smin % 3;
	for (int i = 0; i < 5; i++)
	{
		if (solution[i].numofstation == 50)
			continue;
		else
		{
			runtime = 3.0 * (solution[i].numofstation - 1);
			for (int j = 0; j < solution[i].numofstation-2; j++)
			{
				if (edge[abs(solution[i].sta[j])][abs(solution[i].sta[j + 1])].line == edge[abs(solution[i].sta[j + 1])][abs(solution[i].sta[j + 2])].line)
					continue;
				else
				{
					solution[i].sta[j + 1] = 0 - solution[i].sta[j + 1];
					runtime += 3.5;
				}
			}
			sumtime = runtime + dertmin;
			solution[i].time = sumtime;
			solution[i].endh = starth + ((int)solution[i].time + startmin) / 60;
			solution[i].endmin = startmin + ((int)solution[i].time + startmin) % 60;
			sumtime = 0;
			for (int j = 0; j < solution[i].numofstation - 1; j++)
			{
				solution[i].length += line[LinenumToLinknum(edge[abs(solution[i].sta[j])][abs(solution[i].sta[j + 1])].line)].eachlen;
			}
			if (solution[i].length <= 4.0)
				solution[i].price = 2;
			else if (solution[i].length > 4.0 && solution[i].length <= 12.0)
				solution[i].price = 2 + (((int)solution[i].length - 4) / 4) + 1;
			else if (solution[i].length > 12.0 && solution[i].length <= 24.0)
				solution[i].price = 4 + (((int)solution[i].length - 12) / 6) + 1;
			else if (solution[i].length > 24.0 && solution[i].length <= 40.0)
				solution[i].price = 6 + (((int)solution[i].length - 24) / 8) + 1;
			else if (solution[i].length > 40.0 && solution[i].length <= 50.0)
				solution[i].price = 8 + (((int)solution[i].length - 40) / 10) + 1;
			else
				solution[i].price = 9 + (((int)solution[i].length - 50) / 20) + 1;
		}
		if (FLAG == 0)
			solution[i].timeinmind = 1.113 * solution[i].time;
		else if(FLAG == 1)
		{
			solution[i].timeinmind = 0.811 * solution[i].time;
		}
		else if(FLAG == 2)
		{
			solution[i].timeinmind = 0.677 * solution[i].time;
		}
		else if(FLAG == 3)
		{
			solution[i].timeinmind = 0.744 * solution[i].time;
		}
		else
		{
			solution[i].timeinmind = 0.911 * solution[i].time;
		}
	}
	


}

bool CmpByTime(Solution a, Solution b)
{
	return a.time < b.time;
}

bool CmpByPrice(Solution a, Solution b)
{
	return a.price < b.price;
}

bool CmpByMind(Solution a, Solution b)
{
	return a.timeinmind < b.timeinmind;
}

void PrintResult()
{
	int flag = 0;
	printf("�Ƽ�·�����£�\n");
	for (int i = 0; i < 3; i++)
	{

		if (solution[i].numofstation == 50)
			continue;
		if (solution[i].endh < 6 || solution[i].endh >= 23)
		{
			flag++;
			continue;
		}
		else
		{
			printf("#·��%d:\n", i + 1 - flag);
			for (int j = 0; j < solution[i].numofstation; j++)
			{
				if (j == solution[i].numofstation - 1)
					printf("%s\n", stationnames[abs(solution[i].sta[j])]);
				else
				{
					if (solution[i].sta[j] >= 0)
						printf("%s->", stationnames[solution[i].sta[j]]);
					else
						printf("%s��%d����ת%d���ߣ�->", stationnames[abs(solution[i].sta[j])], edge[abs(solution[i].sta[j - 1])][abs(solution[i].sta[j])].line, edge[abs(solution[i].sta[j])][abs(solution[i].sta[j + 1])].line);
				}
			}
			printf("����·������%d��վ��\t�ܾ���:%.2lfkm\n", solution[i].numofstation, solution[i].length);
			printf("ʵ�ʻ���ʱ�䣺%.1lfmin\tʵ�ʵ���ʱ��:%d:%02d\n", solution[i].time, solution[i].endh, solution[i].endmin);
			printf("��Ʊ��:%dԪ\n", solution[i].price);

			printf("ӵ���ȼ�Ȩʱ��:%.2lfmin\n", solution[i].timeinmind);
		}
	}
	if (flag >= 3)
		printf("��ǰʱ�䲻�ɵ���!\n");
}

int FindMaxNum()
{
	int a = 0;
	for (int i = 0; i < 5; i++)
	{
		a = a > solution[i].numofstation ? a : solution[i].numofstation ;
	}
	return a;
}

void FindRoad(Map &map, int x, int y, int i)
{
	maxofsolution = FindMaxNum();
	if (i + 2 > maxofsolution)
		return;
	visited[x] = 1;//��Ǹõ�
	int j;
	path[i] = x;//����·��
	for (j = map.num_dot - 1; j >= 0; j--)//�����ڽӵ�
	{
		if (map.edge[x][j] != 0)
		{
			if (j == y)//���㵽����v
			{
				path[i+1] = j;
				if (i + 2 > maxofsolution)
					break;
				for (int v = 0; v < 5; v++)
				{
					if (solution[v].numofstation == maxofsolution)
					{
						for (int k = 0; k < solution[v].numofstation; k++)
						{
							solution[v].sta[k] = -1;
						}
						for (int k = 0; k <= i + 1; k++)//���һ��·��
						{
							solution[v].sta[k] = path[k];
						}
						solution[v].numofstation = i + 2;
						break;
					}
					else
						continue;
				}
			}
			else if (j != y && visited[j] == 0) {
				FindRoad(map, j, y, i + 1);
			}
		}
	}
	visited[x] = 0;//ȡ�����
}

void MakeVMap()
{
	FILE* fp1 = fopen("G:\\User\\Desktop\\stationname.txt", "r");
	for(int i=0;i<197;i++)
		fscanf(fp1, "%s", &stationnames[i]);
	fclose(fp1);
	int x, y, z;
	FILE* fp2 = fopen("G:\\User\\Desktop\\edge.txt", "r");
	int j = 277;
	while(j--)
	{
		fscanf(fp2, "%d %d", &x, &y);
		map.edge[x-1][y-1] = 1;
		map.edge[y-1][x-1] = 1;
	}
	fclose(fp2);
	FILE* fp3 = fopen("G:\\User\\Desktop\\edge2.txt", "r");
	j = 277;
	while (j--)
	{
		fscanf(fp2, "%d %d %d", &x, &y, &z);
		edge[x - 1][y - 1].line = z;
		edge[y - 1][x - 1].line = z;
	}
	fclose(fp3);
	map.num_dot = 197;
	return;
}

void SetYongjidu0()
{
	for (int i = 0; i < 48; i++)
	{
		if (i >= 15 && i <= 17)
			quan0[1][i] = 0.8;
		else if (i>=33 && i<=36)
			quan0[1][i] = 0.75;
		else
			quan0[1][i] = 0.4;
	}
	for (int i = 0; i < 48; i++)
	{
		if (i >= 15 && i <= 17)
			quan0[3][i] = 0.8;
		else if (i >= 33 && i <= 36)
			quan0[3][i] = 0.75;
		else
			quan0[3][i] = 0.4;
	}
	for (int i = 0; i < 48; i++)
	{
		if (i >= 19 && i <= 29)
			quan0[8][i] = 0.65;
		else
			quan0[8][i] = 0.2;
	}
	for (int i = 0; i < 48; i++)
	{
		if (i >= 38 && i <= 43)
			quan0[6][i] = 0.65;
		else
			quan0[6][i] = 0.15;
	}
	for (int i = 0; i < 48; i++)
	{
		if (i >= 38 && i <= 43)
			quan0[7][i] = 0.65;
		else
			quan0[7][i] = 0.15;
	}
	for (int i = 0; i < 48; i++)
	{
		quan0[2][i] = 0.5;
		quan0[4][i] = 0.5;
	}
}

void SetYongjidu()
{
	system("cls");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("��        Welcome to take metro of Wuhan!          ��\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("�� 1.Use index setting                             ��\n");
	printf("�� 2.Creat new                                     ��\n");
	printf("�� 0.Back                                          ��\n");
	printf("��                                                 ��\n");
	printf("��                                                 ��\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	int op_crowd;
	int num_set;
	int xianluhao, shijianduan, kaishih, kaishimin, jieshuh, jieshumin;
	double yongjidu;
	scanf("%d", &op_crowd);
	switch (op_crowd)
	{
		case 1:
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 48; j++)
					quan[i][j] = quan0[i][j];
			FLAG = 0;
			break;
		case 2:
			printf("������Ҫ���õ���·����:\n");
			scanf("%d", &num_set);
			while (num_set--)
			{
				printf("��������·�ţ�\n");
				scanf("%d", &xianluhao);
				printf("������ʱ��θ�����\n");
				scanf("%d", &shijianduan);
				while (shijianduan--)
				{
					printf("������ʱ��κͶ�Ӧӵ���ȣ�\n");
					scanf("%d:%d %d:%d %lf", &kaishih, &kaishimin, &jieshuh, &jieshumin, &yongjidu);
					for (int i = kaishih * 2 + kaishimin / 30; i < jieshuh * 2 + jieshumin / 30; i++)
					{
						quan[xianluhao][i] = yongjidu;
					}
				}
			}
			FLAG += 1;
			break;
		case 0:
			MainPage();
			break;
			return;
	}
	printf("���óɹ���\n");
	system("pause");
	MainPage();
	return;
}

bool cmp(Solution a, Solution b)
{
	return a.numofstation < b.numofstation;
}

void Exit()
{
	printf("��лʹ�ñ�ϵͳ��\n");
	system("pause");
	exit(0);
}