/*
��˳���(a1,a2,��,an)����������a1Ϊ��������֣�a1ǰ���ֵ����a1С��
a1�����ֵ����a1�������������Ԫ�ص����;��пɱ��ԣ�������Ϊ���ͣ���
�������Լ���������ݽṹ�Ŀγ̷��� 
*/ 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/***************************************/
/* ˳����ͷ�ļ�,�ļ��������ݽṹ.cpp */
/***************************************/

#define MAXSIZE 100
typedef int datatype;
typedef struct{
	datatype a[MAXSIZE];  //ѧ��
	char *name[MAXSIZE];  // ����
	datatype score[MAXSIZE]; //���ݽṹ�ɼ�;
	int size;
}sequence_list;


//˳���ĳ�ʼ�������ÿձ�
void init(sequence_list *slt);
//��˳���󲿽��в������
void append(sequence_list *slt,datatype x,char *name,int score);
//��ӡ˳�����ڵ��ֵ
void display(sequence_list slt);
//�ж�˳����Ƿ�Ϊ��
int empty(sequence_list slt);
//����˳�����ֵΪx�Ľڵ�λ��
int find(sequence_list slt,datatype x);
//ȡ��˳����е�i���ڵ��ֵ
datatype get(sequence_list slt,int i);
//��˳���� position λ�ò���ֵΪx�Ľڵ� 
void insert(sequence_list *slt,datatype x,int position,char *name,int score);
//ɾ��˳���� position λ�õĽڵ�
void dele(sequence_list *slt,int position);

//��a1��Ϊ���޽��л���
void compare(sequence_list *slt);

int main()
{
	sequence_list Stu;
	init(&Stu);
	append(&Stu,1707004711,"С��",73);
	append(&Stu,1707004712,"С��",56);
	append(&Stu,1707004713,"С��",82);
	append(&Stu,1707004714,"С��",78);
	append(&Stu,1707004715,"����",74);
	append(&Stu,1707004716,"����",67);
	append(&Stu,1707004717,"����Ⱥ",95);
	append(&Stu,1707004718,"������",87);
	insert(&Stu,1707004710,3,"֩����",34);
	//����չʾ����ӵ�����
	display(Stu);
	//��a1Ϊ�ֽ��߻�������
	compare(&Stu);
	//�ٴ�չʾ˳��������
	display(Stu);
	return 0;
}



/**************************************/
/* �������ܣ�˳���ĳ�ʼ�������ÿձ� */
/**************************************/
void init(sequence_list *slt)
{
	slt->size = 0;
}

/**************************************/
/* �������ܣ���˳���󲿽��в������ */
/**************************************/

void append(sequence_list *slt,datatype x,char *name,int score)
{
	if(slt->size == MAXSIZE)
	{
		printf("˳���������");
	}
	slt->a[slt->size] = x;
	slt->score[slt->size] = score;
	slt->name[slt->size] = name;
	slt->size = slt->size + 1;
}

/**************************************/
/* �������ܣ���ӡ˳�����ڵ��ֵ     */
/**************************************/
void display(sequence_list slt)
{
	int i;
	if(!slt.size)
		printf("\n˳����ǿյģ�");
	else
		printf("\tѧ��\t\t����\t���ݽṹ�ɼ�\n");
		for(i = 0;i < slt.size;i ++)
			printf("%15d\t\t%s\t%7d\n",slt.a[i],slt.name[i],slt.score[i]);
	printf("\n");
}



/**************************************/
/* �������ܣ��ж�˳����Ƿ�Ϊ��       */
/**************************************/
int empty(sequence_list slt)
{
	return(slt.size == 0 ? 1 : 0);
}

/******************************************/
/* �������ܣ�����˳�����ֵΪx�Ľڵ�λ��  */
/******************************************/
int find(sequence_list slt,datatype x)
{
	int i = 0;
	while(i < slt.size && slt.a[i] != x)
		i ++;
	return(i < slt.size ? i : -1);
}

/******************************************/
/* �������ܣ�ȡ��˳����е�i���ڵ��ѧ��  */
/******************************************/
datatype get(sequence_list slt,int i)
{
	if(i < 0 || i >= slt.size)
	{
		printf("\nָ��λ�õĽڵ㲻���ڣ�");
		exit(1);
	}
	else
		return slt.a[i];
}

/******************************************************/
/* �������ܣ���˳���� position λ�ò���ֵΪx�Ľڵ�  */
/******************************************************/
void insert(sequence_list *slt,datatype x,int position,char *name,int score)
{
	int i;
	if(slt->size == MAXSIZE)
	{
		printf("\n˳���������!û������!");
		exit(1);
	}
	if(position < 0 || position > slt->size)
	{
		printf("\nָ���Ĳ���λ�ò�����!");
		exit(1);
	}
	for(i = slt->size;i > position;i --)
	{
		slt->a[i] = slt->a[i - 1];
		slt->name[i] = slt->name[i - 1];
		slt->score[i] = slt->score[i - 1];
	}
	slt->a[position] = x;
	slt->name[position] = name;
	slt->score[position] = score;
	slt->size ++;
}

/***********************************************/
/* �������ܣ�ɾ��˳���� position λ�õĽڵ�  */
/***********************************************/

void dele(sequence_list *slt,int position)
{
	int i;
	if(slt->size == 0)
	{
		printf("˳����ǿյ�!");
		exit(1);
	}
	if(position < 0 || position >= slt->size)
	{
		printf("\nָ����ɾ��λ�ò�����");
		exit(1);
	}
	for(i = position;i < slt->size - 1;i ++)
	{
		slt->a[i] = slt->a[i + 1];
		slt->name[i] = slt->name[i + 1];
		slt->score[i] = slt->score[i + 1];
	}
	slt->size --;
}

/***********************************************/
/* �������ܣ���˳�����������,a1λ��Ϊ��
��Ϊ�����֣�positionǰ���ֵ����slt->a[position]����ֵС
position�����ֵ����slt->a[position]����ֵ��  */
/***********************************************/
void compare(sequence_list *slt)
{
	if(!slt->size)
		printf("\n˳����ǿյģ�\n");
	else
	{
		//���ȱ����һ��ѧ���ĳɼ�
		int score = slt->score[0];
		for(int i = 1;i < slt->size;i ++)
		{
			if(slt->score[i] < score)
			{
				//�������ѧ���ĳɼ�������ͷ���������ݲ��뵽��һλ
				insert(slt,slt->a[i],0,slt->name[i],slt->score[i]);
				//ɾ���ո��ƶ����Ǹ�ԭ����
				dele(slt,i + 1);
			}
		}
	}
}

