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

//����һ���յ�ѭ��������
node *init();
//���ѭ���������и����ڵ��ֵ
void display(node *head);
//��ѭ���������в��ҵ�i���ڵ�Ĵ�ŵ�ַ
node *find(node *head,int i);
//��ѭ���������i���������ֵΪx���½��
node *insert(node *head,datatype x,int i);
//��ѭ����������ɾ��һ��ֵΪx�Ľ��
node *dele(node *head,datatype x);
//���ѭ������������һ�����Ĵ����ַ
node *rear(node *head);
//�Զ����������ݺ��� 
node *my_scanf(node *head);
//��һ����ͨ����ת����ѭ��������
node *change(node *head);

int main()
{
	int i = 0,j = 0;
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n����������ڵ��ֵΪ��\n");
	head = change(head);
	display(head);
	printf("\n������Ҫɾ���Ľڵ���ֵ:\n");
	scanf("%d",&i);
	head = dele(head,i);
	printf("\nɾ�������ֵΪ %d �Ľ��������\n",i); 
	display(head);
	printf("\n������Ҫ����Ľ��λ���Լ���ֵ��\n");
	scanf("%d%d",&i,&j);
	insert(head,j,i); 
	printf("\n����ֵ %d ���뵽����� %d λ�������\n",j,i);
	display(head);
	return 0;
}



/*******************************/
/****����һ���յ�ѭ��������*****/
/*******************************/
node *init()
{
	return NULL;
}

//�Զ����������ݺ��� 
node *my_scanf(node *head)
{
	node *p = NULL,*q = NULL;
	int n,a;
	printf("���������ݵĸ�����\n");
	scanf("%d",&n);
	for(int a = 0;a < n;a ++)
	{
		int data = 0; 
		scanf("%d",&data);
		p = (node *)malloc(sizeof(node));
		p->info = data;
		p->next = NULL;
		if(a == 0)
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


/***********************************************/
/****���ѭ������������һ�����Ĵ����ַ******/
/***********************************************/
node *rear(node *head)
{
	node *p;
	//ѭ��������Ϊ��
	if(!head)
		p = NULL;
	else
	{
		//�ӵ�һ����㿪ʼ
		p = head;
		//û�е������һ�����
		while(p->next != head)
			p = p->next; //�������
	}
	return p;
}

/*************************************/
/****���ѭ���������и����ڵ��ֵ******/
/*************************************/
void display(node *head)
{
	node *p;
	if(!head)
		printf("\nѭ���������ǿյ�");
	else
	{
		//�������ĵ�һ������
		printf("%5d",head->info);
		p = head->next;//ָ����һ�����
		while(p != head) //û�лص���һ�����
		{
			printf("%5d",p->info);
			p = p->next;
		}
	}
	printf("\n"); 
}

/**********************************************/
/***��ѭ���������в���ֵΪx�Ľڵ�Ĵ�ŵ�ַ****/
/*********************************************/
node *find(node *head,int x)
{
	//����һ��ֵΪx�Ľ��
	node *q;
	//ѭ���������ǿյ�
	if(!head)
	{
		printf("\nѭ���������ǿյģ��޷��ҵ�ָ���Ľ�㣡");
		return NULL;
	}
	q = head;
	//��qָ��ѭ��������ĵ�һ����㣬׼����ʼ��ѯ
	while(q->next != head && q->info != x)
		q = q->next;
	if(q->info == x)
		return q;
	else
		return NULL;
}



/**********************************************************/
/****��ѭ���������i���������ֵΪx���½��******/
/**********************************************************/
node *insert(node *head,datatype x,int i)
{
	//i = 0ʱ����ʾ��ֵΪx��ϵ�G�����뵽ѭ��������ĵ�һ�����
	node *p,*q,*myrear;
	int j;
	p = (node *)malloc(sizeof(node));
	//�����½���ֵ
	p->info = x;
	if(i < 0)
	{
		printf("\n�޷�����ָ���Ĳ���λ�ã�");
		free(p);
		return head;
	}
	//������ѭ���������ǿյģ�������ָ�����Լ�
	if(i == 0 && !head)
	{
		p->next = p;
		head = p;
		return head;
	}
	//��ѭ��������ĵ�һ��λ�ò���
	if(i == 0 && head)
	{
		//�ҵ�ѭ������������һ�����
		myrear = rear(head);
		p->next = head;
		myrear->next = p;
		return head;
	}
	if(i > 0 && !head)
	{
		printf("\n�޷��ҵ�ָ���Ĳ���λ�ã�");
		free(p);
		return head;
	}
	//�����λ�ò��ǵ�һ��
	if(i > 0 && head)
	{
		//��ѭ���������ͷ��ʼ����
		q = head;
		//������ʼ
		j = 1;
		//û���ҵ���Ӧ�����ݲ���û���ҵ����һ��
		while(i != j && q->next != head)
		{
			q = q->next;
			j ++;
		}
		//�Ҳ���ָ�������λ��
		if(i != j) 
		{
			printf("\n���в����ڵ�%d����㣬�޷����в��������\n");
			free(p);
			return head;
		}
		else
		{
			p->next = q->next;
			q->next = p;
			return head;
		}
	}
}


/***************************************************/
/****��ѭ����������ɾ��һ��ֵΪx�Ľ��******/
/***************************************************/

node *dele(node *head,datatype x)
{
	//q���ڲ���ֵΪx�Ľ�㣬preָ�� q ��ǰ�����
	node *pre = NULL,*q;
	if(!head)
	{
		printf("\nѭ��������Ϊ�գ��޷�����ɾ��������\n");
		return head;
	}
	//�ӵ�һ����㿪ʼ����
	q = head;
	//û���ұ���û���ҵ�
	while(q->next != head && q->info != x)
	{
		pre = q;
		q = q->next;
	}
	//����������û���ҵ�
	if(q->info != x)
		printf("û���ҵ�ֵΪ%d�Ľ�㣡",x);
	else 
	{
		if(q != head)
		{
			pre->next = q->next;
			free(q);
		}
		else
		{
			if(head->next == head)
			{
				free(q);
				head = NULL;
			}
			else
			{
				pre = head->next;
				//���� q ��ǰ���ڵ�λ��
				while(pre->next != q)
					pre = pre->next;
				head = head->next;
				pre->next = head;
				free(q);
			}
		}
	}
	return head;
}

/******************************************/
/*****��һ����ͨ����ת����ѭ��������*******/
/*******************************************/
node *change(node *head)
{
	node *p = head;
	while(p->next != NULL)
		p = p->next;
	p->next = head; 
	return head;
} 















