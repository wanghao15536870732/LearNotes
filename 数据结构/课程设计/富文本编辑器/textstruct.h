#define M 200 /*Ԥ�������к�*/
//ÿ���ֵĽṹ��
#define MAXSIZE 2000
typedef struct node
{
	char data[1000]; //һ���ֵ�������
	int length;		 // һ���ֵ�������
} Word;

typedef struct vnode
{
	int row;		 //�����к�
	Word *FirstWord; //�ڽӱ��ͷָ��,ָ��ÿһ�еĵ�һ����
} Vertexnode;

typedef struct
{						  //�ڽӱ�����
	Vertexnode column[M]; //���ÿһ��ͷ�ڵ��˳���
	int count;			  //��¼������
} TextCompiler;			  //�����ı��������ṹ��

#define MAXSIZWE 2000
typedef struct
{
	char str[MAXSIZWE];
	int length;
} seqstring;

typedef struct
{
	int a[MAXSIZE];
	int top;
} seqstack;