/*
��д������һ������10��Ԫ�ص����������е����Ԫ��ֵ�������ɼ������룩��
*/

#include <stdio.h>
int main()	
{
	int num[10];
	int i,j;
	puts("������ʮ������ ��"); 
	for(i = 0;i < 10;i ++)
		scanf("%d",&num[i]);
	for(j = 0;j < 10;j ++)
	{
		if(num[0] < num[j])
			num[0] = num[j];
	}
	printf("������������Ԫ��Ϊ ��%d\n",num[0]);
	return 0;
} 

