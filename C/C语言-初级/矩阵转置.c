/*
��д������һ3��3�е���������(�����ɼ�������)������þ����ת�þ���
(��ʾ��ת�þ��������ԭ�������)��
*/ 
#include <stdio.h>
int main()	
{	
	int i,j;
	int num1[3][3],num2[3][3];
	puts("����һ��3��3�еľ��� ��");
	for(i = 0;i < 3;i ++)
	{	
		for(j = 0;j < 3;j ++)
		{	
			scanf("%d",&num1[i][j]);
		}
	}
	for(i = 0;i < 3;i ++)
	{	
		for(j = 0;j < 3;j ++)
		{
			num2[i][j] = num1[j][i];
		}
	}
	puts("ת�ú�ľ���Ϊ ��\n"); 
	for(i = 0;i < 3;i ++)
	{	
		for(j = 0;j < 3;j ++)
		{		
			printf("%d ",num2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}


