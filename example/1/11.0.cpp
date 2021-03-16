#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"process.h"
struct bus_route *creat(FILE *fp);//������������վ����Ϣ��������Ϣ����station1.txt��station2.txt�ļ��� 
void print(struct bus_route *head,char filename[]);//���ָ���ļ��е�վ����Ϣ 
struct bus_route *insert(struct bus_route *head,char s[]);//������ָ��վ��������վ�� 
struct bus_route *del(struct bus_route *head,char s[]);//ɾ��������ָ��վ�� 
struct bus_route *change(struct bus_route *head,char s[],char chg[]);//����������ָ��վ������ 
void through(struct bus_route *head1,struct bus_route *head2,char begin[],char end[]);//�ж�������յ����ڵ���·,��֪�ɷ�ֱ�ﲢ���˳�����,���;��վ�� 
void up(struct bus_route *head,char filename[]);//�ؽ������£��ļ����ݣ�������������������������£���ָ���ļ��� 
void overthrough(char begin[],char end[],struct bus_route *head);//ָ����·����㵽�յ�;��վ��Ϊ���������������Ϊ����������� 
void advice(struct bus_route *head1,struct bus_route *head2,char begin[],char end[]);//����ֱ��ʱ�ṩר�̷��������;��վ�� 
int ord(char name[],struct bus_route *head);//����ĳվ����������·�е�վ����� 
struct bus_route
{
	char busstop[50];//վ�����ƣ�ͷ�ڵ���Ϊ���Σ�
	int order;//վ����ţ�ͷ�ڵ���Ϊ����·վ��������
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
    printf("	                        *   ����վ���������·ѡ��ϵͳ    *\n");
   	printf("	                        *                                 *\n");
   	printf("	                        -----------------------------------\n\n");		
	printf("������¼��������·\n");	
	printf("******��·һ:");struct bus_route *head1=creat(fp);
	printf("******��·��:");struct bus_route *head2=creat(fp2);	
	printf("δ���Ĵ���ǰ:\n");
	printf("******��·һ:");print(head1,filename1);
	printf("******��·��:");print(head2,filename2);
	printf("                                   --------1 վ�����ϵͳ--------\n");
	printf("                                   --------2 ������ѯϵͳ--------\n"); 
	printf("                                   --------0 �˳�------------\n"); 
	printf("��ѡ����\n");
	while(1)
	{
	scanf("%d",&select1);
	if(select1==0)break;
	getchar();
	switch(select1)
	{
	case 0:break;
	case 1:
	printf("���������Ա���룺");
	while(gets(shu)&&strcmp(mi,shu)!=0)
	{
	printf("�������,����������:");	
	}
	printf("***********************************��ӭ����վ�����ϵͳ**************************************\n");
	printf("-------------------------����1��Ϊ����ԭվ����������վ�����滻֮����-------------------------\n");	
	printf("-------------------------����2��Ϊ����ڵ�ǰ���վ����������վ�����ƹ���---------------------\n");
	printf("-------------------------����3��Ϊɾ���ڵ�ǰ��ĸ�վ�����Ƽ���������-------------------------\n");
	printf("--------------------------------------����4������һ��----------------------------------------\n");	
	scanf("%d",&select2);
	if(select2!=4)
	{
	printf("�����һ��������1\n����ڶ���������2\n");
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
		printf("������ԭվ������"); 
		gets(s);
		printf("��������ĺ��վ������"); 
		gets(chg);
		head=change(head,s,chg);
		up(head,filename);
		printf("�������ƺ�:\n");
		print(head,filename); 
		printf("*����*\n");
		break;
		
		case 2:
		printf("������Ҫ�����վ���ǰһ��վ�����ƣ�");
		gets(s); 
		head=insert(head,s);
		up(head,filename);
		printf("����ڵ��:\n"); 
		print(head,filename); 	
		printf("*����*\n");
		break;
		
		case 3:
		printf("������Ҫɾ����վ�����ƣ�"); 
		gets(s); 
		head=del(head,s);
		up(head,filename);
		printf("ɾ���ڵ��:\n"); 
		print(head,filename); 
		printf("*����*\n"); 
		break;
	}break;	
	case 2:
	printf("***********************************��ӭ���빫����ѯϵͳ**************************************\n");
	char begin[30],end[30];
	printf("�������:");
	gets(begin);
	printf("�����յ�:");
	gets(end); 
	through(head1,head2,begin,end);
	break;
	}
	printf("                                   --------1 վ�����--------\n");
	printf("                                   --------2 ������ѯ--------\n"); 
	printf("                                   --------0 �˳�------------\n"); 
	printf("��ѡ����\n");	
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
		printf("��ֱ��,����%s��%s\n",p1->busstop,p2->busstop);
		overthrough(begin,end,p1);
	}
	else if(a==1&&b==1)
	{
	printf("��ֱ��,����%s\n",p1->busstop);
	overthrough(begin,end,p1);
	}
	else if(c==1&&d==1)
	{
	printf("��ֱ��,����%s\n",p2->busstop);
	overthrough(begin,end,p2);
	}
	else
	{
	printf("����ֱ��\n");
	advice(head1,head2,begin,end);
	}
}
void advice(struct bus_route *head1,struct bus_route *head2,char begin[],char end[])
{
	char s[30]="���ϴ�ѧ",s1[50]={0},s2[50]={0};int a=0,b=0;	
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
	strcpy(s,"����ׯ");
	if(ord(begin,p2)<12&&ord(end,p1)<21)
	strcpy(s,"����ׯ");
	p1=head1;p2=head2;
	if(a==1)
	{
	printf("���ȳ���%s����---%s\n",head1->busstop,s);
	overthrough(begin,s,p1);
	printf("�ٻ���%s����---%s\n",head2->busstop,end);
	overthrough(s,end,p2);
	}	
	if(b==1)
	{
	printf("���ȳ���%s����---%s\n",head2->busstop,s);
	overthrough(begin,s,p2);
	printf("�ٻ���%s����---%s\n",head1->busstop,end);
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
	printf(";��վ��Ϊ:********\n");
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
	printf("���������վ����������#��ֹ:\n");
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
	printf("                       ******���Σ�%s******\n",t->busstop);		
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
	printf("�����룺");
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
