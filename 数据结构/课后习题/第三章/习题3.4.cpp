/*
ϰ�� 3. 4 ��һ����������ֵΪy�Ľ��ǰ�����һ��ֵΪx�Ľ�㣬
��ʹֵΪ x ���½���ΪֵΪ y �Ľ���ǰ�����
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
//��ֵΪy�Ľ��ǰ����һ��ֵΪx�Ľ��
node *front_insert(node *head,int y,int x);
//�������в���ֵΪx��ǰ�����
node *find(node *head,int x);
int main()
{
	int x = 0,y =0;
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n�������������ֵΪ��\n");
	display(head);
	printf("������Ҫǰ��Ľ������ݣ�\n");
	scanf("%d%d",&y,&x);
	head = front_insert(head,y,x);
	printf("���������ݣ�\n");
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

/****************************************/
/****�������в���ֵΪx��ǰ�����******/
/***************************************/
node *find(node *head,int x)
{
	node *p = head,*pre = head;
	while(p && p->info != x)
		p = p->next;
	//Ѱ��q��ǰ�����
	while(pre->next != p && p->info != x)
		pre = pre->next;
	return pre;
}

/********************************************/
/****��ֵΪy�Ľ��ǰ����һ��ֵΪx�Ľ��******/
/********************************************/
node *front_insert(node *head,int y,int x)
{
	node *p = NULL,*q = NULL;
	q = find(head,y);
	if(!q)
		printf("\n�Ҳ���ֵΪ%d�Ľ�㣬����ǰ��%d!",y,x);
	else
	{
		p = (node *)malloc(sizeof(node));
		p->info = x;
		//����ǵ�һ����㣬���뵽��һ�����ǰ��
		if(head->info == y)
		{
			p->next = head;
			head = p;
		}
		else
		{
			p->next = q->next;
			q->next = p;
		}
	}
	return head;
}


