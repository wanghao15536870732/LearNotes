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
node *find(node *head,int i);
//�������в���ֵΪi�Ľڵ�Ĵ�ŵ�ַ
node *findi(node *head,int i);
//�����i���������ֵΪx���½��
node *insert(node *head,datatype x,int i);
//��������ɾ��һ��ֵΪx�Ľ��
node *dele(node *head,datatype x);
//�Զ����������ݺ��� 
node *my_scanf(node *head);

int main()
{
	int i = 0,j = 0;
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n����������ڵ��ֵΪ��\n");
	display(head);
	printf("\n������Ҫɾ���Ľڵ���ֵ:\n");
	scanf("%d",&i);
	head = dele(head,i);
	printf("\nɾ�������ֵΪ%d�Ľ��������\n",i); 
	display(head);
	printf("\n������Ҫ����Ľ��λ���Լ���ֵ��\n");
	scanf("%d%d",&i,&j);
	insert(head,j,i); 
	printf("\n����ֵ%d���뵽�����%dλ�������\n",j,i);
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

/*********************************************/
/****�������в��ҵ�i���ڵ�Ĵ�ŵ�ַ******/
/*********************************************/
node *find(node *head,int i)
{
	int j = 1;
	node *p = head;
	if(i < 1)
		return NULL;
	while(p && i != j)
	{
		p = p->next;
		j ++;
	}
	return p;
}


/*********************************************/
/****�������в���ֵΪi�Ľڵ�Ĵ�ŵ�ַ******/
/*********************************************/
node *findi(node *head,int i)
{
	node *p = head;
	while(p && p->info != i)
		p = p->next;
	return p;
}

/********************************************/
/****�������i���������ֵΪx���½��******/
/********************************************/
node *insert(node *head,datatype x,int i)
{
	node *p,*q;
	//���ҵ�i�����
	q = find(head,i);
	if(!q && i != 0)
		printf("\n�Ҳ�����%d����㣬���ܲ���%d!",i,x);
	else
	{
		//Ϊp����һ���ռ�
		p = (node *)malloc(sizeof(node));
		//�����½ڵ������
		p->info = x;
		//�������Ľ���ǵ�����ĵ�һ�����
		if(i == 0)
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
