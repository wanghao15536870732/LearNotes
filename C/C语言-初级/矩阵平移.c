/*
��д������һ3��3�е��������������ɼ������룩��
�������²����������һ��������󣬾��������о�����һ�С���������ľ���
*/

#include <stdio.h>
int main()
{ 
	int num1[3][3],num2[3][3];
	int i,j;
	puts("������һ�����׾��� ��\n");
	for(i = 0;i < 3;i ++)
	{
		for(j = 0;j < 3;j ++)
			scanf("%d",&num1[i][j]);
	}
	for(i = 1;i < 3;i ++)
	{
		for(j = 0;j < 3;j ++)
			num2[i - 1][j] = num1[i][j];
	}
	for(j = 0;j < 3;j ++)
		num2[2][j] = num1[0][j];
	puts("ת��֮��ľ���Ϊ ��");
	for(i = 0;i < 3;i ++)
	{
		for(j = 0;j < 3;j ++)
		{
			printf("%d ",num2[i][j]);
			if(j == 2)
				printf("\n");
		}
	}
	printf("\n");	
	return 0;
}	


