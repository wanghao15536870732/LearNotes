/*
ϰ�� 3. 6 ���õ�����ԭ���Ľ��ռ���תһ��������
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
//���õ�����ԭ���Ľڵ�ռ�ռ���תһ��������
node *reverse(node *head);
int main()
{
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n����������ڵ��ֵΪ��\n");
	display(head);
	printf("\n��ֵ��ת��ĵ�����\n");
	head = reverse(head);
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

/****************************************************/
/****���õ�����ԭ���Ľڵ�ռ�ռ���תһ��������******/
/****************************************************/
node *reverse(node *head)
{
	node *p = head,*q;
	head = NULL;
	while(p)
	{
		q = p;
		p = p->next;
		q->next = head;
		head = q;
	}
	return head;
}

