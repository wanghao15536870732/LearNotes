/*
��д������һ����10�����������У������ɼ������룩�����㲢��������зǸ����ĸ�����
*/ 
#include <stdio.h>
int main()	
{
	int num[10];
	int i,j,s;
	puts("������ʮ������ ��"); 
	for(i = 0;i < 10;i ++)
		scanf("%d",&num[i]);
	s = 0;
	for(j = 0;j < 10;j ++)
	{
		if(num[j] >= 0)
			s ++;
	}
	printf("�������зǸ����ĸ���Ϊ ��%d\n",s);
	return 0;
}

