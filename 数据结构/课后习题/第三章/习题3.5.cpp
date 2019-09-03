/*
ϰ�� 3. 5 �жϵ������Ƿ�����
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
int order_down(node *head);
int order_up(node *head);

int main()
{
	int x = 0,y =0;
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n�������������ֵΪ��\n");
	display(head);
	if(order_down(head) || order_up(head))
		printf("�õ������������!\n");
	else
		printf("�õ������������!\n");
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

/***************************/
/****�ж������Ƿ�����******/
/**************************/
int order_up(node *head)
{
	node *pre = head,*p = head ->next;
	if(p == NULL) 
		return 1; //�ձ��������
	while(p != NULL)
	{
		if(p->info > pre->info)
			break;
		pre = p;
		p = p->next;
	}
	return (p == NULL);
}
int order_down(node *head)
{
	node *pre = head,*p = head ->next;
	if(p == NULL) 
		return 1; //�ձ��������
	while(p != NULL)
	{
		if(p->info < pre->info)
			break;
		pre = p;
		p = p->next;
	}
	return (p == NULL);
}
