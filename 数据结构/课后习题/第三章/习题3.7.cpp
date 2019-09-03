
/*
���һ���㷨����һ���ڵ�ֵΪ��Ȼ���ĵ������ֳ�����������
ԭ���б���ֵΪż���Ľ�㣬��ֵΪ�����Ľ�㰴������ԭ���е�
��Դ������һ���µĵ����� 
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
//��ȡ����
node *separate(node *head1,node *head2);
//ʣ��ż���ľ�����
node *surplus(node *head);
/****��������ɾ��һ��ֵΪx�Ľ��******/
node *dele(node *head,datatype x);

int main()
{
	int x = 0,y =0;
	node *head,*p;
	node *head1;
	head = init();
	head1 = init();
	head = my_scanf(head);
	printf("\n�������������ֵΪ��\n");
	display(head);
	head1 = separate(head,head1);
	printf("\n��ȡ�����ڵ��������\n");
	display(head1);
	head = surplus(head);
	printf("\nʣ��ż���ľ�����\n");
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

/*******************/
/****��ȡ����******/
/******************/
node *separate(node *head1,node *head2)
{
	node *p = head1,*q = NULL,*m = NULL;
	if(p->next == NULL)
		printf("�����ǿյ�!\n");
	int a = 0;
	while(p)
	{
		if(p->info % 2 != 0)
		{
			q = (node *)malloc(sizeof(node));
			q->info = p->info;
			q->next = NULL;
			if(a == 0)
			{
				head2 = q;
				m = q;
				a = 1;
			}
			else
			{
				m->next = q;
				m = q;
			}
		}
		p = p->next;
	}
	return head2;
}

/**************************/
/****ʣ��ż���ľ�����******/
/**************************/
node *surplus(node *head)
{
	node *p = head,*pre = NULL;
	if(!head)
	{
		printf("�������ǿյģ�");
		return head;
	}
	pre = head;
	p = head->next;
	while(p)
	{
		if(pre == head && pre->info % 2 != 0)
			head = head->next;
		if(p->info % 2 != 0)
		{
			pre->next = p->next;
			p = pre->next; 
		}
		else
		{
			pre = p;
			p = p->next;
		}
	}
	return head;
}


/**************************************/
/****��������ɾ��һ��ֵΪx�Ľ��******/
/*************************************/

node *dele(node *head,datatype x)
{
	node *pre = NULL,*p;
	if(!head)
	{
		printf("�������ǿյģ�");
		return head;
	}
	p = head;
	//ָ��ָ�����ݴ��ڲ���û���ҵ����ϵ�����
	while(p && p->info != x)
	{
		pre = p;
		p = p->next;
	}
	if(p)
	{
		//ǰ����㲻���ڣ�����Ҫɾ����һ������
		if(!pre)
			head = head->next;
		else
			pre->next = p->next;
		free(p);
	}
	return head;
}
