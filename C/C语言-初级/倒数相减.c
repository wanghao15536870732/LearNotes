/*
��д������һ���е�ֵ������������ʾ����������ʱ����������n�����y��ֵ��
����������С�����ֱ�����λС���� 
 y = 1 - 1 / 2 - 1 / 3 - ... - 1 / n
*/ 

#include <stdio.h>
int main()
{	
	int n,m,k;
	double s;
	printf("���������������� ��");
	scanf("%d%d",&n,&m);
	if(n <= 0 || m <= 0) return 0;
	s = 0;
	for(k = 1;k <= m;k ++)
	s += k;
	for(k = 1;k <= m;k ++)
	s += k * k;
	for(k = 1;k <= m;k ++)
	s += 1.0 / k;
	for(k = 1;k <= m;k ++)
	s += 1.0 / k * k; 
	printf("%.2lf\n",s);
	return 0;
}

