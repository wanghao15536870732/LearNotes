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

//����һ���յĴ���ͷ�ڵ�ĵ�����
node *init();
//�������ͷ�ڵ�ĵ������и����ڵ��ֵ
void display(node *head);
//�ڴ���ͷ�ڵ�ĵ������в��ҵ�i���ڵ�Ĵ�ŵ�ַ
node *find(node *head,int i);
//����ͷ�ڵ�ĵ������i���������ֵΪx���½��
node *insert(node *head,datatype x,int i);
//����ͷ�ڵ�ĵ�������ɾ��һ��ֵΪx�Ľ��
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
		p->next = NULL;
		if(a == 1)
		{
			head = p;
			q = p;
		}
		else
		{
			p->info = data;
			q->next = p;
			q = p;
		}
	}
	return head;
}

/**************************************/
/****����һ���յĴ�ͷ�ڵ�ĵ�����******/
/*************************************/
node *init()
{
	node *head;
	head = (node *) malloc (sizeof(node));
	head->next = NULL;
	return head;
}

/**********************************************/
/****�������ͷ�ڵ�ĵ������и����ڵ��ֵ******/
/**********************************************/
void display(node *head)
{
	node *p;
	//�ӵ�һ��ʵ�ʵĽ�㿪ʼ
	p = head->next;
	if(!p)
		printf("\n��ͷ�ڵ�ĵ������ǿյģ�");
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

/*********************************************************/
/****�ڴ���ͷ���ĵ������в��ҵ�i���ڵ�Ĵ�ŵ�ַ******/
/*********************************************************/
node *find(node *head,int i)
{
	int j = 0;
	node *p = head;
	if(i < 0)
	{
		printf("\n����ͷ���ĵ������в����ڵ�%d����㣡",i);
		return NULL;
	}
	else if(i == 0)  /*��ʱpָ�����ͷ���*/
		return p;
	//û�в����겢��û���ҵ�
	while(p && i != j)
	{
		p = p->next;
		j ++;
	}
	return p;
}



/**********************************************************/
/****�ڴ���ͷ�ڵ�ĵ������i���������ֵΪx���½��******/
/**********************************************************/
node *insert(node *head,datatype x,int i)
{
	node *p,*q;
	//���Ҵ���ͷ�ڵ�ĵ������еĵ�i�����
	q = find(head,i); /*���i = 0����ʾ�½�������ͷ�ڵ�֮��*/
	//û���ҵ�
	if(!q)
	{
		printf("\n����ͷ���ĵ������в����ڵĵ�%d����㣡���ܲ���%d!",i,x);
		return head;
	}
	p = (node *)malloc(sizeof(node));
	p->info = x;
	p->next = q->next;
	//�� i = 0ʱ������qָ�����ͷ��㣬�����ȼ���head->next = p;
	q->next = p;
	return head;
}


/***************************************************/
/****�ڴ���ͷ���ĵ�������ɾ��һ��ֵΪx�Ľ��******/
/***************************************************/

node *dele(node *head,datatype x)
{
	//��preָ��ͷ���
	node *pre = head,*q;
	//q�Ӵ���ͷ���ĵ�һ��ʵ�ʵĽ�㿪ʼ��ֵΪ x �Ľ��
	q = head->next; 
	while(q && q->info != x)
	{
		pre = q;
		q = q->next;
	}
	if(q)
	{
		//ɾ�����
		pre->next = q->next;
		free(q);//�ͷſռ�
	}
	return head;
}

