/*
��д�������Ĺ����ǣ�����������m��m��ֵ��100~10000֮�䣩��
ʹ�õȲ�����1��2��3��4��5��6��nǰn���С��m��ǰn+1��ʹ���m�����n��ֵ��
��m��ֵΪ155��1+2+����+17>155,��1+2+����+17+18<155�����17��
*/ 

#include <stdio.h>
#include <stdlib.h>
int main()
{	
	int m,n,i,s;
	printf("������һ��������m ��");
	scanf("%d",&m);
	if(m < 100 || m > 1000) return 0;
	s = 0;
	for(i = 1;i <= m;i ++)
	{
		s += i;
		if(s > m) break; 
	}
	printf("%d",i - 1);
	system("pause");
	return 0;
} 
