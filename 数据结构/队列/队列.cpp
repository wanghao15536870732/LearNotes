/************************/
/**** ���е�ͷ�ļ� ******/
/************************/
# include "stdio.h"
# include "stdlib.h"
# define MAXSIZE 100
typedef int datatype;
typedef struct {
	datatype a[MAXSIZE];
	int front;
	int rear;
}sequence_queue;


//���еĳ�ʼ��
void init(sequence_queue *sq);
//�ж϶����Ƿ�Ϊ��
int empty(sequence_queue sq);
//��ӡ���еĽڵ�ֵ
void display(sequence_queue sq);
//ȡ�ö��еö��׽ڵ�ֵ
int get(sequence_queue sq);
//���еĲ������
void insert(sequence_queue *sq,int x);
//���е�ɾ������
void dele(sequence_queue *sq);
//ѭ�����еĲ������
void insert_sequence_cqueu(sequence_queue *slt,int x);
//ѭ�����е�ɾ������
void dele_quence_cqueu(sequence_queue *slt);

int main()
{
	int i = 0,j = 0,x = 0;
	sequence_queue Stu;
	init(&Stu);
	scanf("%d",&i);
	for(j = 0;j < i;j ++)
	{
		scanf("%d",&x);
		insert(&Stu,x);
	}
	printf("\n");
	printf("��ͨ���в���\n");
	display(Stu);
	printf("\n");
	printf("ѭ�����в���\n");
	for(i = 7; i < 10;i ++)
		insert_sequence_cqueu(&Stu,i);
	dele_quence_cqueu(&Stu);
	display(Stu);
	return 0;
}

/***********************/
/*** ���еĳ�ʼ�� ******/
/***********************/
void init(sequence_queue *sq)
{
	sq->front = sq->rear = 0;
}

/***************************/
/*** �ж϶����Ƿ�Ϊ�� ******/
/***************************/
int empty(sequence_queue sq)
{
	return (sq.front == sq.rear ? 1 : 0);
}

/***************************/
/*** ��ӡ���еĽڵ�ֵ ******/
/***************************/

void display(sequence_queue sq)
{
	int i;
	if(empty(sq))
		printf("��������ǿյģ�");
	else
		for(i = sq.front;i < sq.rear;i ++)
			printf("%5d",sq.a[i]);
}

/*******************************/
/*** ȡ�ö��еö��׽ڵ�ֵ ******/
/*******************************/

int get(sequence_queue sq)
{
	if(empty(sq))
	{
		printf("\n˳����ǿյģ��޷���ȡ�����׽ڵ��ֵ!\n");
		exit(1);
	}
	return sq.a[sq.front];
}

/*******************************/
/******* ���еĲ������ ********/
/*******************************/

void insert(sequence_queue *sq,int x)
{
	int i;
	if(sq->rear == MAXSIZE)
	{
		printf("���������ģ�");
		exit(1);
	}
	sq->a[sq->rear] = x;
	sq->rear = sq->rear + 1;
}

/*******************************/
/******* ���е�ɾ������ ********/
/*******************************/

void dele(sequence_queue *sq)
{
	if(sq->front == sq->rear)
	{
		printf("\n����ʱ�յģ����ܽ���ɾ��������\n");
		exit(1);
	}
	sq->front ++;
}


/***********************************/
/******* ѭ�����еĲ������ ********/
/***********************************/

void insert_sequence_cqueu(sequence_queue *slt,int x)
{
	if((slt->rear + 1) % MAXSIZE == slt->front)
	{
		printf("˳����������޷����в��������\n");
		exit(1);
	}
	slt->a[slt->rear] = x;
	slt->rear = (slt->rear + 1) % MAXSIZE;
}


/***********************************/
/******* ѭ�����е�ɾ������ ********/
/***********************************/

void dele_quence_cqueu(sequence_queue *slt)
{
	if(slt->front == slt->rear)
	{
		printf("�����ǿյģ��޷�����ɾ��������\n");
		exit(1);
	}
	slt->front = (slt->front + 1) % MAXSIZE;
}
