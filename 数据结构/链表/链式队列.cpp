/*
��ʽ����
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

typedef struct{
	node *front,*rear; /*����������βָ��*/
}queue;



/**********************/
/*����һ���յ���ʽ����*/
/**********************/
queue *init()
{
	queue *qu;
	qu = (queue *)malloc(sizeof(queue));
	qu->front = NULL;
	qu->rear = NULL;
	return qu;
}


/**********************/
/*�ж���ʽ�����Ƿ�Ϊ��*/
/**********************/
int empty(queue qu)
{
	return (qu.front ? 0 : 1);
}

/****************************/
/*�����ʽ�����и����ڵ��ֵ*/
/****************************/
void display(queue *qu)
{
	node *p = qu->front;
	printf("\n");
	if(!p)
		printf("��ʽ�����ǿյ�!\n");
	while(p)
	{
		printf("%d-->",p->info);
		p = p->next;
	}
	printf("\n");
}

/*************************/
/*ȡ����ʽ���еĶ��׽��ֵ*/
/*************************/
int read(queue qu)
{
	if(!qu.front)
	{
		printf("��ʽ�����ǿյģ�");
		exit(1);
	}
	return (qu.front->info);
}


/***********************************/
/*����ʽ���е��в���һ��ֵΪx�Ľ��*/
/***********************************/
queue *insert(queue *qu,datatype x)
{
	node *p = (node *)malloc(sizeof(node));
	p->info = x;
	p->next = NULL;
	if(qu->front == NULL)
		/*��ǰ����Ϊ�գ��²���Ľ����Ϊ�����е�Ψһһ�����*/
		qu->front = qu->rear = p;
	else
	{
		qu->rear->next = p;/*��β����*/
		qu->rear = p;
	}
	return qu;
}

/**************************/
/*ɾ����ʽ�����еĶ��׽��*/
/*************************/
queue *dele(queue *qu)
{
	node *q;
	if(!qu->front)
	{
		printf("����Ϊ�գ��޷�ɾ����");
		return qu;
	}
	q = qu->front;/*qָ����׽��*/
	qu->front = q->next;/*����ָ��ָ����һ�����*/
	free(q);/*�ͷ�ԭ�����׽��ռ�*/
	if(qu->front == NULL)
		qu->rear = NULL;/*�����е�Ψһ��㱻ɾ���󣬶��б��*/
	return qu;

}

int main()
{
	int i,j = 0;
	queue *qu = init();
	printf("���������ݵĸ�����\n");
	scanf("%d",&j);
	for(i = 0;i < j;i ++)
	{
		int k = 0;
		printf("�������%d�����ݣ�\n",i + 1);
		scanf("%d",&k);
		qu = insert(qu,k); 
	}
	printf("�����е�����Ϊ��\n");
	display(qu);
}
