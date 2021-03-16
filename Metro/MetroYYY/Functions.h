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
Line line[MAX_NUM_LINE];//初始化MAX_NUM_LINE条线路
Line* line0, * line1;//指向目前操作的线路
Station* station0, * station1;//指向目前操作的站点
int sum_line;//线路总条数
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



//通过键盘键入线路数据
/*
输入格式：
线路总条数(sum_line)
#线路序号1(line0->line_order) 线路总长1(line0->length) 线路站点数量1(line0->num_station)
##站点序号11(station0->station_order) 站点名11(station0->name) 站点序号12 站点名12 站点序号13 站点名13 ...
#线路序号2(line0->line_order) 线路总长2(line0->length) 线路站点数量2(line0->num_station)
##站点序号21(station0->station_order) 站点名21(station0->name) 站点序号22 站点名22 站点序号23 站点名23 ...
...
*/
void InputByKey()
{
	cin >> sum_line;//输入线路总条数
	for (int i = 0; i < sum_line; i++)
	{
		line0 = &line[i];
		cin >> line0->line_order;
		cin >> line0->length;
		cin >> line0->num_station;
		line0->eachlen = line0->length / (line0->num_station - 1.0);
		line0->start = (Station*)malloc(sizeof(Station));
		station0 = line0->start;//指向目前操作的站点
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
	printf("成功构建地图！\n");
	system("pause");
	MainPage();
}

//通过文件读取线路数据
void InputByFile()
{
	char filename[50] = {0};
LOOP3:
	scanf("%s", filename);
	FILE *fp=fopen(filename, "r");
	while(fp==NULL)
	{
		printf("该文件不存在！\n");
		printf("请输入正确的文件路径：\n");
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
		station0 = line0->start;//指向目前操作的站点
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
	printf("成功构建地图！\n");
	system("pause");
	MainPage();
}

//由于不存在5号线，并且，数组line[]是从line[0]开始存放的1号线
//因此，为了使输入的线路序号指向对应的数组元素，定义了该函数
int LinenumToLinknum(int a)
{
	if (1 <= a && a <= 4)
		return a - 1;
	else if (6 <= a && a <= 8)
		return a - 2;
}

//上述几个函数输入线路图后生成了若干条双向链表
//但是在不同线路中的相同站还没有联系起来
//此函数功能为将相同的站点联系起来

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
	if (sum_line==0)//判断是否已经输入了线路信息
	{
		printf("请先输入线路图数据！\n");
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
		viewnum = LinenumToLinknum(viewnum);//将输入的线路号转化为line[i]中的i
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
	if (sum_line == 0)//判断是否已经输入了线路信息
	{
		printf("请先输入线路图数据！\n");
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
		viewnum = LinenumToLinknum(viewnum);//将输入的线路号转化为line[i]中的i
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
				//如果选择向后一站进行
				else if (op_step == 1)
				{
					if (station0->equal1==NULL)//如果这一站不是换乘站
					{
						if (station0->next == NULL)//如果没有下一站
						{
							printf("没有下一站了！\n");
						}
						else
						{
							station0 = station0->next;
							printf("您现在在 %s ！\n", station0->name);
						}
					}
					else//如果这一站是换乘站
					{
						if (station0->equal2 == NULL)//如果这一站只有一条换乘路线
						{
							printf("该站点可以换乘到%d号线，请输入换乘线路序号:(输入0选择不换乘)\n", station0->exline1);
							scanf("%d", &exchoose);
							if (exchoose == 0)
							{
								printf("您选择按原线路行驶，请继续选择线路行进方向：\n");
								station0 = station0;
							}
							else
							{
								printf("您已换乘到%d号线，请继续选择线路行进方向：\n", station0->exline1);
								station0 = station0->equal1;
							}
LOOP6:
							scanf("%d", &op_step);
							if (op_step == 1)
							{
								if (station0->next == NULL)
								{
									printf("没有下一站了！\n");
									goto LOOP6;
								}
								else
								{
									station0 = station0->next;
									printf("您现在在 %s ！\n", station0->name);
								}
							}
							else if (op_step == 2)
							{
								if (station0->pre == NULL)
								{
									printf("没有上一站了！\n");
									goto LOOP6;
								}
								station0 = station0->pre;
								printf("您现在在 %s ！\n", station0->name);
							}
						}
						else//如果这一站有两条换乘路线
						{
							printf("该站点可以换乘到%d号线和%d号线，请输入换乘线路序号:(输入0选择不换乘)\n", station0->exline1, station0->exline2);
							scanf("%d", &exchoose);
							if (exchoose == 0)
							{
								printf("您选择按原线路行驶，请继续选择线路行进方向：\n");
								station0 = station0;
							}
							else if (exchoose == station0->exline1)
							{
								printf("您已换乘到%d号线，请继续选择线路行进方向：\n", station0->exline1);
								station0 = station0->equal1;
							}
							else
							{
								printf("您已换乘到%d号线，请继续选择线路行进方向：\n", station0->exline2);
								station0 = station0->equal2;
							}
LOOP7:
							scanf("%d", &op_step);
							{
								if (op_step == 1)
								{
									if (station0->next == NULL)
									{
										printf("没有下一站了！\n");
										goto LOOP7;
									}
									else
									{
										station0 = station0->next;
										printf("您现在在 %s ！\n", station0->name);
									}
								}
								else if (op_step == 2)
								{
									if (station0->pre == NULL)
									{
										printf("没有上一站了！\n");
										goto LOOP6;
									}
									station0 = station0->pre;
									printf("您现在在 %s ！\n", station0->name);
								}
							}	
						}
					}
				}
				//如果选择向前一站进行
				else if (op_step == 2)
				{
					if (station0->equal1 == NULL)//如果这一站不是换乘站
					{
						if (station0->pre == NULL)//如果没有上一站
						{
							printf("没有上一站了！\n");
						}
						else
						{
							station0 = station0->pre;
							printf("您现在在 %s ！\n", station0->name);
						}
					}
					else//如果这一站是换乘站
					{
						if (station0->equal2 == NULL)//如果这一站只有一条换乘路线
						{
							printf("该站点可以换乘到%d号线，请输入换乘线路序号:(输入0选择不换乘)\n", station0->exline1);
							scanf("%d", &exchoose);
							if (exchoose == 0)
							{
								printf("您选择按原线路行驶，请继续选择线路行进方向：\n");
								station0 = station0;
							}
							else
							{
								printf("您已换乘到%d号线，请继续选择线路行进方向：\n", station0->exline1);
								station0 = station0->equal1;
							}
LOOP8:
							scanf("%d", &op_step);
							if (op_step == 1)
							{
								if (station0->next == NULL)
								{
									printf("没有下一站了！\n");
									goto LOOP6;
								}
								else
								{
									station0 = station0->next;
									printf("您现在在 %s ！\n", station0->name);
								}
							}
							else if (op_step == 2)
							{
								if (station0->pre == NULL)
								{
									printf("没有上一站了！\n");
									goto LOOP8;
								}
								station0 = station0->pre;
								printf("您现在在 %s ！\n", station0->name);
							}
						}
						else//如果这一站有两条换乘路线
						{
							printf("该站点可以换乘到%d号线和%d号线，请输入换乘线路序号:(输入0选择不换乘)\n", station0->exline1, station0->exline2);
							scanf("%d", &exchoose);
							if (exchoose == 0)
							{
								printf("您选择按原线路行驶，请继续选择线路行进方向：\n");
								station0 = station0;
							}
							else if (exchoose == station0->exline1)
							{
								printf("您已换乘到%d号线，请继续选择线路行进方向：\n", station0->exline1);
								station0 = station0->equal1;
							}
							else
							{
								printf("您已换乘到%d号线，请继续选择线路行进方向：\n", station0->exline2);
								station0 = station0->equal2;
							}
LOOP9:
							scanf("%d", &op_step);
							if (op_step == 1)
							{
								if (station0->next == NULL)
								{
									printf("没有下一站了！\n");
									goto LOOP9;
								}
								else
								{
									station0 = station0->next;
									printf("您现在在 %s ！\n", station0->name);
								}
							}
							else if (op_step == 2)
							{
								if (station0->pre == NULL)
								{
									printf("没有上一站了！\n");
									goto LOOP6;
								}
								station0 = station0->pre;
								printf("您现在在 %s ！\n", station0->name);
							}
						}
					}
				}
			}
		}
	}
}

