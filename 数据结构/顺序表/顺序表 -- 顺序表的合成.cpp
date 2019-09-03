/*
��˳���A��B����Ԫ�ؾ�����С������������У���дһ���㷨�������Ǻϲ���һ��˳���C��
Ҫ��C��Ԫ��Ҳ����С������������С�
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
//˳���ɼ�����
void sort(sequence_list *slt);
//�����ڵ�
void exchange(sequence_list *slt,int position1,int position2);
//����int���͵�����
void exchange_num(datatype *x,int *y);
//�����ַ���������
void exchange_string(char a[],char b[]);
//˳���ĺϳ�
void sort_insert(sequence_list *slt1,sequence_list *slt2,sequence_list *slt3);
void sort_insert2(sequence_list *slt1,sequence_list *slt2);

int main()
{
	sequence_list Stu1,Stu2,Stu3;
	init(&Stu1);
	init(&Stu2);
	init(&Stu3);
	append(&Stu1,1707004711,"С��",56);
	append(&Stu1,1707004712,"С��",62);
	append(&Stu1,1707004713,"С��",73);
	append(&Stu1,1707004714,"������",78);
	append(&Stu2,1707004715,"��Ҳ",43);
	append(&Stu2,1707004716,"С��",56);
	append(&Stu2,1707004717,"С��Ⱥ",65);
	append(&Stu2,1707004718,"С����",72);
	append(&Stu2,1707004719,"֩����",83);
	printf("ԭʼ�����ݣ�\n");
	printf("���ݱ�1��\n");
	display(Stu1);
	printf("���ݱ�2��\n");
	display(Stu2);
	printf("\n-------------------------------------\n");
	printf("\n����slt1��slt2�ӵ�slt3���еķ���:\n\n");
	sort_insert(&Stu1,&Stu2,&Stu3);
	display(Stu3);
	printf("\n����slt1���뵽slt2�ķ���:\n\n");
	sort_insert2(&Stu1,&Stu2);
	display(Stu2);
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

/********************************************************/
/* �������ܣ���˳���slt1��˳���slt2˳�����ӵ�stl3����*/        
/******************************************************/
void sort_insert(sequence_list *slt1,sequence_list *slt2,sequence_list *slt3)
{
	int i = 0,j = 0; //i����ɨ��˳���slt1,j����ɨ��˳���slt2
	if(slt1->size == 0 || slt2->size == 0)
		printf("�пյ�˳���!\n");
	while(i < slt1->size && j < slt2->size)
	{
		if(slt1->score[i] < slt2->score[j])
		{
			//��slt3�ĺ������slt1������
			append(slt3,slt1->a[i],slt1->name[i],slt1->score[i]);
			//
			i ++;
		}
		else
		{
			//��slt3�ĺ������slt2������
			append(slt3,slt2->a[j],slt2->name[j],slt2->score[j]);
			j ++;
		}
	}

	while(i < slt1->size)//��slt1δɨ���꣬��slt1ʣ���Ԫ�ؼӵ�slt3��
	{
		append(slt3,slt1->a[i],slt1->name[i],slt1->score[i]);
		i ++;
	}

	while(j < slt2->size)//��slt2δɨ���꣬��slt2ʣ���Ԫ�ؼӵ�slt3��
	{
		append(slt3,slt2->a[j],slt2->name[j],slt2->score[j]);
		j ++;
	}
}

/********************************************************/
/* �������ܣ���˳���slt1��˳���˳��Ĳ嵽slt2����*****/        
/******************************************************/
void sort_insert2(sequence_list *slt1,sequence_list *slt2)
{
	int i = 0,j = 0;
	while(i < slt1->size)
	{
		//���˳���slt1�����ݱ�slt2���Ķ���ֱ�ӽ�slt1�����ݼӵ�slt2���� 
		if(slt1->score[i] > slt2->score[slt2->size - 1])
		{
			append(slt2,slt1->a[i],slt1->name[i],slt1->score[i]);
			i ++;
		}else if(slt1->score[i] < slt2->score[j])  //������slt1�����ݱ�slt2λ��j�ϵĵ�ҪС 
		{
			// ��slt1�����ݲ��뵽slt2�� j ��λ�� 
			insert(slt2,slt1->a[i],j,slt1->name[i],slt1->score[i]); 
			//����˳������ɨ�� 
			i ++;
			j ++;
		}else
			//���ɨ��slt2 
			j ++;
	}
}
