#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"process.h"
struct bus_route *creat(FILE *fp);//创建链表并读入站点信息，并将信息存入station1.txt和station2.txt文件中 
void print(struct bus_route *head,char filename[]);//输出指定文件中的站点信息 
struct bus_route *insert(struct bus_route *head,char s[]);//向链表指定站点后插入新站点 
struct bus_route *del(struct bus_route *head,char s[]);//删除链表中指定站点 
struct bus_route *change(struct bus_route *head,char s[],char chg[]);//更改链表中指定站点名称 
void through(struct bus_route *head1,struct bus_route *head2,char begin[],char end[]);//判断起点与终点所在的线路,告知可否直达并供乘车方案,输出途径站点 
void up(struct bus_route *head,char filename[]);//重建（更新）文件内容，将处理后的链表内容输出（更新）到指定文件中 
void overthrough(char begin[],char end[],struct bus_route *head);//指定线路中起点到终点途经站点为正向则正向输出，为逆向则反向输出 
void advice(struct bus_route *head1,struct bus_route *head2,char begin[],char end[]);//不可直达时提供专程方案并输出途径站点 
int ord(char name[],struct bus_route *head);//返回某站点在所在线路中的站点序号 
struct bus_route
{
	char busstop[50];//站点名称（头节点则为车次）
	int order;//站点序号（头节点则为此线路站点总数）
	struct bus_route *next; 
};
int main()
{
	int select1,select2,select3;
	char mi[30]="777",shu[30];
	char s[50],chg[50];
	char filename[20];
	char filename1[20]="station1.txt";
	char filename2[20]="station2.txt";
	struct bus_route *head=NULL;
	FILE *fp,*fp2;
	if((fp=fopen(filename1, "w+"))==NULL)		
    {
    printf("cannot open file\n");
    exit(0);
    }
	if((fp2=fopen(filename2, "w+"))==NULL)		
    {
    printf("cannot open file2\n");
    exit(0);
    }
	printf("\n");
    printf("	                        -----------------------------------\n");
    printf("	                        *                                 *\n");
    printf("	                        *   公交站点管理与线路选择系统    *\n");
   	printf("	                        *                                 *\n");
   	printf("	                        -----------------------------------\n\n");		
	printf("首先请录入两条线路\n");	
	printf("******线路一:");struct bus_route *head1=creat(fp);
	printf("******线路二:");struct bus_route *head2=creat(fp2);	
	printf("未更改处理前:\n");
	printf("******线路一:");print(head1,filename1);
	printf("******线路二:");print(head2,filename2);
	printf("                                   --------1 站点管理系统--------\n");
	printf("                                   --------2 公交查询系统--------\n"); 
	printf("                                   --------0 退出------------\n"); 
	printf("请选择功能\n");
	while(1)
	{
	scanf("%d",&select1);
	if(select1==0)break;
	getchar();
	switch(select1)
	{
	case 0:break;
	case 1:
	printf("请输入管理员密码：");
	while(gets(shu)&&strcmp(mi,shu)!=0)
	{
	printf("密码错误,请重新输入:");	
	}
	printf("***********************************欢迎进入站点管理系统**************************************\n");
	printf("-------------------------输入1则为输入原站点名并输新站点名替换之功能-------------------------\n");	
	printf("-------------------------输入2则为插入节点前后的站点数量及各站点名称功能---------------------\n");
	printf("-------------------------输入3则为删除节点前后的各站点名称及数量功能-------------------------\n");
	printf("--------------------------------------输入4返回上一步----------------------------------------\n");	
	scanf("%d",&select2);
	if(select2!=4)
	{
	printf("管理第一条链请输1\n管理第二条链请输2\n");
	scanf("%d",&select3);
	getchar();
	}
	else 
	{
	break;	
	}			
	if(select3==1)
	{
		head=head1;
		strcpy(filename,filename1);
	}
	if(select3==2)
	{
		head=head2;
		strcpy(filename,filename2);
	}
	switch(select2)
	{
		case 1:
		printf("请输入原站点名："); 
		gets(s);
		printf("请输入更改后的站点名："); 
		gets(chg);
		head=change(head,s,chg);
		up(head,filename);
		printf("更改名称后:\n");
		print(head,filename); 
		printf("*结束*\n");
		break;
		
		case 2:
		printf("请输入要插入的站点的前一个站点名称：");
		gets(s); 
		head=insert(head,s);
		up(head,filename);
		printf("插入节点后:\n"); 
		print(head,filename); 	
		printf("*结束*\n");
		break;
		
		case 3:
		printf("请输入要删除的站点名称："); 
		gets(s); 
		head=del(head,s);
		up(head,filename);
		printf("删除节点后:\n"); 
		print(head,filename); 
		printf("*结束*\n"); 
		break;
	}break;	
	case 2:
	printf("***********************************欢迎进入公交查询系统**************************************\n");
	char begin[30],end[30];
	printf("输入起点:");
	gets(begin);
	printf("输入终点:");
	gets(end); 
	through(head1,head2,begin,end);
	break;
	}
	printf("                                   --------1 站点管理--------\n");
	printf("                                   --------2 公交查询--------\n"); 
	printf("                                   --------0 退出------------\n"); 
	printf("请选择功能\n");	
	}
}
void through(struct bus_route *head1,struct bus_route *head2,char begin[],char end[])
{
	int beg=0,en=0;
	int a=0,b=0,c=0,d=0;
	struct bus_route *p1=head1,*p2=head2;
	while(p1!=NULL)
	{
		if(strcmp(begin,p1->busstop)==0)
		{
			a=1;break;
		}
		p1=p1->next;
	}
	p1=head1;
	while(p1!=NULL)
	{
		if(strcmp(end,p1->busstop)==0)
		{
			b=1;break;
		}
		p1=p1->next;
	}
	while(p2!=NULL)
	{
		if(strcmp(begin,p2->busstop)==0)
		{
			c=1;break;
		}
		p2=p2->next;
	}
	p2=head2;
	while(p2!=NULL)
	{
		if(strcmp(end,p2->busstop)==0)
		{
			d=1;break;
		}
		p2=p2->next;
	}	
	p1=head1;
	p2=head2;
	if((a==1&&b==1)&&(c==1&&d==1))
	{
		printf("可直达,乘坐%s或%s\n",p1->busstop,p2->busstop);
		overthrough(begin,end,p1);
	}
	else if(a==1&&b==1)
	{
	printf("可直达,乘坐%s\n",p1->busstop);
	overthrough(begin,end,p1);
	}
	else if(c==1&&d==1)
	{
	printf("可直达,乘坐%s\n",p2->busstop);
	overthrough(begin,end,p2);
	}
	else
	{
	printf("不可直达\n");
	advice(head1,head2,begin,end);
	}
}
void advice(struct bus_route *head1,struct bus_route *head2,char begin[],char end[])
{
	char s[30]="济南大学",s1[50]={0},s2[50]={0};int a=0,b=0;	
	struct bus_route *p1=head1,*p2=head2;
	while(p1->next!=NULL)
	{
	p1=p1->next;
	if(strcmp(p1->busstop,begin)==0)
	{
	a=1;break;	
	}
	}
	strcpy(s1,p1->busstop);
	while(p2->next!=NULL)
	{
	p2=p2->next;
	if(strcmp(p2->busstop,begin)==0)
	{
	b=1;break;	
	}
	}
	strcpy(s2,p2->busstop);
	p1=head1;p2=head2;
	if(ord(begin,p1)<21&&ord(end,p2)<12)
	strcpy(s,"南辛庄");
	if(ord(begin,p2)<12&&ord(end,p1)<21)
	strcpy(s,"南辛庄");
	p1=head1;p2=head2;
	if(a==1)
	{
	printf("首先乘坐%s到达---%s\n",head1->busstop,s);
	overthrough(begin,s,p1);
	printf("再换乘%s到达---%s\n",head2->busstop,end);
	overthrough(s,end,p2);
	}	
	if(b==1)
	{
	printf("首先乘坐%s到达---%s\n",head2->busstop,s);
	overthrough(begin,s,p2);
	printf("再换乘%s到达---%s\n",head1->busstop,end);
	overthrough(s,end,p1);		
	}

}
int ord(char name[],struct bus_route *head)
{
	struct bus_route *p=head;
	while(strcmp(name,p->busstop)!=0&&p->next!=NULL)
	{
		p=p->next;
	}
	return p->order;
}
void overthrough(char begin[],char end[],struct bus_route *head)
{
	printf("途径站点为:********\n");
	struct bus_route *p1=head->next;
	struct bus_route *p2=head->next;
	int num1=0,num2=0;
	char str[30][30];
	int i=0;
	while(strcmp(p1->busstop,begin)!=0)
	{
	p1=p1->next;
	}
	num1=p1->order;
	while(strcmp(p2->busstop,end)!=0)
	{
	p2=p2->next;
	}
	num2=p2->order;
	if(num1<num2)
	{
	puts(begin);
	while(strcmp(p1->busstop,end)!=0)
	{
	p1=p1->next;
	puts(p1->busstop);
	}
	}
	if(num1>num2)
	{
	while(strcmp(p2->busstop,begin)!=0)
	{		
	p2=p2->next;
	sprintf(str[i],"%s",p2->busstop);
	i++;
	}
	i--;
	for(;i>=0;i--)
	puts(str[i]);
	puts(end);
	}
}
void up(struct bus_route *head,char filename[])
{
	FILE *fp;
	if ((fp=fopen(filename, "w+")) == NULL)		
    {
        printf("cannot open file\n");
        exit(0);
    }
    struct bus_route *p=head->next;
    int num=1;
    while(p!=NULL)
    {
    	p->order=num;
    	num++;
    	p=p->next;
	}
	struct bus_route *p1=head;
	fprintf(fp,"%d",p1->order);
	fputc(10,fp);
	fputs(p1->busstop,fp);
	p1=p1->next;
    while(p1!=NULL)
    {
	fputc(10,fp);
	fprintf(fp,"%d",p1->order);
	fputc(10,fp);
	fputs(p1->busstop,fp);		
	p1=p1->next;
	}
	fputc(10,fp);
	fclose(fp);			
}
struct bus_route *creat(FILE *fp)
{
	printf("请输入各个站点名称至以#终止:\n");
	struct bus_route *head=NULL,*p1,*p2;	
	p1=p2=(struct bus_route *)malloc(sizeof(struct bus_route));
	scanf("%d%s",&p1->order,p1->busstop);
	fprintf(fp,"%d",p1->order);
	fputc(10,fp);
	fputs(p1->busstop,fp);
	while(strcmp(p1->busstop,"#")!=0)
	{
		if(head==NULL)
		head=p1;
		else
		p2->next=p1;
		p2=p1;
		p1=(struct bus_route *)malloc(sizeof(struct bus_route));
		scanf("%d%s",&p1->order,p1->busstop);
		if(strcmp(p1->busstop,"#")!=0)
		{
			fputc(10,fp);
			fprintf(fp,"%d",p1->order);
			fputc(10,fp);
			fputs(p1->busstop,fp);	
		} 
	}
	fputc(10,fp);
	fclose(fp);
	p1->next=NULL;
	p2->next=NULL;
	free(p1);
	return head;
}
void print(struct bus_route *head,char filename[])
{
	char str[50];
	int i;
	FILE *fp;
	if ((fp=fopen(filename, "r")) == NULL)		
    {
        printf("cannot open file\n");
        exit(0);
    }
	struct bus_route *t=head;
	printf("                       ******车次：%s******\n",t->busstop);		
	t=t->next;													
    fgets(str,sizeof(str),fp);
	fgets(str,sizeof(str),fp);  
    while(fscanf(fp,"%d",&i)!=EOF)
    {
    printf("||");
    fgets(str,sizeof(str),fp); 	
	fgets(str,sizeof(str),fp);
    printf("(%d)%s",i,str);
	}
    fclose(fp);			
}
struct bus_route *change(struct bus_route *head,char s[],char chg[])
{
	struct bus_route *t=head;
	while(strcmp(t->busstop,s)!=0)
	{
		t=t->next;
	}
	strcpy(t->busstop,chg);
	return head;
} 
struct bus_route *insert(struct bus_route *head,char s[])
{
	
	struct bus_route *t=head,*pnew=(struct bus_route *)malloc(sizeof(struct bus_route));
	printf("请输入：");
	scanf("%s",pnew->busstop); 
	while(strcmp(t->busstop,s)!=0)
	{
		t=t->next;
	}
	pnew->next=t->next;
	t->next=pnew;
	return head;	
}
struct bus_route *del(struct bus_route *head,char s[])
{
	struct bus_route *t=head,*pre=head;
	while(strcmp(t->busstop,s)!=0)
	{
		pre=t;
		t=t->next;	
	}
	pre->next=t->next;
	free(t);
	return head;
}
