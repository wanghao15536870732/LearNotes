/*
��д����ͳ�������ĸ�������������ʱ����һ����Ȼ��n��n��100��10000֮�䣩��
���100��n֮�䣨����n�������ĸ���������ʾ��ֻ�ܱ�1����������������Ϊ��������
*/ 

#include <stdio.h>
#include <math.h>
int main()
{	
	int n,i,j,s;
	puts("������һ����Ȼ�� ��");
	scanf("%d",&n);
	if(n < 100 || n > 10000) return 0;
	s = 0;
	for(i = 100;i <= n;i ++)
	{
		for(j = 2;j <= (int) sqrt( (double) i );j ++)
			if(i % j == 0)
				break;
			if(j == (int) sqrt( (double) i ) + 1)
				s ++;
	}
	printf("100������Ȼ��֮�������ĸ���Ϊ ��%d",s);
	return 0;
}

