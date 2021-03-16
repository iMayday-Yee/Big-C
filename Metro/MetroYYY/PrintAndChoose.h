//提供制表符使用：
// ┌─────┐
// ├─────┤
// │     │
// └─────┘
#pragma once
#pragma warning(disable:28182)
#pragma warning(disable:4715)
#include<stdio.h>
#include<windows.h>
#include"MetroStruct.h"

int Output_Welcome()
{
	int op_Welcome;
	system("cls");
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│ 1.Input a map of metro                          │\n");
	printf("│ 2.View present map of metro                     │\n");
	printf("│ 3.View present map of metro by step             │\n");
	printf("│ 4.Runtime Table                                 │\n");
	printf("│ 5.Start your trip                               │\n");
	printf("│ 6.Set crowd                                     │\n");
	printf("│ 0.Exit                                          │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
LOOP1:
	printf("请选择一个功能：\n");
	scanf_s("%d", &op_Welcome);
	if (op_Welcome >= 0 && op_Welcome <= 6)
		return op_Welcome;
	else
	{
		printf("你选择了错误的选项！\n");
		goto LOOP1;
	}
}

int Output_InputMap()
{
	int op_InputMap;
	system("cls");
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│ 1.By keyboard                                   │\n");
	printf("│ 2.By file                                       │\n");
	printf("│ 0.Back                                          │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
LOOP2:
	printf("请选择一种方式输入线路数据：\n");
	scanf_s("%d", &op_InputMap);
	if (op_InputMap <= 2 && op_InputMap >= 0)
		return op_InputMap;
	else
	{
		printf("你选择了错误的选项！\n");
		goto LOOP2;
	}
}

void Output_InputByKey()
{
	system("cls");
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│ Inputing Map By Keyboard...                     │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
	printf("请用键盘输入路线数据：\n");
}

void Output_InputByFile()
{
	system("cls");
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│ Inputing Map By File...                         │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
	printf("请输入文件路径：\n");
}

int Output_View_LineChoose()
{
	int op_viewlinenum;
	system("cls");
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│ 1~4.Choose Line 1~4...                          │\n");
	printf("│ 6~8.Choose Line 6~8...                          │\n");
	printf("│ 0.Back                                          │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
LOOP4:
	printf("请输入你想查看的线路序号：\n");
	scanf_s("%d", &op_viewlinenum);
	if (0 <= op_viewlinenum && op_viewlinenum <= 8 && op_viewlinenum != 5)
		return op_viewlinenum;
	else
	{
		printf("你选择了错误的选项！\n");
		goto LOOP4;
	}
}

Station *Output_StepStart(int viewnum, Line* line)
{
	int startstation;
	Line* line0;
	Station* station0;
	line0 = &line[viewnum];
	printf("请选择一个站点作为出发站:(输入0以退出)\n");
LOOP5:
	scanf_s("%d", &startstation);
	if (startstation == 0)
	{
		return 0;
	}
	else if (startstation <= 0 || startstation > line0->num_station)
	{
		printf("你选择了错误的选项！\n");
		printf("请选择一个正确的站点作为出发站:(输入0以退出)\n");
		goto LOOP5;
	}
	station0 = line0->start;
	int p = startstation-1;
	while (p--)
	{
		station0 = station0->next;
	}
	system("cls");
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│ 1.Next Station                                  │\n");
	printf("│ 2.Last Station                                  │\n");
	printf("│ 0.Exit                                          │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
	printf("你选择了 %s 作为出发站！\n", station0->name);
	return station0;
}

void Output_Runtime(Line* line)
{
	system("cls");
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│                Runtime Table                    │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
	int runtimehour, runtimemin, runtimedert, nowtimehour, nowtimemin, nowtime, linenow, stationnow, tingkaotime, starttonow;
	printf("请输入列车开始运行时间(如8:30)：\n");
	scanf_s("%d:%d", &runtimehour, &runtimemin);
	printf("请输入两班列车之间的时间间隔(min)：\n");
	scanf_s("%d", &runtimedert);
	printf("请输入列车停靠时间(min)：\n");
	scanf_s("%d", &tingkaotime);
	printf("请输入当前时间(如10:30)：\n");
	scanf_s("%d:%d", &nowtimehour, &nowtimemin);
	printf("请输入你要查询的站点所在线路：\n");
	scanf_s("%d", &linenow);
	if (1 <= linenow && linenow <= 4)
		linenow = linenow - 1;
	else if (6 <= linenow && linenow <= 8)
		linenow = linenow - 2;
	Line* rtline = &line[linenow];
	Station* rtstation = rtline->start;
	while (rtstation != NULL)
	{
		printf("%d %s\n", rtstation->station_order, rtstation->name);
		rtstation = rtstation->next;
	}
	printf("请输入你要查询的站点序号:\n");
	scanf_s("%d", &stationnow);
	starttonow = 60 * (nowtimehour - runtimehour) + (nowtimemin - runtimemin) - stationnow * runtimedert;
	nowtime = nowtimehour * 60 + nowtimemin;
	int waittime =starttonow % runtimedert;
	int startoutputtime[6];
	printf("%2d:%02d左右该站点列车运行时刻表为：\n", nowtimehour, nowtimemin);
	for (int i = 0; i <= 5; i++)
	{
		startoutputtime[i] = nowtime -  waittime + (i - 2) * runtimedert;
		printf("%2d:%02d到站\t", startoutputtime[i] / 60, startoutputtime[i] % 60);
		printf("%2d:%02d离站\n", (startoutputtime[i]+tingkaotime) / 60, (startoutputtime[i] + tingkaotime) % 60);
	}
	printf("......\n");
	system("pause");
	return;
}


Station* Output_Start(Line* line)
{
	int startlinenum, startstationnum;
	Station* start;
	system("cls");
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│             Start your trip now!                │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
	//选择出发站
	printf("请输入出发站点所在线路：\n");
	scanf_s("%d", &startlinenum);
	if (1 <= startlinenum && startlinenum <= 4)
		startlinenum = startlinenum - 1;
	else if (6 <= startlinenum && startlinenum <= 8)
		startlinenum = startlinenum - 2;
	Line* startline = &line[startlinenum];
	Station* startstation = startline->start;
	while (startstation != NULL)
	{
		printf("%d %s\n", startstation->station_order, startstation->name);
		startstation = startstation->next;
	}
	printf("请输入你要选择出发的站点序号:\n");
	scanf_s("%d", &startstationnum);
	int k1 = startstationnum;
	start = startline->start;
	while (--k1)
		start = start->next;
	return start;
}

Station* Output_End(Line* line)
{
	int endlinenum, endstationnum;
	Station* end;
	//选择终点站
	printf("请输入目的站点所在线路：\n");
	scanf_s("%d", &endlinenum);
	if (1 <= endlinenum && endlinenum <= 4)
		endlinenum = endlinenum - 1;
	else if (6 <= endlinenum && endlinenum <= 8)
		endlinenum = endlinenum - 2;
	Line* endline = &line[endlinenum];
	Station* endstation = endline->start;
	while (endstation != NULL)
	{
		printf("%d %s\n", endstation->station_order, endstation->name);
		endstation = endstation->next;
	}
	printf("请输入你要选择出发的站点序号:\n");
	scanf_s("%d", &endstationnum);
	int k2 = endstationnum;
	end = endline->start;
	while (--k2)
		end = end->next;
	//输出选择情况
	system("cls");
	printf("┌─────────────────────────────────────────────────┐\n");
	printf("│        Welcome to take metro of Wuhan!          │\n");
	printf("├─────────────────────────────────────────────────┤\n");
	printf("│             Start your trip now!                │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("│                                                 │\n");
	printf("└─────────────────────────────────────────────────┘\n");
	return end;
}