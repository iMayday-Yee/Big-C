#pragma once
#include<stdio.h>

typedef struct Line
{
	int line_order;			//��·���
	int num_station;		//����·��վ����
	double length;			//����·�ܳ���
	double eachlen;			//ÿһ�εĳ���
	struct Station* start;	//ָ�����·��һ��վ��
}Line;

typedef struct Station
{
	char name[20];
	int view_flag;
	int station_order;		//n[i]��ʾ��վ����i+1�����ϵ�λ�����
	struct Station* pre;	//ָ�����·��һվ
	struct Station* next;	//ָ�����·��һվ
	int exline1;				//��վ����ex1����·��Ҳ����
	int exorder1;			//��վ����ex1����·�е�λ�����
	struct Station* equal1;	//ָ�򻻳���·1�и�վ��
	int exline2;				//��վ����ex2����·��Ҳ����
	int exorder2;			//��վ����ex2����·�е�λ�����
	struct Station* equal2;	//ָ�򻻳���·2�и�վ����һվ
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