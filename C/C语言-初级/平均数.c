/*
��д������һ����10�����������У������ɼ������룬��֤������һ����������
���㲢�������������������ƽ��ֵ�����������λС������
*/

#include <stdio.h>
#include <math.h>
int main()
{ 
	int num[10];
	int i;
	double n,c,s;
	puts("������ʮ������ ��\n");
	for(i = 0;i < 10;i ++)
		scanf("%d",&num[i]);
	c = 0;
	s = 0;
	for(i = 0;i < 10;i ++)
	{
		if(num[i] > 0)
		{
			s += num[i];
			c ++;
		}
	}
	n = s / c;
	printf("����������������ƽ��ֵ ��%.2lf\n",n);
	return 0;
}

