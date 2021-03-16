#pragma once
#include<stdio.h>

typedef struct Line
{
	int line_order;			//线路序号
	int num_station;		//该线路车站个数
	double length;			//该线路总长度
	double eachlen;			//每一段的长度
	struct Station* start;	//指向该线路第一个站点
}Line;

typedef struct Station
{
	char name[20];
	int view_flag;
	int station_order;		//n[i]表示该站点在i+1号线上的位置序号
	struct Station* pre;	//指向该线路上一站
	struct Station* next;	//指向该线路下一站
	int exline1;				//该站点在ex1号线路中也存在
	int exorder1;			//该站点在ex1号线路中的位置序号
	struct Station* equal1;	//指向换乘线路1中该站点
	int exline2;				//该站点在ex2号线路中也存在
	int exorder2;			//该站点在ex2号线路中的位置序号
	struct Station* equal2;	//指向换乘线路2中该站点上一站
}Station;


typedef struct Map
{
	int edge[200][200];
	int num_dot, num_edge;
}Map;

typedef struct Solution
{
	int numofstation;
	double length;
	double time;
	int price;
	double timeinmind;
	int endh;
	int endmin;
	int sta[51];
}Solution;

typedef struct Edge
{
	int line;
	double lenth;
	double quan;
}Edge;

typedef double Quan;