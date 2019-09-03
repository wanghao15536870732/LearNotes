/*
��ʽջ
*/
#include "stdio.h"
#include "stdlib.h"

/*
��ʽջ��ͷ�ļ����뵥��������
*/
typedef int datatype;
typedef struct link_node{
	datatype info;
	struct link_node *next;
}node;



/********************/
/*����һ���յ���ʽջ*/
/********************/
node *init()
{
	return NULL;
}

/********************/
/*�ж���ʽջ�Ƿ�Ϊ��*/
/********************/
int empty(node *top)
{
	return (top ? 0 : 1);
}

/************************/
/*��ȡ��ʽջ��ջ�����ֵ*/
/************************/
datatype read(node *top)
{
	if(! top)
	{
		printf("\n��ʽջ�ǿյģ�");
		exit(1);
	}
	return (top->info);
}

/**************************/
/*�����ʽջ�и����ڵ��ֵ*/
/**************************/
void display(node *top)
{
	node *p = top;
	printf("\n");
	if(!p)
		printf("��ʽջ�ǿյģ�");
	while(p)
	{
		printf("%3d-->",p->info);
		p = p->next;
	}
	printf("\n");
}

/*************************/
/*����ʽջ����ֵΪx�Ľ��*/
/*************************/
node *push(node *top,datatype x)
{
	node *p = (node *)malloc(sizeof(node));
	p->info = x;
	p->next = top;
	top = p;
	return top;
}


/**********************/
/*ɾ����ʽջ��ջ�����*/
/**********************/
node *pop(node *top)
{
	node *q;
	if(!top)
	{
		printf("\n��ʽջʱ�յ�!");
		return NULL;
	}
	q =top;
	top = top->next;
	free(q);
	return top;
}

int main()
{
	int i,j = 0;
	node *head = init();
	printf("������ѧ���ĸ���:\n");
	scanf("%d",&j);
	for(i = 0;i < j;i ++)
	{
		int p = 0;
		printf("�������%d��ֵ��\n",i + 1);
		scanf("%d",&p);
		head = push(head,p);
	}
	printf("��ʽջ������Ϊ:\n");
	display(head);
}
