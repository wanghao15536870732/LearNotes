/*
��д������һ���е�ֵ����������������ʾ����������m������n��ֵ��������е�ֵ��
����������С�����ֱ�����λС������
��(k=1,m) k + ��(k=1,m) k^2 +��(k=1,n) 1/k + ��(k=1,n) 1/k^2 
*/ 
#include <stdio.h>
int main()
{	
	int n,i;
	double s;
	printf("������һ�������� ��");
	scanf("%d",&n);
	if(n <= 0) return 0;
	s = 1;
	for(i = 2; i <= n;i ++)
		s = s - 1.0 / i;
	printf("%.2lf\n",s);
	return 0;
}


