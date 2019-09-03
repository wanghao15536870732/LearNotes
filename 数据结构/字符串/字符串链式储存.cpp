# include "stdio.h"
# include "stdlib.h"
//��ʽ����ͷ�ļ�
typedef struct node
{
	char data;
	struct node *next;
}linkstrnode;

//��ʽ���Ĵ���
linkstrnode *strcreate(linkstrnode *S)
{
	char ch;
	linkstrnode *p,*r = NULL;
	S = NULL;
	while((ch = getchar()) != '\n')
	{
		p = (linkstrnode *)malloc(sizeof(linkstrnode));
		p->data = ch;
		if(S == NULL)
			S = p;
		else 
			r->next = p;
		r = p;
	}
	if(r != NULL)
		r->next = NULL;
	return S;
}

//�ַ�����������
linkstrnode *strinsert(linkstrnode *s,int i,linkstrnode *T)
{
	int k = 1;
	linkstrnode *p = s,*q = NULL;
	while(p && k < i - 1)  /*��p����S�е�i - 1��Ԫ�ص�λ��*/
	{
		p = p->next;
		k ++;
	}
	if(!p)
		printf("error!\n"); /*��i - 1��Ԫ�ز�����*/
	else
	{
		q = T;
		while(q && q->next)  /*��q����T�����һ��Ԫ�ص�λ��*/
			q = q->next;
		q->next = p->next;  /*��T���ӵ�S�еĵ�i��λ����*/
		p->next = T;
	}
	return s;
}

//��ʽ����ɾ��
linkstrnode *strdelete(linkstrnode *S,int i,int len)
{
	int k = 1;
	linkstrnode *p = S,*q = NULL,*r = NULL; 
	//��p����s�ĵ�i��Ԫ�أ�qʼ�ո���p��ǰ��
	while(p && k < i)
	{
		q = p;   
		p = p->next;
		k ++;
	}
	//S�ĵ�i��Ԫ�ز����ڣ������
	if(!p)
		printf("error!\n");
	else
	{
		k = 1;
		//p�ӵ�i��Ԫ�ؿ�ʼ���ҳ���Ϊlen�ִ������Ԫ��
		while(k < len && p)
		{
			p = p->next;
			k ++;
		}
		if(!p)
			printf("error2\n");
		else
		{
			//��ɾ�����ִ�λ��s����ǰ��
			if(!q)
			{
				r = S;
				S = p->next;
			}
			//��ɾ�����ִ�λ��s���м����������
			else
			{
				r = q->next;
				q->next = p->next;
			}
			p->next = NULL;
			//���ձ�ɾ�����ִ��Ŀռ�
			while(r != NULL)
			{
				p = r;
				r = r->next;
				free(p);
			}
		}
	}
	return S;
}

void strcompare(linkstrnode *st1,linkstrnode *st2)
{
	int i = 0;
	if(st1 && st2 && st1->data == st2->data)
	{
		st1 = st1->next;
		st2 = st2->next;
	}
	if((st1 && !st2) && (st1 && st2 && st1->data > st2->data) )
		printf("��һ���ַ������ڵڶ����ַ���!\n");
	else
		printf("�ڶ����ַ������ڵ�һ���ַ���!\n");
}

//�ַ�������
linkstrnode *strconcat(linkstrnode *s1,linkstrnode *s2)
{
	linkstrnode *p = NULL,*st = s1;;
	if(!s1)
	{
		s1 = s2;
		return NULL;
	}
	else
		if(s2)
		{
			p = s1;
			while(p->next)
				p = p->next;
			p->next = s2;
		}
	return st;
}

//���ִ�������
linkstrnode *substring(linkstrnode *S,int i,int len)
{
	int k = 1;
	linkstrnode *p = S,*q = NULL,*r = NULL,*t = NULL;
	linkstrnode *s = NULL;
	//��p����s�еĵ�i���ַ���
	while(p && k < i)
	{
		p = p->next;
		k ++;
	}
	if(!p)
	{
		printf("error1\n");
		return NULL;
	}
	//����S�еĵ�i���ַ������ڵ����
	else
	{
		r = (linkstrnode *)malloc(sizeof(linkstrnode));
		r->data = p->data;
		r->next = NULL;
		k = 1;
		q = r; //��qʼ��ָ���Ӵ������һ���ַ�����λ��
		while(p->next && k < len) //ȡ����Ϊlen���ִ�
		{
			p = p->next;
			k ++;
			t = (linkstrnode *) malloc (sizeof(linkstrnode));
			t->data = p->data;
			q->next = t;
			q = t;
		}
		if(k < len)
		{
			printf("error2\n");
			return NULL;
		}
		//�����Ӵ���β��
		else
		{
			q->next = NULL;
			return r;  
		}
	}
}

void display(linkstrnode *s)
{
	linkstrnode *p=s;
	while(p)
	{
		printf("%c",p->data);
		p=p->next;
	}
	printf("\n");
}


int main()
{
	int m = 0,n = 0;
	int i = 0,j = 0;
	linkstrnode *st1 = NULL,*st2 = NULL,*st3 = NULL;
	printf("������һ���ַ�����\n");
	st1 = strcreate(st1);
	printf("������ַ���Ϊ��\n");
	display(st1);
	printf("��������Ҫ������ַ�����\n");
	st2 = strcreate(st2);
	printf("��������Ҫ�����λ�ã�\n");
	scanf("%d",&m);
	st1 = strinsert(st1,m,st2);
	printf("��st1�ĵ�%d��λ���ϲ���st2����ַ���Ϊ��\n",m);
	display(st1);
	printf("��������Ҫɾ�����ַ�����λ���Լ����ȣ�\n");
	scanf("%d%d",&i,&j);
	getchar();
	st1 = strdelete(st1,i,j);
	printf("st1��λ��%d��ɾ������Ϊ%d���ַ�������ַ���Ϊ:\n",i,j);
	display(st1);
	printf("��������Ҫ���ӵ��ַ�����\n");
	st3 = strcreate(st3);
	st1 = strconcat(st1,st3);
	printf("���Ӻ���ַ���Ϊ��\n");
	display(st1);
	printf("��������Ҫ����ִ���λ�ü�����\n");
	i = 0,j = 0;
	scanf("%d%d",&i,&j);
	getchar();
	st1 = substring(st1,i,j);
	printf("��õ��ַ���Ϊ��\n");
	display(st1);
	st2 = NULL;
	printf("������һ���ַ��������бȽϣ�\n");
	st2 = strcreate(st2);
	printf("���Ϊ��\n");
	strcompare(st1,st2);
	return 0;
}
