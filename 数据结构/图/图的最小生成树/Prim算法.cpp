#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#define M 30  /*Ԥ����ͼ����󶥵���*/
#define FINITY 5000  //�� 5000��������


//��С�������㷨�Ľṹ��
typedef struct {
	char vexs[M];  //�����������
	int edges[M][M];  //������ڽӾ���
	int n, e;  //ͼ�еĶ������ͱ���
}Mgraph;


typedef struct edgedata
{
	int beg, en;  //beg,en���Ƕ������
	int length;  //�߳�
}edge;



void create(Mgraph *g, char *filename, int c)  //c = 0��ʾ��������ͼ 
{
	int weight = 0;  //�ߵ�Ȩֵ
	int front, rear; //���ǰ���ͺ���
	FILE *file;
	file = fopen(filename, "r"); //���ļ���ȡͼ�ı���Ϣ
	if (file)
	{
		fscanf(file, "%d%d\n", &g->n, &g->e);  //��ȡͼ�Ķ����������
		for (int i = 0; i < g->n; i++)
		{
			fscanf(file, "%c", &g->vexs[i]);  //��ȡͼ�ж������Ϣ��
		}
		for (int i = 0; i < g->n; i++)
		{
			for (int j = 0; j < g->n; j++)
			{
				if (i == j)
					g->edges[i][j] = 0;  //�Խ����ϵľ�Ϊ0
				else
					g->edges[i][j] = FINITY;  //û�и�ֵ������ӳ���
			}
		}
		for (int k = 0; k < g->e; k++)
		{
			fscanf(file, "%d%d%d", &front, &rear, &weight);
			g->edges[front][rear] = weight;  //ֻЩ��Ӧ˳��ģ�������ͼ
			if (c == 0)
				g->edges[rear][front] = weight;  //�Գ�ͼ�Σ���Ϊ����ͼ
		}
		fclose(file);
	}
	else
	{
		g->n = 0;
		printf("�ļ���ʧ�ܣ�\n");
	}
}




//��С��������prim�㷨
void prim(Mgraph g, edge tree[M - 1])
{
	edge x;
	/*
	min ������С��Ȩֵ
	s ���������ǰ�ڵ㣬����ѡ�����򣬾���ѡ�������б����±�ֵһ��

	*/
	int d, min, s, v;
	for (v = 1; v <= g.n - 1; v++)  //v��1��ʼ�������� - 1
	{
		tree[v - 1].beg = 0;  //�Ӷ���v0��ʼ����С������
		tree[v - 1].en = v;  //�߶���
		tree[v - 1].length = g.edges[0][v];  //������ڵ�����бߵ�Ȩֵ
	}
	for (int k = 0; k <= g.n - 3; k++)  //������ǰ(��k��)��С���ܱߣ�������TREE,����˼�����ѡ������
	{
		min = tree[k].length;  //min���ڱ�����СȨֵ
		s = k;  //���潻��֮ǰ���±�
		for (int j = k + 1; j <= g.n - 2; j++)
		{
			if (tree[j].length < min)
			{
				min = tree[j].length;  //������СȨֵ
				s = j; //���������ǰ���±�
			}
		}
		v = tree[s].en;  //��ѡ�Ľ��
		/*���������ṹ�壬����ѡ�������н�������ֵһ��*/
		x = tree[s];
		tree[s] = tree[k];
		tree[k] = x;
		for (int j = k + 1; j <= g.n - 2; j++)
		{
			d = g.edges[v][tree[j].en];   //���ڽӾ����л�ȡ�������Ľڵ㵽�����ڵ��Ȩֵ
			if (d < tree[j].length)  //���d��ȨֵС���ڽӾ����е�ʵ��Ȩֵ
			{
				tree[j].length = d; //��ֵȨֵ
				tree[j].beg = v; //��ֵ
			}
		}
	}

	printf("\n��С������Ϊ��\n");
	for (int j = 0; j <= g.n - 2; j++)
	{
		printf("\n%c---%c %d\n", g.vexs[tree[j].beg], g.vexs[tree[j].en], tree[j].length);
	}

	printf("\n���ڵ�Ϊ��%c\n", g.vexs[0]);
}

int main()
{
	Mgraph h;
	edge tree[M - 1];
	char filename[20] = "D:\\Desktop\\Test.txt";
	create(&h, filename, 0);
	prim(h, tree);
	system("pause");
	return 0;
}

