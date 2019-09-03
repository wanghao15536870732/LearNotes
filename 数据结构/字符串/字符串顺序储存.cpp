#include "stdio.h"
#include "stdlib.h"
# define MAXSIZE 100

//˳�򴮵�ͷ�ļ�
typedef struct{
	char str[MAXSIZE];
	int length;
}seqstring;

//�ַ����Ĵ���
seqstring *create()
{
	int m = 0;
	seqstring *p;
	p = (seqstring *)malloc(sizeof(seqstring));
	printf("�����뽫Ҫ������ַ�������:\n");
	scanf("%d",&m);
	p->length = m;
	printf("�������ַ���:\n");
	scanf("%s",p->str);
	return p;

}
//˳�򴮵Ĳ���
seqstring *strinsert(seqstring *S,int i,seqstring *T)
{
	int k;
	if(i < 1 || i > S->length + 1 || S->length + T->length > MAXSIZE -1)/*�Ƿ��ж�*/
		printf("�ַ����������޷����룡\n");
	else
	{
		//�ӵ�i��Ԫ�ؿ�ʼ����
		for(k = S->length; k >= i - 1;k --)
			S->str[T->length + k] = S->str[k];
		//��Tд��S�еĵ�i���ַ�����ʼ��λ��
		for(k = 0;k < T->length; k ++)
			S->str[i + k - 1] = T->str[k];
		S->length = S->length + T->length;
		S->str[S->length] = '\0';
	}
	return S;
}

//�ַ�����ɾ��
seqstring *strdelete(seqstring *S,int i,int len)
{
	int k;
	if(i < 1 || i > S->length || i + len - 1 > S->length) /*�Ƿ�����Ĵ���*/
		printf("�޷������ַ�����");
	else
	{
		for(k = i + len - 1; k < S->length; k ++)
			//s�д��±�Ϊi + len - 1��ʼ��Ԫ��ǰ��
			S->str[k - len] = S->str[k];
		S->length = S->length - len;
		S->str[S->length] = '\0';
	}
	return S;
}

//�ַ���������
seqstring *strconcat(seqstring *S1,seqstring *S2)
{
	int i;
	seqstring *r;
	//�����ַ�������ռ䲻��ʹ�õ����
	if(S1->length + S2->length > MAXSIZE - 1)
	{
		printf("�޷������ַ�����\n");
		return (NULL);
	}
	else
	{
		r = (seqstring *) malloc(sizeof(seqstring));
		//��s1���Ƶ�r�ַ�����ǰ��
		for(i = 0;i < S1->length;i ++)
			r->str[i] = S1->str[i];
		//��s2���Ƶ�r�ַ����ĺ��
		for(i = 0;i < S2->length;i ++)
			r->str[S1->length  + i] = S2->str[i];
		r->length = S1->length + S2->length;
		r->str[r->length] = '\0';
	}
	return (r);
}

//������ַ������Ӵ�
seqstring *substring(seqstring *S,int i,int len)
{
	int k;
	seqstring *r;
	//����Ƿ����
	if(i < 1 || i > S->length || i + len - 1 > S->length)
	{
		printf("����\n");
		return (NULL);
	}
	else
	{
		r = (seqstring *) malloc(sizeof(seqstring));
		for(k = 0;k < len;k ++)
			r->str[k] = S->str[i + k - 1];
		r->length =len;
		r->str[r->length] = '\0';
	}
	return (r);
}

void display(seqstring *p)
{
	if(!p)
	{
		printf("��˳�򴢴���ַ���Ϊ�գ�");
		exit(0);
	}
	printf("%s",p->str);
	printf("\n");
}

int strcompare(seqstring *st1,seqstring *st2)
{
	int i = 0;
	while(st1->str[i] == st2->str[i])
		i ++;
	if(i == st1->length && i == st2->length)
		return 0;
	//����st1->str[i] ��= st2->str[i]�������
	else if(st1->str[i] > st2->str[i] || st1->length > st2->length)
		return 1;
	else
		return -1;
}

int main()
{
	int m = 0,n = 0;
	int i = 0,j = 0;
	seqstring *st1,*st2,*st3;
	st1 = create();
	printf("�������ַ���Ϊ��\n");
	display(st1);
	printf("\n");
	printf("������Ҫ������ַ���");
	printf("\n");
	st2 = create();
	printf("��������Ҫ�����λ�ã�\n");
	scanf("%d",&m);
	st1 = strinsert(st1,m,st2);
	printf("���ַ���st1��%dλ���ϲ���st2����ַ���Ϊ��\n",m);
	display(st1);
	printf("\n");
	printf("��������Ҫɾ����λ���Լ��ַ�������:\n");
	scanf("%d%d",&i,&j);
	st1 = strdelete(st1,i,j);
	printf("ɾ��%dλ����%d���ȵ��ַ�������ַ���:\n",i,j);
	display(st1);
	printf("\n");
	printf("����һ����Ҫ���ӵ��ַ���\n");
	st3 = create();
	st1 = strconcat(st1,st3);
	printf("��st3���ӵ�st1�������ַ���Ϊ��\n");
	display(st1);
	printf("\n");
	printf("��������Ҫ��ȡ���ַ���λ���Լ�����:\n");
	i = 0,j = 0;
	scanf("%d%d",&i,&j);
	st1 = substring(st1,i,j);
	printf("��ȡ�ַ�����%dλ���ϳ���Ϊ%d���Ӵ�:\n",i,j);
	display(st1);
	printf("\n");
	printf("��������Ҫ�����ַ����Ƚϵ��ַ���\n");
	st3 = create();
	printf("�����\n");
	display(st1);
	display(st3);
	if(strcompare(st1,st3) == 0)
		printf("�����ַ������\n");
	else if(strcompare(st1,st3) == 1)
		printf("��һ���ַ������ڵڶ����ַ���\n");
	else if(strcompare(st1,st3) == -1)
		printf("��һ���ַ���С�ڵڶ����ַ���\n");
	else
		printf("error");
	return 0;
}
