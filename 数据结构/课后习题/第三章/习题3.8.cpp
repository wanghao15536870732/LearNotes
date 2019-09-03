/*
ϰ�� 3. 8 ��һ������ĵ�����ɾ������ֵ���� x �������� y �Ľ��
*/ 

#include "stdio.h"
#include "stdlib.h"

/**************************/
/*****�������ͷ�ļ�*******/
/**************************/
typedef int datatype;
typedef struct link_node{
	datatype info;
	struct link_node *next;
}node;

//����һ���յĵ�����
node *init();
//����������и����ڵ��ֵ
void display(node *head);
//�������в��ҵ�i���ڵ�Ĵ�ŵ�ַ
//�Զ����������ݺ��� 
node *my_scanf(node *head);
//��������ɾ��һ��ֵΪx�Ľ��
node *dele(node *head,datatype x);
//��������ɾ������ֵ����x��������y�Ľ��
node *dele_more(node *head,int x,int y);
node *find(node *head,int i);

int main()
{
	int x = 0,y =0;
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n�������������ֵΪ��\n");
	display(head);
	printf("������Ҫɾ����ֵ�ķ�Χ��\n");
	scanf("%d%d",&x,&y);
	head = dele_more(head,x,y);
	printf("ɾ��֮�������\n");
	display(head);
	return 0;
}

//�Զ����������ݺ��� 
node *my_scanf(node *head)
{
	node *p = NULL,*q = NULL;
	int n,a;
	printf("���������ݵĸ�����\n");
	scanf("%d",&n);
	for(int a = 1;a <= n;a ++)
	{
		int data = 0; 
		scanf("%d",&data);
		p = (node *)malloc(sizeof(node));
		p->info = data;
		p->next = NULL;
		if(a == 1)
		{
			head = p;
			q = p;
		}
		else
		{
			q->next = p;
			q = p;
		}
	}
	return head;
}

/****************************/
/****����һ���յĵ�����******/
/****************************/
node *init()
{
	return NULL;
}

/**********************************/
/****����������и����ڵ��ֵ******/
/**********************************/
void display(node *head)
{
	node *p;
	p = head;
	if(!p)
		printf("\n�����ǿյģ�");
	else
	{
		while(p)
		{
			printf("%5d",p->info);
			p = p->next;
		}
	}
	printf("\n");
}

node *find(node *head,int i)
{
	node *p = head;
	while(p && p->info != i)
		p = p->next;
	return p;
}

/************************************************/
/****��������ɾ������ֵ����x��������y�Ľ��******/
/************************************************/
node *dele_more(node *head,int x,int y)
{
	int i = 0;
	node *p1 = NULL,*p2 = NULL;
	p1 = find(head,x);
	p2 = find(head,y);
	p1->next = p2->next;
	return head;
}