//列车运行时刻表
void RunTime()
{
	if (sum_line == 0)
	{
		printf("请先输入线路图数据！\n");
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
		printf("请先输入线路图数据！\n");
		system("pause");
		MainPage();
		return;
	}
	start0 = Output_Start(line);
	end0 = Output_End(line);
	//printf("你选择了 %s 作为出发站点，%s 作为目的站点！\n", start0->name, end0->name);
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
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│ 1.Sort by time you will spend                   │\n");
	printf("│ 2.Sort by price                                 │\n");
	printf("│ 3.Sort by time in mind                          │\n");
	printf("│ 0.Exit                                          │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
	printf("你选择了 %s 作为出发站点，%s 作为目的站点！\n", start0->name, end0->name);
	printf("请输入当前时刻：\n");
	scanf_s("%d:%d", &starth, &startmin);
	Confuse();
	printf("请选择一种排序方案：\n");
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
	printf("推荐路线如下：\n");
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
			printf("#路线%d:\n", i + 1 - flag);
			for (int j = 0; j < solution[i].numofstation; j++)
			{
				if (j == solution[i].numofstation - 1)
					printf("%s\n", stationnames[abs(solution[i].sta[j])]);
				else
				{
					if (solution[i].sta[j] >= 0)
						printf("%s->", stationnames[solution[i].sta[j]]);
					else
						printf("%s（%d号线转%d号线）->", stationnames[abs(solution[i].sta[j])], edge[abs(solution[i].sta[j - 1])][abs(solution[i].sta[j])].line, edge[abs(solution[i].sta[j])][abs(solution[i].sta[j + 1])].line);
				}
			}
			printf("该线路共经过%d个站点\t总距离:%.2lfkm\n", solution[i].numofstation, solution[i].length);
			printf("实际花费时间：%.1lfmin\t实际到达时间:%d:%02d\n", solution[i].time, solution[i].endh, solution[i].endmin);
			printf("总票价:%d元\n", solution[i].price);

			printf("拥挤度加权时间:%.2lfmin\n", solution[i].timeinmind);
		}
	}
	if (flag >= 3)
		printf("当前时间不可到达!\n");
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
	visited[x] = 1;//标记该点
	int j;
	path[i] = x;//存入路径
	for (j = map.num_dot - 1; j >= 0; j--)//遍历邻接点
	{
		if (map.edge[x][j] != 0)
		{
			if (j == y)//满足到顶点v
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
						for (int k = 0; k <= i + 1; k++)//输出一组路径
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
	visited[x] = 0;//取消标记
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
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│ 1.Use index setting                             │\n");
	printf("│ 2.Creat new                                     │\n");
	printf("│ 0.Back                                          │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
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
			printf("请输入要设置的线路条数:\n");
			scanf("%d", &num_set);
			while (num_set--)
			{
				printf("请输入线路号：\n");
				scanf("%d", &xianluhao);
				printf("请输入时间段个数：\n");
				scanf("%d", &shijianduan);
				while (shijianduan--)
				{
					printf("请输入时间段和对应拥挤度：\n");
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
	printf("设置成功！\n");
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
	printf("感谢使用本系统！\n");
	system("pause");
	exit(0);
}